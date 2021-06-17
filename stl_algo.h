//@Author: Lin Tao
//@Email: putaopu@qq.com
#pragma once
#include "iterator.h"


//该头文件负责实现标准库算法中的其他算法，目前已经实现的有
//二分查找lower_bound，upper_bound, binary_serch

namespace LT {
	//****************************************二分查找*******************************************************
	
	//---------------------------------------------------------------------lower_bound------------------------------------
   // lower_bound
// 在[_first, _end)中查找第一个不小于 _value 的元素，并返回指向它的迭代器，若没有则返回 _end
/*****************************************************************************************/
// __lower_bound 的 forward_iterator_tag 版本
    template <class ForwardIter, class T>
    ForwardIter __lower_bound(ForwardIter _first, ForwardIter _end, const T& _value, forward_iterator_tag)
    {
        auto len = LT::distance(_first, _end);
        auto half = len;
        ForwardIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = _first;
            LT::advance(middle, half);
            if (*middle < _value)
            {
                _first = middle;
                ++_first;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return _first;
    }

    // __lower_bound 的 random_access_iterator_tag 版本
    template <class RandomIter, class T>
    RandomIter __lower_bound(RandomIter _first, RandomIter _end,const T& _value, random_access_iterator_tag)
    {
        auto len = _end - _first;
        auto half = len;
        RandomIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = _first + half;
            if (*middle < _value)
            {
                _first = middle + 1;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return _first;
    }

    template <class ForwardIter, class T>
    ForwardIter lower_bound(ForwardIter _first, ForwardIter _end, const T& _value)
    {
        return __lower_bound(_first, _end, _value, iterator_category(_first));
    }

    // 自定义比较函数的版本
    // __lower_bound 的 forward_iterator_tag 版本
    template <class ForwardIter, class T, class Compared>
    ForwardIter  __lower_bound(ForwardIter _first, ForwardIter _end, const T& _value, forward_iterator_tag, Compared comp)
    {
        auto len = distance(_first, _end);
        auto half = len;
        ForwardIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = _first;
            advance(middle, half);
            if (comp(*middle, _value))
            {
                _first = middle;
                ++_first;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return _first;
    }

    // __lower_bound 的 random_access_iterator_tag 版本
    template <class RandomIter, class T, class Compared>
    RandomIter __lower_bound(RandomIter _first, RandomIter _end,const T& _value, random_access_iterator_tag, Compared comp)
    {
        auto len = _end - _first;
        auto half = len;
        RandomIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = _first + half;
            if (comp(*middle, _value))
            {
                _first = middle + 1;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return _first;
    }

    template <class ForwardIter, class T, class Compared>
    ForwardIter lower_bound(ForwardIter _first, ForwardIter _end, const T& _value, Compared comp)
    {
        return __lower_bound(_first, _end, _value, iterator_category(_first), comp);
    }



}


