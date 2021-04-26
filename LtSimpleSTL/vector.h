#pragma once

#include "memory.h"
#include "iterator.h"
#include "type_traits.h"
#include "allocator.h"


//该文件负责提供vector
namespace LT {
	template<typename T, class Alloc = allocator<T>>
	class vector {
		//先定义一些类型
	public:
		typedef T									value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef reverse_iterator<T*>				reverse_iterator;
		typedef reverse_iterator<const T*>			const_reverse_iterator;
		typedef iterator<T*>						iterator;
		typedef iterator<const T*>					const_iterator;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t								size_type;
		typedef ptrdiff_t							difference_type;

		//定义vector内部的三个重要的指针
	private:
		iterator start_;
		iterator finish_;
		iterator endOfStorage_;

	public:
		//写一些构造函数
		vector() :start_(0), finish_(0), endOfStorage_(0) {}

		explicit vector(const size_type _n) {
			fill_initialize(_n, T());
		}

		vector(const size_type _n, const value_type& _value) {
			fill_initialize(_n, _value);
		}

		template<typename InputIterator>
		vector(InputIterator _first, InputIterator _end) {

		}

		vector(const vector& _v) {

		}

		vector(const vector&& _v) {

		}

		vector& operator=(const vector& _v) {}

		vector& operator=(const vector&& _v) {}

		//------------------------------------------------------------这一组是公共接口，对外的api----------------------------------------------
	public:
		iterator begin() { return start_; }
		iterator end() { return finish_; }
		size_type size() { return size_type(finish_ - start_); }
		size_type capacity()const { return size_type(endOfStorage_ - start_); }
		bool empty()const { return start_ == finish_; }
		reference operator[](size_type _n) { return *(start_ + _n); }
		reference front() { return *start_; }
		reference back() { return *(finish_ - 1); }
		void pop_back() { destroy(finish_--); }
		void resize(size_type _newSize) { resize(_newSize, T()); }
		void clear(){erase(begin(), end())};

		void resize(size_type _newSize, const T& _value){}
		void push_back(const T& _val) {}
		iterator erase(iterator _pos) {
			if (_pos + 1 != end()) {
				copy(_pos + 1, finish_, _pos);
			}
			return _pos;
		}

	//空间配置函数
	protected:
		iterator allocate_and_fill(size_type _n, const T& _value) {

		}
	};
}