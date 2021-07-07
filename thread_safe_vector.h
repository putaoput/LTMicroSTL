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

//���ļ�����atomicʵ����������ѭ������
//�����½ӿڽ����̰߳�ȫ��֤��
//Ԥ��ʼ����֧����ֵ���ú��ƶ������Ч�ʡ�
//ʹ���������ߺ�������ģ�ͣ�ͨ������ֵ����ʾӦ�õ��������߻���������
//push_back()
//pop_front()
namespace LT {
    template<typename T, size_t LENGTH, class Alloc = allocator<T>>
    class thread_safe_vector {
        //�ȶ���һЩ����
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

        //����vector�ڲ���������Ҫ��ָ��
    private:
        iterator start_;
        std::atomic_int front_; //������ʶѭ�������ͷ
        std::atomic_int back_;  //������ʶѭ�������β
        std::atomic_int writableCount_; //����ȷ����������Ƿ�Ϊ�գ�����Ϊ��
        std::atomic_int readableCount_;


/////********************************************************************************************************
//**************************************************����ӿ�**************************************************
////**********************************************************************************************************
    public:
        //дһЩ���캯��
         vector()
                :start_(0), finish_(0), endOfStorage_(0)
        {
            //��ÿ��Ԫ�ؽ���Ԥ��ʼ��
            __init_n(LENGTH,node<T>());
        }



        //��������
        ~vector()
        {
            __destroy_mem(start_ , start_ + LENGTH);
            __deallocate_mem(start, start_ + LENGTH);
        }
        //------------------------------------------------------------��һ���ǹ����ӿڣ������api----------------------------------------------
    public:
        // @parm retͨ�������������ȡ�����һ��Ԫ�ص�ֵ������ʹ�����ƶ����������Ч�ʡ�
        // @����boolֵ�����Ϊtrue�����ȡ�˵�һ��Ԫ��Ӧ���������ߣ����Ϊfalse����ǰ����Ϊ�գ�Ӧ���������ߡ�
        //
        bool pop_front(reference ret)
        {
            int nowCount = readableCount_--;
            if(nowCount < 0)//������ֿ���д������̫�٣��ͼӻ�ȥ��Ȼ������ȴ�������������ܹ����������ߡ�//
            {
                ++readableCount_;
                return false;
            }

            int idx = front_++;
            idx %= LENGTH;//�Է���һ
            front_ %= LENGTH;//
            ret = LT::move(*(start_ + idx));
            ++writableCount_;
            return true;
        }

        // @parm _args ���Դ�����ֵ������ֵ����
        // @����boolֵ�����Ϊtrue���������һ��Ԫ��Ӧ���������ߣ����Ϊfalse����ǰ����Ϊ�գ�Ӧ���������ߡ�
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
            idx %= LENGTH;//�Է���һ
            front_ %= LENGTH;//
            *(start_ + idx) = LT::forward<Args>(_args);//֧����ֵ����ֵ
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



        //--------------------------------------------------------------�������������-----------------------------------------
        Alloc get_allocator() const { return allocator_type(); }
        /////********************************************************************************************************
        //**************************************************�ڲ�ʵ��**************************************************
        ////**********************************************************************************************************
    private:
        //----------------------------------------------����һ�麯���������ÿռ䣬�������г�ʼ��------------------------
        //Ҫ�����������:
        //1.����һ���СΪn���ڴ棬��������г�ʼ��
        //2.����һ���СΪn���ڴ棬�����д�СΪm�Ĳ��ֽ��п�����ʼ����ʣ�µ��ڴ����
        //3.���ڴˣ���Ϊ�����֣�һ�����ǻ�ø�����С���ڴ棬һ�����ǳ�ʼ��������С���ڴ�����

        //�ռ����ú���
        typedef Alloc            allocator_type;

        //��ø�����С���ڴ�����,���������쳣��֤
        iterator __get_mem(size_type _size)
        {
            //��ʵ��allo�������ص���T*�����ǲ���֤���ڴ��Сһ��Ϊ_size��
            try {
                pointer memPtr = allocator_type::allocate(_size);
                return static_cast<iterator>(memPtr);//vectorʵ��ʱ��T*�������iterator��
            }
            catch (...) {//��һ���쳣��֤Ҳ�����ʡ�ԣ���Ϊ��alloctor�ļ�����Ӧ�����ṩ���쳣��֤��
                return static_cast<iterator>(nullptr);
            }

        }

        //�ɽ�����ֵ��ʼ���ĺ���
        template<class ...Args>
        void __construct_one(iterator _pos, Args&&... _args)
        {
            LT::construct(LT::address_of(*_pos), LT::forward<Args>(_args)...);
        }
        //��ʼ��������С�����򡣽����쳣��֤��������ֵ����
        void __construct_mem_n(iterator _begin, size_type _size, const value_type& _value) {
            LT::uninitialized_fill_n(_begin, _size, _value);
        }
        //����Ҫ��֤_begin�Ĵ�С�㹻��˳����
        template<class InputIter>
        void __construct_mem_iter(iterator _begin, InputIter _itBeg, InputIter _itEnd)
        {
            size_type n = LT::distance(_itBeg, _itEnd);
            LT::uninitialized_copy(_itBeg, _itEnd, _begin);
        }

        //��������ĺ���
        void __destroy_mem(iterator _first, iterator _last)
        {
            //��һ��construct�������Լ�����������ȡ��ʶ���Ƿ���Ҫ������������
            LT::destroy(_first, _last);
        }
        //�ͷ��ڴ�
        template<class iterator>
        void __deallocate_mem(iterator _first, iterator _endOfStorage)
        {
            allocator_type::deallocate(_first, static_cast<size_type>((_endOfStorage - start_)));
        }


        //-------------------------------------------��ʼ������----------------------------------------------------------------------
        //����һ��������ʼLength�ĳ�ʼ����
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