//@Author: Lin Tao
//@Email: putaopu@qq.com
#pragma once
#include "iterator.h"


//��ͷ�ļ�����ʵ�ֱ�׼���㷨�е������㷨��Ŀǰ�Ѿ�ʵ�ֵ���
//���ֲ���lower_bound��upper_bound, binary_serch

namespace LT {
	//****************************************���ֲ���*******************************************************
	
	//---------------------------------------------------------------------lower_bound------------------------------------
   // lower_bound
// ��[_first, _end)�в��ҵ�һ����С�� _value ��Ԫ�أ�������ָ�����ĵ���������û���򷵻� _end
/*****************************************************************************************/
// __lower_bound �� forward_iterator_tag �汾
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

    // __lower_bound �� random_access_iterator_tag �汾
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

    // �Զ���ȽϺ����İ汾
    // __lower_bound �� forward_iterator_tag �汾
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

    // __lower_bound �� random_access_iterator_tag �汾
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


