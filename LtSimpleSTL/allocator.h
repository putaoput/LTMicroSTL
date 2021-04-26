//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//该头文件负责大内存的分配
#include "construct.h"

namespace LT {
	//
	template <class T>
	class allocator
	{
	public://用来提取类型
		typedef T            value_type;
		typedef T*           pointer;
		typedef const T*     const_pointer;
		typedef T&           reference;
		typedef const T&     const_reference;
		typedef size_t       size_type;
		typedef ptrdiff_t    difference_type;

	public:
		static T* allocate();
		static T* allocate(size_type _n);

		static void deallocate(T* _ptr);
		static void deallocate(T* _ptr, size_type _n);

		static void construct(T* _ptr);
		static void construct(T* _ptr, const T& _value);
		static void construct(T* _ptr, T&& _value);

		template <class... Args>
		static void construct(T* _ptr, Args&& ..._args);

		static void destroy(T* _ptr);
		static void destroy(T* _first, T* _last);
	};

	template <class T>
	T* allocator<T>::allocate()
	{
		return static_cast<T*>(::operator new(sizeof(T)));//调用到全局函数
	}

	template <class T>
	T* allocator<T>::allocate(size_type _n)
	{
		if (!_n) { return nullptr; }//经过实践发现，如果new的大小为零，也是会返回一个不为空指针指向大小不为零的内存区域
		return static_cast<T*>(::operator new(_n * sizeof(T)));//调用到全局函数，只有这么调用new 才可以满足这种语法。
	}

	template <class T>
	void allocator<T>::deallocate(T* _ptr)
	{
		if (_ptr)
		{
			::operator delete(_ptr);
		}
	}

	template <class T>
	void allocator<T>::deallocate(T* _ptr, size_type /*size*/)
	{
		deallocate(_ptr);
	}

	template <class T>
	void allocator<T>::construct(T* _ptr)
	{
		LT::construct(_ptr);
	}

	template <class T>
	void allocator<T>::construct(T* _ptr, const T& _value)
	{
		LT::construct(_ptr, _value);
	}

	template <class T>
	void allocator<T>::construct(T* _ptr, T&& _value)
	{
		LT::construct(_ptr, LT::move(_value));
	}

	template <class T>
	template <class ...Args>
	void allocator<T>::construct(T* _ptr, Args&& ..._args)
	{
		LT::construct(_ptr, LT::forward<Args>(_args)...);
	}

	template <class T>
	void allocator<T>::destroy(T* _ptr)
	{
		LT::destroy(_ptr);
	}

	template <class T>
	void allocator<T>::destroy(T* _first, T* _last)
	{
		LT::destroy(_first, _last);
	}
}

