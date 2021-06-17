//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
#include <cstddef>
#include "type_traits.h"
#include "iterator.h"
//��ͷ�ļ�����ʵ��һЩ����ı�׼�⹦��.��Ҫ��
//move�� forward��swap,iter_swap, �ѵĸ���������pair����غ���.

namespace LT {
	

	//----------------------------------��ֵ----------------------------------------------
		//forward������c++11�������ԣ�Ҳ��һ����׼����ĺ�����
		//Ϊ����ʹ����ֵ���ò����ĺ���ģ���н������������ת������
		//std::forward<T>(u)������������T �� u����TΪ��ֵ��������ʱ��u����ת��ΪT���͵���ֵ������u����ת��ΪT������ֵ��
		//std::move����������תΪ��ֵ���ã���std::forward����������תΪ��ֵ����
	template <class T>
	typename std::remove_reference<T>::type&& move(T&& _args) noexcept
	{
		return static_cast<typename std::remove_reference<T>::type&&>(_args);
	}


	// forward

	template <class T>
	T&& forward(typename std::remove_reference<T>::type& _args) noexcept//���߱����������׳��쳣
	{
		return static_cast<T&&>(_args);
	}

	template <class T>
	T&& forward(typename std::remove_reference<T>::type&& _args) noexcept
	{
		//is_lvalue_reference�����ֵ�Ƿ�Ϊ�ο�����
		static_assert(!std::is_lvalue_reference<T>::value, "template argument"
			" substituting T is an lvalue reference type");
		return static_cast<T&&>(_args);
	}




	//-----------------------------------------swap-----------------------------------------------------
	//swap��������������Ҫ�ջ�ԭ��c++������ʹ����ֵ�����ٽ����ģ���������Դ����

	template<class T>
	inline void swap(T& _lhs, T& _rhs) {
		T tmp = LT::move(_lhs);							//���T&& tmp���ƶ�ʧ�ܣ���Ϊ��ʱtmp��ʱ��Ȼ��һ����ֵ���á�Ȼ�����ֵ�����ֵa����ͬһ���ڴ�
		_lhs = LT::move(_rhs);
		_rhs = LT::move(tmp);
	}
	//int�͵�swapʹ��λ����

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

	//���������ڶ������������������
	template <class Tp, size_t _N>
	inline void swap(Tp(&_a)[_N], Tp(&_b)[_N])
	{
		LT::swap_range(_a, _a + _N, _b);
	}
	//��������swap����
	template <class ForwardIterator>
	inline void iter_swap(ForwardIterator _itA, ForwardIterator _itB) {
		LT::swap(*_itA, *_itB);
	}
	//--------------------------------------�ѵ���ظ�������------------------------------------
	template<class RandomIterator,class Distance,  class Comp>//�ú����������µ�����
	void __adjust(RandomIterator _itBegin, Distance _index, Distance _len, Comp _cmp) {
		int left = 2 * _index + 1;//�����ӽڵ�
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
	//�ú����ṩ��βѹ��һ��Ԫ��֮������ѡ��������ϵ�����
	template<class RandomIterator, class Distance, class T, class Comp>
	inline void __push_heap(RandomIterator _itBegin, Distance _holeIndex, Distance _topIndex, T _value, Comp _cmp) {
		//�ú�����ʵ��ִ��push_heap�ѵ����ĺ���
		Distance parent = (_holeIndex - 1) / 2; //holeIndex��ѹ���Ԫ�أ��ҳ���Ԫ�صĸ��ڵ㣬Ȼ���е�����
		while (_holeIndex < _topIndex && _cmp(*(_itBegin + parent), _value))//˵����Ҫ������������_cmp(child,parent) == true;
		{
			*(_itBegin + _holeIndex) = *(_itBegin + parent);
			_holeIndex = parent;
			parent = (_holeIndex - 1) / 2 ;
		}
		*(_itBegin + _holeIndex) = _value;//������ɡ�
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
	//�ú����ṩpopһ��Ԫ��֮�󣬶Զѵĵ�������������
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
    //pair�ķ��ͱ�̿�����Ҫ�Ľ�
    //std::pair<int, int> a;//��һ�д�����������Դ��
	template<class T1,class T2>
	struct pair
	{
		//��struct�ķ��ͱ�̿���һ�����ͱ�̵�˼��
		typedef T1  first_type;
		typedef T2  second_type;//������Ҫ�ṩ��ʹ������ȡ��Ա�������͵Ľӿڣ�

		T1 first;
		T2 second;
		//----------------------------------���캯��--------------------------------------

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
			first = LT::move(_p.first);//ע��Ĭ������LT�������£����Ե��õ���LT
			second = LT::move(_p.second);
			return *this;
		}

		
		void swap(pair& _p) {
			LT::swap(_p.first, first);
			LT::swap(_p.second, second);
		}


	};

	//pair��һϵ�и���������
	
	template<class T1, class T2>
	pair<T1, T2>  make_pair( T1&& _first,  T2&& _second) {
		return pair<T1, T2>(LT::forward<T1>(_first),LT::forward<T2>(_second));
	}
	
	template<class T1, class T2>
	pair<T1, T2>  make_pair(T1& _first, T2& _second) {
		return pair<T1, T2>((_first), (_second));
	}

	//�������²����� ==, !=, >, >=, <,<=
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
    

    // ���� swap
    template <class T1, class T2>
    void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs)
    {
        lhs.swap(rhs);
    }

    
}
