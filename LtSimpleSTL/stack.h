//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//��ͷ�ļ��ṩ�����stack
#include "deque.h"
namespace LT {
	template<class T, class Sequence = deque<T>>
	class stack {
	public:
		//��������һЩ��������
		typedef typename Sequence::value_type						  value_type;
		typedef typename Sequence::reference						  reference;
		typedef typename Sequence::size_type						  size_type;
		typedef typename Sequence::const_reference                    const_reference;

		typedef stack<T>											  self;
	protected:
		Sequence container_;
	public:
		//------------------------------------------���������ຯ��------------------------------------
		stack() = default;
		explicit stack(size_type _n) :container_(_n) {}
		stack(size_type _n, value_type& _value) :container_(_n, _value) {};
		template<class InputIterator>
		stack(InputIterator _first, InputIterator _end) :container_(_first, _end) {}
		stack(std::initializer_list<T> _ilist) :container_(_ilist.begin(), _ilist.end()) {}
		stack(stack& _rhs) :container_(_rhs.container_) {}
		stack(const stack& _rhs) :container_(_rhs.container_) {}
		stack(stack&& _rhs) :container_(LT::move(_rhs.container_)) {}
		stack operator=(const stack& _rhs) { container_ = _rhs.container_; return *this; }
		stack operator=(stack&& _rhs) { container_ = LT::move(_rhs.container_); }
		~stack() = default;

		//-------------------------------------------����ӿ�-------------------------------------------

		reference top() { return container_.back(); }
		const_reference top() const { return container_.back(); }

		bool      empty() const { return container_.empty(); }
		size_type size()  const { return container_.size(); }
		void clear() { container_.clear(); }
		//Ԫ���޸�
		void push(const value_type& _value) { container_.push_back(_value); }
		void push(value_type&& value) { container_.emplace_back(LT::move(value)); }
		void pop() { container_.pop_back(); }

		//----------------------------------------------------���رȽϲ�����---------------------------------------------------------
		bool operator==(const stack& _rhs) { return _rhs.container_ == container_; }
		bool operator!=(const stack& _rhs) { return _rhs.container_ != container_; }
		bool operator>(const stack& _rhs) { return _rhs.container_ > container_; }
		bool operator>=(const stack& _rhs) { return _rhs.container_ >= container_; }
		bool operator<(const stack& _rhs) { return _rhs.container_ < container_; }
		bool operator<=(const stack& _rhs) { return _rhs.container_ <= container_; }

	};
}