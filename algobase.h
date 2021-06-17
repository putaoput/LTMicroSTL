//@Author: Lin Tao
//@Email: putaopu@qq.com
#pragma once

//��ͷ�ļ�����ʵ�ֳ��������㷨��Ŀǰ�Ѿ�ʵ�ֵ��У�
//max,min,swap
//copy��fill,fill_n,copy_backward
//equal
//lexicographical_compare������һ���Զ���ѭ���߼��Ƚ��㷨lexicographical_loop_compare
#include "iterator.h"
#include "util.h"
#include "functional.h"
#include "type_traits.h"
#include "allocator.h"
#include <iostream>

namespace LT {
	//---------------------------------------------max,min��swap----------------------------------------
	//Ϊ�˽��ѭ������swap������utilͷ�ļ�����
	template <class T>
	const T& min(const T& _a, const T& _b) {
		return (_a < _b) ? _a : _b;
	}

	template <class T, class Compare>
	const T& min(const T& _a, const T& _b, Compare cmp) {
		return (cmp(_a, _b)) ? _a : _b;
	}

	template <class T>
	const T& max(const T& _a, const T& _b) {
		return (_a > _b) ? _a : _b;
	}

	template <class T, class Compare>
	const T& max(const T& _a, const T& _b, Compare cmp) {
		return (cmp(_a, _b)) ? _a : _b;
	}


	

	//----------------------------------�����ײ��ڴ�����ߵĸ߽׺���---------------------------------
	//copy,fill
	//-------------------------------------------copy-----------------------------------------------------
	//copy���ú��������������һ������������Խ���������[_first,end)�ڵ�Ԫ�ظ��Ƶ��������[result,result + (end - _first))��
	//��֤�ڶ�������������������㹻�Ŀռ䡣��Ҫǿ��Ч��
	//����ȡ����������
	
	//input_iterator�汾
	template<class InputItertor, class OutputIterator>
	inline OutputIterator __copy(InputItertor _first, InputItertor _end, OutputIterator _result, LT::input_iterator_tag) {
		for (; _first != _end; ++_first, ++_result) {
			*_result = *_first;
		}
		return _result;
	}
	//random_iterator�汾
	template<class RandomIterator, class OutputIterator, class Distance>
	inline OutputIterator __copy_d(RandomIterator _first, RandomIterator _end, OutputIterator _result, Distance*) {
		//��n������ѭ���������ٶȸ��졣
		for (Distance n = _end - _first; n; --n, ++_result, ++_first) {
			*_result = *_first;
		}
		return _result;
	}
	template<class RandomItertor, class OutputIterator>
	inline OutputIterator __copy(RandomItertor _first, RandomItertor _end, OutputIterator _result, LT::random_access_iterator_tag) {
		for (; _first != _end; ++_first, ++_result) {
			*_result = *_first;
		}
		return _result;
	}
	//ԭ��ָ��汾
	template<class T>
	inline T* __copy_t(const T* _first, const T* _end, T* _result, true_type) {
		std::memmove(_result, _first, sizeof(T) * (_end - _first));
		return _result + (_end - _first);
	}

	template<class T>
	inline T* __copy_t(const T* _first, const T* _end, T* _result, false_type) {
		return __copy_d(_first, _end, _result, (ptrdiff_t*)0);
	}
	//__copy_dispatch
	template<class InputIterator, class OutputIterator>
	inline OutputIterator __copy_dispatch(InputIterator _first, InputIterator _end, OutputIterator _result) {
		return __copy(_first, _end, _result, LT::iterator_category(_first));
	}

	template<class Tp,class Up>
	inline typename std::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
		std::is_trivially_copy_assignable<Up>::value,
		Up*>::type
	 __copy_dispatch(Tp* _first, Tp* _end, Up* _result) {
		typedef typename _type_traits<Tp>::has_trivial_assignment_operator is_true_type;
		return __copy_t(_first, _end, _result, is_true_type());
	}

	
	//copy����ӿ�
	template<class InputIterator, class OutputIterator>
	inline OutputIterator copy(InputIterator _itBegin, InputIterator _itEnd, OutputIterator _result) {
		return __copy_dispatch<InputIterator, OutputIterator>(_itBegin, _itEnd, _result);
	}

