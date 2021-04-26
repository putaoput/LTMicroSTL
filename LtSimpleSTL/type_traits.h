//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//这个头文件用于提取类型信息
//是第一个编写的头文件，

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
	//由于内嵌类型申明没法表示true和false，我们在这里定义结构体表示__true_type和__false_type。
	//缺省情况下, 这些特性都依照最保守的值, 接下来再依据详细的情况, 利用模版特化, 
	//对详细的类型设定更加乐观的值.比方内置int类型的定义模版特化:


	//-------------------------------萃取类型----------------------------------------
	template<class T>
	struct _type_traits
	{
		typedef __false_type		has_trivial_default_counstructor;
		typedef __false_type		has_trivial_copy_constructor;
		typedef __false_type		has_trivial_assignment_operator;
		typedef __false_type		has_trivial_destructor;
		typedef __false_type		is_POD_type;//基本数据类型
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
	struct _type_traits<wchar_t> //wchar_t是C/C++的字符类型，是一种扩展的存储方式。wchar_t类型主要用在国际化程序的实现中，但它不等同于unicode编码。unicode编码的字符一般以wchar_t类型存储
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


	//------------------------------指针------------------------------
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