//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//��ͷ�ļ�����ʵ�ֳ����㷨��
#include "iterator.h"
#include "util.h"
#include "functional.h"
#include "type_traits.h"
#include "allocator.h"
#include "algobase.h"
#include "stl_algo.h"

namespace LT {


	//-----------------------------------------�����㷨-------------------------------------------
	//��Ԫ������С�ڵ���16ʱ��ֱ��ʹ�ò������򡣷���ʹ��������ֵ�ָ�Ŀ������򣬵���ʱ��ת��ʹ�ö�����

	//��ʹ�ò��������ԭ����ð�ݣ�ѡ�񣬲��������У�������������õġ�
	//��������ð�����ȶ����򣬲���Ҫ����ռ䣬��ԭ���������ΪO(n),�ΪO(n2),ƽ��ΪO(n2)��
	//ѡ�������Ǵ�δ��������ѡ����С�ķ�����������ĩβ��ʱ�临�Ӷ���ã����ƽ����ΪO(n2)
	//�����ں��Ĵ����ϣ���������ֻҪһ����ֵ(�ƶ�)������ð��������Ҫ������������
	template<class RandomIterator, class Comp>
	void __insert_sort(RandomIterator _first, RandomIterator _end, Comp _cmp) {
		auto n = _end - _first;
		for (auto it = ++_first; it != _end; ++it) {
			auto j = it;
			//���Ѿ�δ����Ĵ�����뵽���������֮��
			for (; j != _first;) {
				if (_cmp(*it, *(--j))) {
					*j = *(j + 1);
				}
				else {
					break;
				}
			}
			*j = *it;
		}
	}

	//�ڿ���
	//������ֵ�ָ�
	template<class RandomAcessIterator>
	RandomAcessIterator __mid3(RandomAcessIterator _first, RandomAcessIterator _end) {
		auto mid = (_end - _first) / 2 + _first;
		auto _end = _end - 1;
		if (*_first > * mid) {
			LT::iter_swap(_first, mid);
		}
		if (*mid > * _end) {
			LT::iter_swap(_end, mid);
		}

		if (*mid < *_first) {
			LT::iter_swap(_first, mid);
		}

		return mid;
	}

	//��������
	template<class RandomAcessIterator,class Comp>
	void __quick_sort(RandomAcessIterator _first, RandomAcessIterator _end, Comp _cmp, int _n ,int _max) {
		int len = _end - _first;
		if (len <= 1) { return; }
		if (len <= 16) { return __insert_sort(_first, _end, _cmp); }
		if (_n >= _max) { return __heap_sort(_first, _end, _cmp); }

		auto left = _first;
		auto right = _end - 1;
		auto pivot = __mid3(_first, _end);
		while (true) {
			while (++left < right && _cmp(*left, *pivot)) {}
			while (--right < left && _cmp(*pivot, *right)) {}
			if (right - left >= 1) {
				iter_swap(left, right);
			}
			else {
				break;
			}
		}
		__quick_sort(_first, left, _cmp, _n + 1, _max);
		__quick_sort(left + 1, _end, _cmp, _n + 1, _max);
	}

	//��������
	template<class RandomAcessIterator, class Comp>
	void __heap_sort(RandomAcessIterator _first, RandomAcessIterator _end, Comp _cmp) {
		int len = _end - _first;
		//�Ƚ�����
		LT::__make_heap(_first,_end,_cmp);
		//����
		for (int i = len - 1; i >= 0; --i) {
			iter_swap(_first, _first + i);
			LT::__adjust(_first, 0, i, _cmp);
		}
	}

	//����Ľӿ�
	template<class RandomAcessIterator, class Comp>
	void sort(RandomAcessIterator _first, RandomAcessIterator _end,
		Comp _cmp = less<typename iterator_traits<RandomAcessIterator>::value_type>()) {
		//ե������������������
		int n = _end - _first;
		if (n > 1 && n <= 16) {
			return __insert_sort(_first, _end, _cmp);
		}
		if (n > 16) {
			int _max = log(n)/log(2);
			return __quick_sort(_first, _end, _cmp, 0, _max);
		}
	}

	template<class RandomAcessIterator>
	void sort(RandomAcessIterator _first, RandomAcessIterator _end) {
		LT::sort(_first, _end, less<typename iterator_traits<RandomAcessIterator>::value_type>());
	}
}