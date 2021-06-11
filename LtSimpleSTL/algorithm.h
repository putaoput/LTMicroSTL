//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//该头文件负责实现常见算法，
#include "iterator.h"
#include "util.h"
#include "functional.h"
#include "type_traits.h"
#include "allocator.h"
#include "algobase.h"
#include "stl_algo.h"

namespace LT {


	//-----------------------------------------排序算法-------------------------------------------
	//当元素数量小于等于16时，直接使用插入排序。否则使用三数中值分割的快速排序，当恶化时。转而使用堆排序

	//①使用插入排序的原因：在冒泡，选择，插入排序中，插入排序是最好的。
	//插入排序，冒泡是稳定排序，不需要额外空间，是原地排序最好为O(n),最坏为O(n2),平均为O(n2)。
	//选择排序是从未排序区间选择最小的放入排序区间末尾，时间复杂度最好，最坏，平均均为O(n2)
	//但是在核心代码上，插入排序只要一个赋值(移动)，但是冒泡排序需要三个（交换）
	template<class RandomIterator, class Comp>
	void __insert_sort(RandomIterator _first, RandomIterator _end, Comp _cmp) {
		auto n = _end - _first;
		for (auto it = ++_first; it != _end; ++it) {
			auto j = it;
			//把已经未排序的代码插入到已排序代码之中
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

	//②快排
	//三数中值分割
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

	//快排例程
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

	//堆排例程
	template<class RandomAcessIterator, class Comp>
	void __heap_sort(RandomAcessIterator _first, RandomAcessIterator _end, Comp _cmp) {
		int len = _end - _first;
		//先建立堆
		LT::__make_heap(_first,_end,_cmp);
		//排序
		for (int i = len - 1; i >= 0; --i) {
			iter_swap(_first, _first + i);
			LT::__adjust(_first, 0, i, _cmp);
		}
	}

	//排序的接口
	template<class RandomAcessIterator, class Comp>
	void sort(RandomAcessIterator _first, RandomAcessIterator _end,
		Comp _cmp = less<typename iterator_traits<RandomAcessIterator>::value_type>()) {
		//榨出迭代器的数据类型
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