	//�������ذ汾
	inline char* copy(const char* _first, const char* _end, char* _result) {
		std::memmove(_result, _first, _end - _first);
		return _result + (_end - _first);
	}
	inline wchar_t* copy(const wchar_t* _first, const wchar_t* _end, wchar_t* _result) {
		std::memmove(_result, _first, _end - _first);
		return _result + (_end - _first);
	}


	//-------------------------------------------------------------fill_n--------------------------------------------------------
	//�ú����ӵ�������ʼ��λ�ã����n��Ԫ��
	template<class OutputIterator, class Size_t, class T>
	OutputIterator __fill_n(OutputIterator _first, Size_t _n, const T& _value) {
		for (; _n > 0; --_n, ++_first) {
			*_first = _value;
		}
		return _first;
	}

	// ���ֽڿ������ػ��汾
	template<class Tp, class Size_t, class Up>
	typename std::enable_if<
		std::is_integral<Tp>::_value && sizeof(Tp) == 1 && //is_integral<T>���T�Ƿ�����������
		!std::is_same<Tp, bool>::_value &&
		std::is_integral<Up>::_value && sizeof(Up) == 1,
		Tp*>::type
		__fill_n(Tp* _first, Size_t _n, Up _value)
	{
		if (_n > 0)
		{
			std::memset(_first, (unsigned char)_value, (size_t)(_n));
		}
		return _first + _n;
	}

	template <class OutputIterator, class Size_t, class T>
	OutputIterator fill_n(OutputIterator _first, Size_t _n, const T& _value) {
		return __fill_n(_first, _n, _value);
	}


	//--------------------------------------------------------fill:--------------------------------------------------------------
	//Ϊ�����е�Ԫ�������ֵ
	template <class ForwardIter, class T>
	void __fill(ForwardIter _first, ForwardIter _last, const T& _value, LT::forward_iterator_tag)
	{
		for (; _first != _last; ++_first)
		{
			*_first = _value;
		}
	}

	template <class RandomIter, class T>//֧���������˵���������ڴ�
	void __fill(RandomIter _first, RandomIter _end, const T& _value,LT::random_access_iterator_tag)
	{
		LT::fill_n(_first, _end - _first, _value);
	}

	template <class ForwardIter, class T>
	void fill(ForwardIter _first, ForwardIter _end, const T& _value)
	{
		__fill(_first, _end, _value, iterator_category(_first));
	}

//----------------------------------------------------- copy_backward------------------------------------------------
// �� [_first, _end)�����ڵ�Ԫ�ؿ����� [_endResult - (_end - _first), _endResult)��

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		__copy_backward_dispatch(BidirectionalIter1 _first, BidirectionalIter1 _end,
			BidirectionalIter2 _endResult, LT::bidirectional_iterator_tag)
	{
		while (_first != _end)
		{
			*--_endResult = *--_end;
		}
			
		return _endResult;
	}

