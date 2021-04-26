//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//该头文件提供迭代器
#include <cstddef>
#include "type_traits.h"

namespace LT {
	//迭代器分为只读，只写，前向，双向，随机访问五种类型
	struct input_iterator {};
	struct ouput_iterator{};
	struct forward_iterator: public input_iterator,ouput_iterator{};
	struct bidirectional_iterator: public forward_iterator{};
	struct random_iterator: public bidirectional_iterator{};

	//迭代器有五种型别,当继承该模板之后，就可以自动获得这一迭代器的五种类型,忘记继承该迭代器会出现问题
	template <class C, class V, class D = ptrdiff_t, class P = V*, class R = V&>
	struct iterator {
		typedef C                            iterator_category;
		typedef V                            value_type;
		typedef P                            pointer;
		typedef R                            reference;
		typedef D                            difference_type;
	};

	//（榨汁机）,typedef都是编译期完成，所以无需担心其带来的运行性能损失
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category		iterator_category;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::pointer				    pointer;
		typedef typename Iterator::reference				reference;
		typedef typename Iterator::difference_type			difference_type;
	};
	//
	//针对原生指针的偏特化版本
	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_iterator						 iterator_category;
		typedef T                                    value_type;
		typedef T*									 pointer;
		typedef T&									 reference;
		typedef ptrdiff_t                            difference_type;
	};

	//针对原生cosnt 指针的偏特化版本
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_iterator						 iterator_category;
		typedef T                                    value_type;
		typedef T*									 pointer;
		typedef T&									 reference;
		typedef ptrdiff_t                            difference_type;
	};

	//用于确定迭代器的类型
	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category //此处typename用于标明内嵌依赖类型名
		iterator_category(const Iterator&) {
			typedef typename iterator_traits<Iterator>::iterator_category category;
			return category();
	}

	// 用于确定迭代器的 distance_type
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type*
		distance_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	// 用于确定迭代器的 value_type
	template <class Iterator>
	typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//-----------------------------------------distance函数----------------------------------
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		__distance(InputIterator _first, InputIterator _last, input_iterator)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (_first != _last)
		{
			++_first;
			++n;
		}
		return n;
	}

	// distance 的 random_access_iterator 的版本
	template <class RandomIter>
	typename iterator_traits<RandomIter>::difference_type
		__distance(RandomIter _first, RandomIter _last,
			random_iterator)
	{
		return _last - _first;
	}

	// distance函数
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator _first, InputIterator _last,InputIterator)
	{
		return __distance(_first, _last, iterator_category(_first));
	}


	//---------------------------------------移动函数-------------------------------------------------
	//迭代器的移动函数，前进n个距离
	template <class InputIterator, class Distance>
	inline void __advance(InputIterator& _it, Distance _n, input_iterator) {
		while (--_n) {
			++_it;
		}
	}

	template <class BidirectionalIterator, class Distance>
	inline void __advance(BidirectionalIterator& _it, Distance _n, bidirectional_iterator) {
		if (_n >= 0) {
			while (--_n) {
				++_it;
			}
		}
		else {
			while (++_n) {
				--_it;
			}
		}
	}

	template <class RandomAcessIterator, class Distance>
	inline void __advance(RandomAcessIterator& _it, Distance _n, random_iterator) {
		_it += _n;
	}

	template <class InputIterator, class Distance>
	inline void advance(InputIterator& _it, Distance _n) {
		__advance(_it, _n, iterator_category(_it));
	}

	//----------------------------------------反向迭代器------------------------------------------------
	template <class Iterator>
	class reverse_iterator 
	{
	private:
		Iterator cur;
	public:
		// 反向迭代器的五种相应型别
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type        value_type;
		typedef typename iterator_traits<Iterator>::difference_type   difference_type;
		typedef typename iterator_traits<Iterator>::pointer           pointer;
		typedef typename iterator_traits<Iterator>::reference         reference;

		typedef Iterator											  F_Iterator;
		typedef reverse_iterator<Iterator>							  R_Iterator;

	public:
		reverse_iterator(){}
		explicit reverse_iterator(F_Iterator _it) :cur(_it) {};
		//拷贝构造函数
		reverse_iterator(const R_Iterator& __rhs) :cur(__rhs.cur) {};

	public:
		//取出正向迭代器
		F_Iterator get_cur()const {
			return cur;
		}

		//重载操作符 //!!!!注意!!!!
		reference operator*() const {
			return *cur;
		}

		pointer operator->()const {
			return cur;
		}

		//移动操作符----------------------------------------------------------------------------
		R_Iterator& operator++() {
			--cur;
			return *this;
		}

		R_Iterator& operator--() {
			++cur;
			return *this;
		}

		R_Iterator& operator++(int) {
			R_Iterator tmp = *this;
			--cur;
			return tmp;
		}

		R_Iterator& operator--(int) {
			R_Iterator tmp = *this;
			++cur;
			return tmp;
		}

		//+,+=, -, -=, []
		R_Iterator& operator-=(difference_type _n) {
			cur += _n;
			return *this;
		}

		R_Iterator& operator-(difference_type _n) {
			return R_Iterator(cur + _n);
		}

		R_Iterator& operator+=(difference_type _n) {
			cur -= _n;
			return *this;
		}

		R_Iterator& operator+(difference_type _n) {
			return R_Iterator(cur - _n);
		}

		reference operator[](difference_type _n)const
		{
			return *(*this + _n);
		}
	};


	//----------------------------------------需要在外部重载的操作符-------------------------------------------------

	// 重载 operator-
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type
		operator-(const reverse_iterator<Iterator>& _lhs,
			const reverse_iterator<Iterator>& _rhs)
	{
		return _rhs.get_cur() - _lhs.get_cur();
	}

	// 重载比较操作符
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& _lhs,
		const reverse_iterator<Iterator>& _rhs)
	{
		return _lhs.get_cur() == _rhs.get_cur();
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& _lhs,
		const reverse_iterator<Iterator>& _rhs)
	{
		return _rhs.get_cur() < _lhs.get_cur();
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& _lhs,
		const reverse_iterator<Iterator>& _rhs)
	{
		return !(_lhs == _rhs);
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& _lhs,
		const reverse_iterator<Iterator>& _rhs)
	{
		return _rhs < _lhs;
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& _lhs,
		const reverse_iterator<Iterator>& _rhs)
	{
		return !(_rhs < _lhs);
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& _lhs,
		const reverse_iterator<Iterator>& _rhs)
	{
		return !(_lhs < _rhs);
	}

}
