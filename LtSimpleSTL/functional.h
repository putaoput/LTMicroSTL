//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//��ͷ�ļ��ṩ�º���
#include <cstddef>
#include "util.h"
namespace LT {
	//����һԪ�����Ĳ����ͱ�ͷ���ֵ�ͱ�
	template<class Arg, class Result>
	struct single_function {
		typedef Arg argument_type;
		typedef Result result_type;
	};

	//�����Ԫ�����Ĳ����ͱ�ͷ���ֵ�ͱ�
	template<class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 _first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	//----------------------------------------��������º���-------------------------------
	template<class T>
	struct plus:public binary_function<T,T,T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 + _arg2;
		}
	};

	template<class T>
	struct minus :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 - _arg2;
		}
	};

	template<class T>
	struct multiplies :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 * _arg2;
		}
	};

	template<class T>
	struct divides :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 / _arg2;
		}
	};

	template<class T>
	struct modulus :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 % _arg2;
		}
	};

	//----------------------------------------�Ƚ������----------------------------------
	template<class T>
	struct equal:public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 == _arg2;
		}
	};

	template<class T>
	struct not_equal :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 != _arg2;
		}
	};

	template<class T>
	struct greater :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 > _arg2;
		}
	};

	template<class T>
	struct less :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 < _arg2;
		}
	};

	template<class T>
	struct greater_and_equal :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 >= _arg2;
		}
	};

	template<class T>
	struct less_and_equal :public binary_function<T, T, T>
	{
		T operator()(const T& _arg1, const T& _arg2) {
			return _arg1 <= _arg2;
		}
	};

	//ȡ����
	template <class T>
	struct negate :public single_function<T, T>
	{
		T operator()(const T& _arg) const { return -_arg; }
	};

	//---------------------------------�߼������---------------------------------------------
	// ���������߼���
	template <class T>
	struct logical_and :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x && y; }
	};

	// ���������߼���
	template <class T>
	struct logical_or :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x || y; }
	};

	// ���������߼���
	template <class T>
	struct logical_not :public single_function<T, bool>
	{
		bool operator()(const T& x) const { return !x; }
	};

	//-----------------------------------------֤ͬ-----------------------------------------------
	//���Ԫ�����Ͳ�ͬ�������ֱ����ڴ���

	// �ӷ���֤ͬԪ��
	template <class T>
	T identity_element(plus<T>) { return T(0); }

	// �˷���֤ͬԪ��
	template <class T>
	T identity_element(multiplies<T>) { return T(1); }

	// ֤ͬ����������ı�Ԫ�أ����ر���
	template <class T>
	struct identity :public single_function<T, bool>
	{
		const T& operator()(const T& _arg) const { return _arg; }
	};

	//------------------------------------------Ͷ����ѡ����-------------------------------------------

	// ѡ����������һ�� pair�����ص�һ��Ԫ��
	template <class Pair>
	struct get_first :public single_function<Pair, typename Pair::_first_type>
	{
		const typename Pair::_first_type& operator()(const Pair& _arg) const
		{
			return _arg._first;
		}
	};

	// ѡ����������һ�� pair�����صڶ���Ԫ��
	template <class Pair>
	struct get_second :public single_function<Pair, typename Pair::_second_type>
	{
		const typename Pair::second_type& operator()(const Pair& _arg) const
		{
			return _arg.second;
		}
	};

	// Ͷ�亯�������ص�һ����
	template <class Arg1, class Arg2>
	struct project_first :public binary_function<Arg1, Arg2, Arg1>
	{
		Arg1 operator()(const Arg1& _arg, const Arg2&) const { return _arg; }
	};

	// Ͷ�亯�������صڶ�����
	template <class Arg1, class Arg2>
	struct project_second :public binary_function<Arg1, Arg2, Arg2>
	{
		Arg2 operator()(const Arg1&, const Arg2& _arg) const { return _arg; }
	};



}