	//  random_access_iterator_tag �汾
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		__copy_backward_dispatch(BidirectionalIter1 _first, BidirectionalIter1 _end,
			BidirectionalIter2 _endResult, LT::random_access_iterator_tag)
	{
		for (auto n = _end - _first; n > 0; --n)
			*--_endResult = *--_end;
		return _endResult;
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		__copy_backward(BidirectionalIter1 _first, BidirectionalIter1 _end,
			BidirectionalIter2 _endResult)
	{
		return __copy_backward_dispatch(_first, _end, _endResult,
			iterator_category(_first));
	}

	// Ϊ trivially_copy_assignable �����ṩ�ػ��汾
	template <class Tp, class Up>
	typename LT::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value&&
		std::is_trivially_copy_assignable<Up>::value,
		Up*>::type
		__copy_backward(Tp* _first, Tp* _end, Up* _endResult)
	{
		const auto n = static_cast<size_t>(_end - _first);
		if (n != 0)
		{
			_endResult -= n;
			std::memmove(_endResult, _first, n * sizeof(Up));
		}
		return _endResult;
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		copy_backward(BidirectionalIter1 _first, BidirectionalIter1 _end, BidirectionalIter2 _endResult)
	{
		return __copy_backward(_first, _end, _endResult);
	}

	//-----------------------------------------------move-------------------------------------------------------------
	//�������汾
	template<class InputIterator, class OutputIterator>
	OutputIterator __move_dispatch(InputIterator _first, InputIterator _end, OutputIterator _result, random_access_iterator_tag)
	{
		size_t n = LT::distance(_first, _end);
		for (; n; --n, ++_first, ++_result)
		{
			*_result = LT::move(*_first);
		}
		return _result;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator __move_dispatch(InputIterator _first, InputIterator _end, OutputIterator _result, forward_iterator_tag)
	{
		size_t n = LT::distance(_first, _end);
		for (; n; --n, ++_first, ++_result)
		{
			*_result = LT::move(*_first);
		}
		return _result;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator __move(InputIterator _first, InputIterator _end, OutputIterator _result)
	{
		return __move_dispatch(_first, _end, _result,LT::iterator_category(_first));
	}
	

	//ֱ�Ӱ�λ�����İ汾
	template<class Tp, class Up>
	typename LT::enable_if <
		std::is_same<typename std::remove_const<Tp>::type, Up>::value && 
		std::is_trivially_move_assignable<Tp>::value,
		Up*>::type
		__move(Tp* _first, Tp* _end, Up* _result)
	{
		const size_t n = static_cast<size_t>(_end - _first);
		n && std::memmove(_result, _first, n * sizeof(Tp));
		return _result + n;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator move(InputIterator _first, InputIterator _end, OutputIterator _result)
	{
		return __move(_first, _end, _result);
	}
	//-------------------------------------------------------move_backward()-----------------------------------------------
		//�������汾
	template<class InputIterator, class OutputIterator>
	OutputIterator __move_backward_dispatch(InputIterator _first, InputIterator _end, OutputIterator _endResult, random_access_iterator_tag)
	{
		size_t n = _end - _first;
		for (; n; --n)
		{
			*--_endResult = LT::move(*--_end);
		}
		return _endResult;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator __move_backward_dispatch(InputIterator _first, InputIterator _end, OutputIterator _endResult, forward_iterator_tag)
	{
		size_t n = LT::distance(_first, _end);
		for (; n; --n)
		{
			*--_endResult = LT::move(*--_end);
		}
		return _endResult;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator move_backward(InputIterator _first, InputIterator _end, OutputIterator _endResult)
	{
		return __move_backward_dispatch(_first, _end, _endResult, LT::iterator_category(_first));
	}



	//--------------------------------------------equal--------------------------------------------------
	//�ú�������Ƚ������������ָ�����������ϵ�Ԫ��ֵ�Ƿ���ȡ�
	//��������������ǲ�ͬ���ͣ����ǵ�������value_typeҪ��ȡ�
	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 _first1, InputIterator1 _end, InputIterator2 _first2) {
		for (; _first1 != _end; ++_first1, ++_first2) {
			if (*_first1 != *_first2) {
				return false;
			}
		}
		return true;
	}

	template <typename InputIterator1, typename InputIterator2, typename Comp>
	bool equal(InputIterator1 _first1, InputIterator1 _end, InputIterator2 _first2, Comp _cmp) {
		for (; _first1 != _end; ++_first1, ++_first2) {
			if (!_cmp(*_first1  *_first2)) {
				return false;
			}
		}
		return true;
	}

	//-------------------------------------lexicographical_compare-----------------------------------
	//�ú������ֵ�����бȽϣ����������һ�������ϸ�����ǰ����ͬ������£������бȳ�����С
	template<typename InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 _first1, InputIterator1 _end1, InputIterator2 _first2, InputIterator2 _end2) {
		for (; _first1 != _end1 && _first2 != _end2; ++_first1,++_first2) {
			if (*_first1 < *_first2) {
				return true;
			}
			if (*_first2 < *_first1) {
				return false;
			}
		}
		return _first1 == _end1 && _first2 != _end2;
	}

	//�Զ���Ƚϰ汾
	template<typename InputIterator1, typename InputIterator2, typename Comp>
	bool lexicographical_compare(InputIterator1 _first1, InputIterator1 _end1, InputIterator2 _first2, InputIterator2 _end2, Comp _cmp) {
		for (; _first1 != _end1 && _first2 != _end2; ++_first1, ++_first2) {
			if (_cmp(*_first1 , *_first2)) {
				return true;
			}
			if (_cmp(*_first2, *_first1)) {
				return false;
			}
		}
		return _first1 == _end1 && _first2 != _end2;
	}

	//�����ػ��汾,����ַ���
	// ��� const char* ���ػ��汾
	/*
	template<>
	bool lexicographical_compare<const char*, const char*>(const  char* _first1, const  char* _last1, const  char* _first2, const char* _last2)
	{
		const auto len1 = _last1 - _first1;
		const auto len2 = _last2 - _first2;
		// �ȱȽ���ͬ���ȵĲ���
		const auto result = memcmp(_first1, _first2, LT::min(len1, len2));
		// ����ȣ����Ƚϳ��ıȽϴ�
		return result != 0 ? result < 0 : len1 < len2;
	}

	// ��� const unsigned char* ���ػ��汾
	template<>
	bool lexicographical_compare<const unsigned char*, const unsigned char*>(const unsigned char* _first1, const unsigned char* _last1, const unsigned char* _first2, const unsigned char* _last2)
	{
		const auto len1 = _last1 - _first1;
		const auto len2 = _last2 - _first2;
		// �ȱȽ���ͬ���ȵĲ���
		const auto result = memcmp(_first1, _first2, LT::min(len1, len2));
		// ����ȣ����Ƚϳ��ıȽϴ�
		return result != 0 ? result < 0 : len1 < len2;
	}
	*/
	/*
	//-------------------------------------lexicographical_loop_compare-----------------------------------
	//�ú������ֵ�����бȽϣ����������һ�������ϸ�����ǰ����ͬ������£������бȳ�����С
	template<typename InputIterator1, class InputIterator2>
	bool lexicographical_loop_compare(InputIterator1 _first1, InputIterator1 _end1, InputIterator2 _first2, InputIterator2 _end2) {
		for (; _first1 != _end1 && _first2 != _end2; ++_first1, ++_first2) {
			if (*_first1 < *_first2) {
				return true;
			}
			if (*_first2 < *_first1) {
				return false;
			}
		}
		return _first1 == _end1 && _first2 != _end2;
	}

	//�Զ���Ƚϰ汾
	template<typename InputIterator1, typename InputIterator2, typename Comp>
	bool lexicographical_loop_compare(InputIterator1 _first1, InputIterator1 _end1, InputIterator2 _first2, InputIterator2 _end2, Comp _cmp) {
		for (; _first1 != _end1 && _first2 != _end2; ++_first1, ++_first2) {
			if (_cmp(*_first1, *_first2)) {
				return true;
			}
			if (_cmp(*_first2, *_first1)) {
				return false;
			}
		}
		return _first1 == _end1 && _first2 != _end2;
	}

	//�����ػ��汾,����ַ���
	// ��� const char* ���ػ��汾

	bool lexicographical_loop_compare(const  char* _first1, const  char* _last1, const  char* _first2, const char* _last2)
	{
		const auto len1 = _last1 - _first1;
		const auto len2 = _last2 - _first2;
		// �ȱȽ���ͬ���ȵĲ���
		const auto result = std::memcmp(_first1, _first2, LT::min(len1, len2));
		// ����ȣ����Ƚϳ��ıȽϴ�
		return result != 0 ? result < 0 : len1 < len2;
	}

	// ��� const unsigned char* ���ػ��汾
	bool lexicographical_loop_compare(const unsigned char* _first1, const unsigned char* _last1, const unsigned char* _first2, const unsigned char* _last2)
	{
		const auto len1 = _last1 - _first1;
		const auto len2 = _last2 - _first2;
		// �ȱȽ���ͬ���ȵĲ���
		const auto result = std::memcmp(_first1, _first2, LT::min(len1, len2));
		// ����ȣ����Ƚϳ��ıȽϴ�
		return result != 0 ? result < 0 : len1 < len2;
	}
	*/
}
