//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
#include <cstddef>
#include "type_traits.h"
#include "iterator.h"
//该头文件用来实现一些琐碎的标准库功能.主要有
//move， forward，swap,iter_swap, 堆的辅助函数，pair及相关函数.

namespace LT {
	

	//----------------------------------右值----------------------------------------------
		//forward函数是c++11的新特性，也是一个标准库里的函数，
		//为了在使用右值引用参数的函数模板中解决参数的完美转发问题
		//std::forward<T>(u)有两个参数：T 与 u。当T为左值引用类型时，u将被转换为T类型的左值，否则u将被转换为T类型右值。
		//std::move是无条件的转为右值引用，而std::forward是有条件的转为右值引用
	template <class T>
	typename std::remove_reference<T>::type&& move(T&& _args) noexcept
	{
		return static_cast<typename std::remove_reference<T>::type&&>(_args);
	}


	// forward

	template <class T>
	T&& forward(typename std::remove_reference<T>::type& _args) noexcept//告诉编译器不会抛出异常
	{
		return static_cast<T&&>(_args);
	}

	template <class T>
	T&& forward(typename std::remove_reference<T>::type&& _args) noexcept
	{
		//is_lvalue_reference：检查值是否为参考类型
		static_assert(!std::is_lvalue_reference<T>::value, "template argument"
			" substituting T is an lvalue reference type");
		return static_cast<T&&>(_args);
	}




	//-----------------------------------------swap-----------------------------------------------------
	//swap函数，这里用重要收获，原来c++里面是使用右值来加速交换的，减少了资源消耗

	template<class T>
	inline void swap(T& _lhs, T& _rhs) {
		T tmp = LT::move(_lhs);							//如果T&& tmp会移动失败，因为此时tmp此时仍然是一个右值引用。然后该右值会和左值a管理同一块内存
		_lhs = LT::move(_rhs);
		_rhs = LT::move(tmp);
	}
	//int型的swap使用位运算

	template<>
	inline void swap(int& _a, int& _b)
	{
		_a ^= _b;
		_b ^= _a;
		_a ^= _b;
	}

