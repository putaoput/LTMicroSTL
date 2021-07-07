//@Author: Lin Tao
//@Email: putaopu@qq.com
#pragma once

#include <assert.h>
#include "memory.h"
#include "iterator.h"
#include "type_traits.h"
#include "allocator.h"
#include "uninitialized.h"
#include "algobase.h"
#include <atomic>

//该文件利用atomic实现无锁定长循环数组
//对以下接口进行线程安全保证：
//预初始化，支持右值引用和移动以提高效率。
//使用了消费者和生产者模型，通过返回值来提示应该调用消费者还是生产者
//push_back()
//pop_front()
namespace LT {
    template<typename T, size_t LENGTH, class Alloc = allocator<T>>
    class thread_safe_vector {
        //先定义一些类型
    public:
        typedef T											value_type;
        typedef value_type*									pointer;
        typedef const T* const_pointer;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef LT::reverse_iterator<iterator>				reverse_iterator;
        typedef LT::reverse_iterator<const_iterator>		const_reverse_iterator;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t										size_type;
        typedef ptrdiff_t									difference_type;

        //定义vector内部的三个重要的指针
    private:
        iterator start_;
        std::atomic_int front_; //用来标识循环数组的头
        std::atomic_int back_;  //用来标识循环数组的尾
        std::atomic_int writableCount_; //用来确定任务队列是否为空，或者为满
        std::atomic_int readableCount_;


/////********************************************************************************************************
//**************************************************对外接口**************************************************
////**********************************************************************************************************
    public:
        //写一些构造函数
         vector()
                :start_(0), finish_(0), endOfStorage_(0)
        {
            //对每个元素进行预初始化
            __init_n(LENGTH,node<T>());
        }



        //析构函数
        ~vector()
        {
            __destroy_mem(start_ , start_ + LENGTH);
            __deallocate_mem(start, start_ + LENGTH);
        }
        //------------------------------------------------------------这一组是公共接口，对外的api----------------------------------------------
    public:
        // @parm ret通过这个引用来获取数组第一个元素的值，这里使用了移动拷贝来提高效率。
        // @返回bool值，如果为true代表获取了第一个元素应调用消费者，如果为false，当前数组为空，应调用生产者。
        //
        bool pop_front(reference ret)
        {
            int nowCount = readableCount_--;
            if(nowCount < 0)//如果发现可以写的数量太少，就加回去，然后继续等待。这里最好是能够唤醒生产者。//
            {
                ++readableCount_;
                return false;
            }

            int idx = front_++;
            idx %= LENGTH;//以防万一
            front_ %= LENGTH;//
            ret = LT::move(*(start_ + idx));
            ++writableCount_;
            return true;
        }

        // @parm _args 可以传入左值或者右值引用
        // @返回bool值，如果为true代表填充了一个元素应调用生产者，如果为false，当前数组为空，应调用生产者。
        //
        template<class Args>
        bool push_back(Args&& _args) {

            int nowCount = writableCount_--;
            if(writableCount_ < 0)
            {
                ++writableCount_;
                return false;
            }

            int idx = back_++;
            idx %= LENGTH;//以防万一
            front_ %= LENGTH;//
            *(start_ + idx) = LT::forward<Args>(_args);//支持右值或左值
            ++readableCount_;
            return tmp;
        }



        bool full()
        {
            return !writableCount_;
        }

        bool  empty()
        {
            return !readableCount_;
        }



        //--------------------------------------------------------------容量配置器相关-----------------------------------------
        Alloc get_allocator() const { return allocator_type(); }
        /////********************************************************************************************************
        //**************************************************内部实现**************************************************
        ////**********************************************************************************************************
    private:
        //----------------------------------------------声明一组函数用来配置空间，包括进行初始化------------------------
        //要完成以下内容:
        //1.配置一块大小为n的内存，并对齐进行初始化
        //2.配置一块大小为n的内存，对其中大小为m的部分进行拷贝初始化，剩下的内存进行
        //3.鉴于此，分为两部分，一部分是获得给定大小的内存，一部分是初始化给定大小的内存区域

        //空间配置函数
        typedef Alloc            allocator_type;

        //获得给定大小的内存区域,在这里有异常保证
        iterator __get_mem(size_type _size)
        {
            //事实上allo函数返回的是T*。但是不保证该内存大小一定为_size，
            try {
                pointer memPtr = allocator_type::allocate(_size);
                return static_cast<iterator>(memPtr);//vector实现时将T*定义成了iterator。
            }
            catch (...) {//这一层异常保证也许可以省略，因为在alloctor文件里面应该是提供了异常保证的
                return static_cast<iterator>(nullptr);
            }

        }

        //可进行右值初始化的函数
        template<class ...Args>
        void __construct_one(iterator _pos, Args&&... _args)
        {
            LT::construct(LT::address_of(*_pos), LT::forward<Args>(_args)...);
        }
        //初始化给定大小的区域。进行异常保证，这是左值构造
        void __construct_mem_n(iterator _begin, size_type _size, const value_type& _value) {
            LT::uninitialized_fill_n(_begin, _size, _value);
        }
        //这里要保证_begin的大小足够，顺序复制
        template<class InputIter>
        void __construct_mem_iter(iterator _begin, InputIter _itBeg, InputIter _itEnd)
        {
            size_type n = LT::distance(_itBeg, _itEnd);
            LT::uninitialized_copy(_itBeg, _itEnd, _begin);
        }

        //析构对象的函数
        void __destroy_mem(iterator _first, iterator _last)
        {
            //下一层construct函数会自己进行类型萃取，识别是否需要调用析构函数
            LT::destroy(_first, _last);
        }
        //释放内存
        template<class iterator>
        void __deallocate_mem(iterator _first, iterator _endOfStorage)
        {
            allocator_type::deallocate(_first, static_cast<size_type>((_endOfStorage - start_)));
        }


        //-------------------------------------------初始化函数----------------------------------------------------------------------
        //进行一个给定初始Length的初始化。
        void __init_n(size_type _size, const value_type& _value)
        {
            iterator newMem = __get_mem(_size);
            __construct_mem_n(newMem, _size, _value);
            start_ = newMem;
            finish_ = newMem + _size;
            endOfStorage_ = newMem + _size;
            front_ = 0;
            back_ = 0;
            writableCount_ = LENGTH;
            readableCount_ = 0;
        }
    };
}