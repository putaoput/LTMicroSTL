//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//���ͷ�ļ�������ȡ������Ϣ
//�ǵ�һ����д��ͷ�ļ���

namespace LT
{
	namespace {
		template<bool,class Ta, class Tb>
		struct IfThenElse;
		template<class Ta, class Tb>
		struct IfThenElse <true, Ta, Tb> {
			using result = Ta;
		};
		template<class Ta, class Tb>
		struct IfThenElse<false, Ta, Tb> {
			using result = Tb;
		};
	}

	struct __true_type{};
	struct __false_type{};
	//������Ƕ��������û����ʾtrue��false�����������ﶨ��ṹ���ʾ__true_type��__false_type��
	//ȱʡ�����, ��Щ���Զ�������ص�ֵ, ��������������ϸ�����, ����ģ���ػ�, 
	//����ϸ�������趨�����ֹ۵�ֵ.�ȷ�����int���͵Ķ���ģ���ػ�:


	//-------------------------------��ȡ����----------------------------------------
	template<class T>
	struct _type_traits
	{
		typedef __false_type		has_trivial_default_counstructor;
		typedef __false_type		has_trivial_copy_constructor;
		typedef __false_type		has_trivial_assignment_operator;
		typedef __false_type		has_trivial_destructor;
		typedef __false_type		is_POD_type;//������������
	};

	template<>
	struct _type_traits<bool>
	{
		typedef __true_type		has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<char>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<unsigned char>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<signed char>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<wchar_t> //wchar_t��C/C++���ַ����ͣ���һ����չ�Ĵ洢��ʽ��wchar_t������Ҫ���ڹ��ʻ������ʵ���У���������ͬ��unicode���롣unicode������ַ�һ����wchar_t���ʹ洢
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<short>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<unsigned short>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<int>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<unsigned int>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<long>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<unsigned long>
	{
		typedef __true_type	    has_trivial_default_counstructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};

	template<>
	struct _type_traits<long long>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned long long>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<float>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<double>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<long double>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};


	//------------------------------ָ��------------------------------
	template<class T>
	struct _type_traits<T*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<class T>
	struct _type_traits<const T*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<char*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned char*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<signed char*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<const char*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<const unsigned char*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
	template<>
	struct _type_traits<const signed char*>
	{
		typedef __true_type		has_trivial_default_constructor;
		typedef __true_type		has_trivial_copy_constructor;
		typedef __true_type		has_trivial_assignment_operator;
		typedef __true_type		has_trivial_destructor;
		typedef __true_type		is_POD_type;
	};
}