	template <class ForwardIter1, class ForwardIter2>
	inline ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 _last1, ForwardIter2 first2)
	{
		for (; first1 != _last1; ++first1, (void) ++first2)
			LT::swap(*first1, *first2);
		return first2;
	}

	//特例化，第二个参数可以输入个数
	template <class Tp, size_t _N>
	inline void swap(Tp(&_a)[_N], Tp(&_b)[_N])
	{
		LT::swap_range(_a, _a + _N, _b);
	}
	//迭代器的swap函数
	template <class ForwardIterator>
	inline void iter_swap(ForwardIterator _itA, ForwardIterator _itB) {
		LT::swap(*_itA, *_itB);
	}
	//--------------------------------------堆的相关辅助函数------------------------------------
	template<class RandomIterator,class Distance,  class Comp>//该函数自上向下调整堆
	void __adjust(RandomIterator _itBegin, Distance _index, Distance _len, Comp _cmp) {
		int left = 2 * _index + 1;//左右子节点
		int right = 2 * _index + 2;

		int maxIdx = _index;
		if (left < _len && _cmp(*(_itBegin + left), *(_itBegin + maxIdx))) { maxIdx = left; }
		if (left < _len && _cmp(*(_itBegin + right), *(_itBegin + maxIdx))) { maxIdx = right; }
		if (maxIdx != _index) {
			iter_swap(_itBegin + _index, _itBegin + maxIdx);
			__adjust(_itBegin, maxIdx, _len, _cmp);
		}
	} 

	template<class RandomIterator, class Comp>
	inline void __make_heap(RandomIterator _itBegin, RandomIterator _itEnd, Comp _cmp) {
		size_t len = _itEnd - _itBegin;
		for (int i = (_itEnd - _itBegin) / 2 - 1; i >= 0; --i) {
			LT::__adjust(_itBegin, i, len, _cmp);
		}
	}

	//push_heap
	//该函数提供堆尾压入一个元素之后调整堆。自下向上调整。
	template<class RandomIterator, class Distance, class T, class Comp>
	inline void __push_heap(RandomIterator _itBegin, Distance _holeIndex, Distance _topIndex, T _value, Comp _cmp) {
		//该函数是实际执行push_heap堆调整的函数
		Distance parent = (_holeIndex - 1) / 2; //holeIndex是压入的元素，找出该元素的父节点，然进行调整。
		while (_holeIndex < _topIndex && _cmp(*(_itBegin + parent), _value))//说明需要调整，不满足_cmp(child,parent) == true;
		{
			*(_itBegin + _holeIndex) = *(_itBegin + parent);
			_holeIndex = parent;
			parent = (_holeIndex - 1) / 2 ;
		}
		*(_itBegin + _holeIndex) = _value;//调整完成。
	}
	template<class RandomIterator, class Distance, class T, class Comp>
	inline void __push_heap_aux(RandomIterator _itBegin, RandomIterator _itEnd, Distance*, T*, Comp _cmp) {
		__push_heap(_itBegin, static_cast<Distance>(_itEnd - _itBegin - 1), Distance(0), T(*(_itEnd - 1)), _cmp);
	}

	template<class RandomIterator, class Comp>
	inline void push_heap(RandomIterator _itBegin, RandomIterator _itEnd, Comp _cmp) {
		__push_heap_aux(_itBegin, _itEnd, distance_type(_itBegin), value_type(_itBegin), _cmp);
	}
	

	//pop_heap
	//该函数提供pop一个元素之后，对堆的调整。自上向下
	template<class RandomIterator, class Distance, class Comp>
	inline void __pop_heap(RandomIterator _itBegin, Distance _holeIndex, Distance _tailIndex,Comp _cmp) {
		Distance left = _holeIndex * 2 + 1;
		Distance right = _holeIndex * 2 + 2;

		while (_holeIndex <= (_tailIndex - 1) / 2) {
			Distance tmpIndex = _holeIndex;
			if (left <= _tailIndex && _cmp(*(_itBegin + tmpIndex), *(_itBegin + left))) {
				tmpIndex = left;
			}
			if (right <= _tailIndex && _cmp(*(_itBegin + tmpIndex), *(_itBegin + right))) {
				tmpIndex = right;
			}
			if (tmpIndex == _holeIndex) {
				break;
			}
			else {
				LT::iter_swap(_itBegin + tmpIndex, _itBegin + _holeIndex);
				_holeIndex = tmpIndex;
			}
		}
	}
	template<class RandomIterator, class Distance, class T, class Comp>
	inline void __pop_heap_aux(RandomIterator _itBegin, RandomIterator _itEnd, Distance*, Comp _cmp) {
		__pop_heap(_itBegin, static_cast<Distance>(0), static_cast<Distance>(_itEnd - _itBegin - 1),_cmp);
	}

	template<class RandomIterator, class Comp >
	inline void pop_heap(RandomIterator _itBegin, RandomIterator _itEnd, Comp _cmp) {
		__pop_heap_aux(_itBegin, _itEnd, distance_type(*_itBegin), _cmp);
	}
	
	//--------------------------------pair----------------------------------------------------------
    //pair的泛型编程可能需要改进
    //std::pair<int, int> a;//这一行代码用来翻看源码
	template<class T1,class T2>
	struct pair
	{
		//从struct的泛型编程可以一窥泛型编程的思想
		typedef T1  first_type;
		typedef T2  second_type;//首先是要提供给使用者萃取成员变量类型的接口，

		T1 first;
		T2 second;
		//----------------------------------构造函数--------------------------------------

		pair(const T1& _first, const T2& _second):first(_first),second(_second){}
        pair(const pair<T1, T2>& _p) {
            first = _p.first;
            second = _p.second;
        }
		pair(const T1&& _first, const T2&& _second) {
			first = LT::move(_first);
			second = LT::move(_second);
		}
		pair& operator=(const pair& _p) {
			first = _p.first;
			second = _p.second;
			return *this;
		}

		pair& operator=(const pair&& _p) {
			first = LT::move(_p.first);//注意默认是在LT命名域下，所以调用的是LT
			second = LT::move(_p.second);
			return *this;
		}

		
		void swap(pair& _p) {
			LT::swap(_p.first, first);
			LT::swap(_p.second, second);
		}


	};

	//pair的一系列辅助函数：
	
	template<class T1, class T2>
	pair<T1, T2>  make_pair( T1&& _first,  T2&& _second) {
		return pair<T1, T2>(LT::forward<T1>(_first),LT::forward<T2>(_second));
	}
	
	template<class T1, class T2>
	pair<T1, T2>  make_pair(T1& _first, T2& _second) {
		return pair<T1, T2>((_first), (_second));
	}

	//重载以下操作符 ==, !=, >, >=, <,<=
	template<class T1, class T2>
	pair<T1, T2>  operator==(const pair<T1,T2>& _lhs, const pair<T1,T2>& _rhs) {
		return _lhs.first == _rhs.first && _lhs.second == _rhs.second;
	}

	template<class T1, class T2>
	pair<T1, T2>  operator!=(const pair<T1, T2>& _lhs, const pair<T1, T2>& _rhs) {
		return _lhs.first != _rhs.first || _lhs.second != _rhs.second;
	}

	template<class T1, class T2>
	pair<T1, T2>  operator > (const pair<T1, T2>& _lhs, const pair<T1, T2>& _rhs) {
		return _lhs.first > _rhs.first ||(_lhs.first == _rhs.first && _lhs.second > _rhs.second);
	}

	template<class T1, class T2>
	pair<T1, T2>  operator>=(const pair<T1, T2>& _lhs, const pair<T1, T2>& _rhs) {
		return !(_lhs < _rhs);
	}

	template<class T1, class T2>
	pair<T1, T2>  operator<(const pair<T1, T2>& _lhs, const pair<T1, T2>& _rhs) {
		return _lhs.first < _rhs.first && _lhs.second < _rhs.second;
	}

	template<class T1, class T2>
	pair<T1, T2>  operator<=(const pair<T1, T2>& _lhs, const pair<T1, T2>& _rhs) {
		return !(_lhs > _rhs);
	}
    

    // 重载 swap
    template <class T1, class T2>
    void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs)
    {
        lhs.swap(rhs);
    }

    
}
