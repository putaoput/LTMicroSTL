//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//��ͷ�ļ�����ʵ��uninitialized_copy(),uninitialized_fill_n(),uninitialized_fiil()�����ڴ������
//���������Ͳ�εĺ�����Ӧ�����߲�κ���:copy(),fill(),fill_n()��
//ʵ��������Ҫ�쳣�����
//Ҫ����лع����ܣ���commit or rollback��Ҫôȫ�����죬Ҫôһ��Ҳ������
//����POD���Ͳ������Ч�÷�ʽ�����ڷ�POD���Ͳ�����յķ�ʽ
#include "construct.h"
#include "iterator.h"
#include "type_traits.h"
#include "util.h"
#include <wchar.h>


namespace LT {
	
	//-------------------------------------------uninitialized_fiil_n()��ʵ��---------------------------------------------
	//�ú����Ľ����߼���������ȡ����������value_type��Ȼ���жϸ�value_type�Ƿ���POD�ͱ�
	template <typename ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator _first, Size _n, const T& _value) {
		return __uninitialized_fill(_first, _n, _value, value_type(_first));
		//������ȡ���ͣ�value_type��ȡ��������ʵ�Ǹ����͵�ָ�롣
	}

	template <typename ForwardIterator, class Size, class T, class Val_t>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator _first,Size _n, const T& _value, Val_t*) {
		typedef typename _type_traits<T>::is_POD_type is_POD //��һ������ȡ���Ƿ��ǻ����������ͣ������struct true_type ����false_type
			return __uninitialized_fill_n_aux(_first, _n, _value, is_POD());
		//��������__true_type ���� __false_type ���͵���ͬ��ģ�庯����
	}

	//__true_type����������ģ�庯��
	template <typename ForwardIterator, class Size, class T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator _first, Size _n, const T& _value, __true_type) {
		return fill_n(_first, _n, _value)//�������߽׵ĺ���ִ��
	}
	//__flase_type����������ģ�庯��
	template <typename ForwardIterator, class Size, class T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator _first, Size _n, const T& _value, __false_type) {
		ForwardIterator cur = _first;	
		try {
			for (; _n > 0; --n; ++cur) {
				construct(&*cur, _value);
			}
			return cur;
		}
		catch(...){
			//�˴�Ӧ�����쳣����,�Ա�֤commit or rollback��
			for (auto it = _first; cur != it; ++ it) {
				destroy(&*it);
			}
			return _first;
		}	
	}


	//-------------------------------------------uninitialized_copy()��ʵ��---------------------------------------------
	
	//�������ṩһ�鿽�������������һ����������ݿ�������һ������,���ؿ���������λ�õĵ�����
	template <typename InputIterator, class ForwardIterator>//������������
	inline ForwardIterator uninitialized_copy(InputIterator _first, InputIterator _end, ForwardIterator _result) {
		return __uninitialized_copy(_first, _end, _result, value_type(_result);//��ȡvalue_type
	}

	template <typename InputIterator, class ForwardIterator, class T>//�ֱ��Ƿ��ǻ�����������
	inline ForwardIterator __uninitialized_copy_aux(InputIterator _first, InputIterator _end, ForwardIterator _result, T*) {
		typedef typename _type_traits<T>::is_POD_type is_POD;
		return __uninitialized_copy_aux(_first, _end, _result, is_POD())
	}

	template <typename InputIterator, class ForwardIterator>//������������
	inline ForwardIterator __uninitialized_copy_aux(InputIterator _first, InputIterator _end, ForwardIterator _result, __true_type) {
		return copy(_first, _end, result);//���ɸ߽׺�������
	}

	template <typename InputIterator, class ForwardIterator>//�ǻ�����������
	inline ForwardIterator __uninitialized_copy_aux(InputIterator _first, InputIterator _end, ForwardIterator _result, __false_type) {
		InputIterator copyStart = _first;
		ForwardIterator cur = _result;
		try {
			for (; _n > 0; --n; ++cur) {
				construct(&*cur, *copyStart++);
			}
			return cur;
		}
		catch (...) {
			//�˴�Ӧ�����쳣����,�Ա�֤commit or rollback��
			for (auto it = _result; cur != it; ++it) {
				destroy(&*it);
			}
			return _result;
		}
	}

	//Ҫ��char* �� wchar_t*�ṩ��Ϊ��Ч���ػ��汾

	inline char* uninitialized_copy(const char* _first, const char* _end, char* _result) {
		memmove(_result, _first, _end - _first);
		return _result + (_end - _first);
	}

	inline wchar_t* uninitialized_copy(const wchar_t* _first, const wchar_t* _end, wchar_t* _result) {
		memmove(_result, _first, _end - _first);
		return _result + (_end - _first);
	}


	//-------------------------------------------uninitialized_fill()��ʵ��---------------------------------------------
	template <typename ForwardIterator, class T>
	inline void uninitialized_fill(ForwardIterator _first, ForwardIterator _end, const T& _value) {
		__uninitialized_fill(_first, _end, _value, value_type(_first));
	}

	template <typename ForwardIterator, class T, class T1>
	inline void __uninitialized_fill(ForwardIterator _first, ForwardIterator _end, const T& _value, T1*) {
		typedef typename _type_traits<T>::is_POD_type is_POD;
		__uninitialized_fill_aux(_first, _end, _value, is_POD());
	}

	template <typename ForwardIterator, class T>
	inline void __uninitialized_fill_aux(ForwardIterator _first, ForwardIterator _end, const T& _value, __true_type) {
		fill(_first, _end, _value);//����stl�㷨fill().
	}

	template <typename ForwardIterator, class T>
	inline void __uninitialized_fill_aux(ForwardIterator _first, ForwardIterator _end, const T& _value, __false_type) {
		ForwardIterator cur = _first;
		try {
			for (; cur != _end; ++cur) {
				construct(&*cur, _value);
			}
			return cur;
		}
		catch(...){
			//ʧ����Ҫ��������
			for (auto it = _first; cur != it; ++it) {
				destroy(&*it);
			}
			return _first;
		}
	}

}


