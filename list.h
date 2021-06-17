//@Author: Lin Tao
//@Email: putaopu@qq.com


#pragma once
//��ͷ�ļ��ṩ����ʽ����list��
#include "iterator.h"
#include "allocator.h"
#include "memory.h"
#include "algobase.h"
#include "assert.h"
#include "memory.h"

namespace LT {
	///**************************************************************************************************************
	//----------------------------------------------list�Ľ��-------------------------------------------------------
	//�����һ��list�Ľ��
	template<class T>
	struct __list_node
	{
		typedef __list_node<T>*  node_pointer;
		node_pointer pre;
		node_pointer next;
		T			 data;
		__list_node() = default;//д��Щ���캯�����ٹ��죬������ֵ����
		__list_node(const T& _value) :data(_value){}
	};

	//**************************************************************************************************************
	//----------------------------------------------list�ĵ�����-------------------------------------------------------

	template<class T, class Ref, class Ptr>
	struct __list_iterator :public iterator<bidirectional_iterator_tag, T>
	{
		
		typedef typename iterator<bidirectional_iterator_tag,T>::iterator_category                             iterator_category;
		typedef T																							   value_type;
		typedef value_type*																					   pointer;
		typedef value_type&																				       reference;
		typedef typename iterator<bidirectional_iterator_tag, T>::difference_type			                           difference_type;
		
		typedef __list_node<T>*						 node_pointer;
		typedef __list_node<T>						 node;
		typedef size_t                               size_type;
		typedef __list_iterator<T, Ref, Ptr>	     self;
		typedef __list_iterator<T, T&, T*>			 iterator;
		

		//ָ��һ��list����ָ��
		node_pointer nodePtr_;


		//---------------------------------------����ϵ�к���------------------------------------------------------------------------
		__list_iterator() = default;	//���û�����Ĺ��캯������ʹ��ʲôҲ������ʹ�����Ͳ��Ǿۺϣ�Ҳ����΢������ġ������ϣ���������Ǿۺ����ͻ���ͨ���ͣ���ͨ�������ԣ�POD���ͣ�����ô��Ҫʹ�á�= default����
										//ʹ�á� = default��Ҳ�����븴�ƹ��캯������������һ��ʹ�á����磬�տ������캯����Ĭ�Ͽ������캯������ִ�����Ա�ĸ��Ƹ�������ͬ����ÿ�������Ա����ͳһʹ�á� = default���﷨ʹ����������Ķ���
		__list_iterator(const node_pointer& _nodePtr):nodePtr_(_nodePtr){}
		__list_iterator(const iterator& _rhs):nodePtr_(_rhs.nodePtr_){}
		__list_iterator(iterator&& _rhs) :nodePtr_(_rhs.nodePtr_) { _rhs.nodePtr_ = nullptr; }
		__list_iterator(const node& _node):nodePtr_(&_node){}
		self& operator=(const iterator& _rhs) {
			nodePtr_ = _rhs.nodePtr_;
			return *this;
		}
		self& operator=(iterator&& _rhs) {
			nodePtr_ = _rhs.nodePtr_;
			_rhs.nodePtr_ = nullptr;
			return *this;
		}
		~__list_iterator() = default;

		//--------------------------------------����ӿ�--------------------------------------------------------------------------------
		reference operator*() const
		{
			return nodePtr_->data; 
		}
		pointer operator->() const 
		{ 
			return &(operator*()); 
		}

		self& operator++()
		{
			nodePtr_ = nodePtr_->next;
			return *this;
		}
		self operator++(int)
		{
			self tmp = *this;
			++* this;
			return tmp;
		}
		self& operator--()
		{
			nodePtr_ = nodePtr_->pre;
			return *this;
		}
		self operator--(int)
		{
			self tmp = *this;
			--* this;
			return tmp;
		}

		bool operator==(const self& rhs) const 
		{ 
			return nodePtr_ == rhs.nodePtr_;
		}

		bool operator!=(const self& rhs) const
		{ 
			return nodePtr_ != rhs.nodePtr_;
		}

	};
	//*****************************************************************************************************************
	//---------------------------------------------------list-------------------------------------------------------
	template <class T, class Alloc = allocator<T>>
	class list {
	public:
		//�����ȶ���һ��
		typedef T													value_type;
		typedef value_type*											pointer;
		typedef value_type&											reference;
		typedef size_t												size_type;
		typedef __list_iterator<T, T*, T&>							iterator;
		typedef __list_iterator<T, const T*, const T&>				const_iterator;
		typedef __list_node<T>										list_node;
		typedef list_node*											list_node_pointer;
		typedef LT::reverse_iterator<iterator>						reverse_iterator;
		typedef LT::reverse_iterator<const_iterator>				const_reverse_iterator;

		//��������
	protected:
		list_node_pointer nodePtr_;//���ָ��ָ��listĩβ��һ���ս�㡣ͨ�����ָ������ʾ������״����
		
		//***************************************************************************************************************************
		//***************************************************����ӿ�****************************************************************
		//***************************************************************************************************************************
	public:
		//���캯��
		list() { __init(); };
		explicit list(size_type _n) { __init(_n, T()); }
		list(size_type _n, const value_type& _value) { __init(_n, _value); }
		template<class InputIter,
				typename std::enable_if<LT::is_input_iterator<InputIter>::value>::type>
		list(InputIter _itBeign, InputIter _itEnd) { __init(_itBeign, _itEnd); }
		list(std::initializer_list<T> _ilist) { __init(_ilist.begin(), _ilist.end()); }
		list(const list& _rhs) { __init(_rhs.begin(), _rhs.end()); }
		list(list&& _rhs) :nodePtr_(_rhs.nodePtr_) { _rhs.nodePtr_ = nullptr; }
		list& operator=(const list& _rhs) { assign(_rhs.begin(), _rhs.end()); return *this; }
		list& operator=(list&& _rhs) { 
			clear();
			splice(end(), _rhs);
			return *this; 
		}
		list& operator=(std::initializer_list<T> _ilist) {
			list tmp(_ilist.begin(), _ilist.end()); 
			swap(tmp); 
			return *this;
		}
		~list() {
			__uninit();
		}

		//------------------------------------------------------������----------------------------------------------------------------
		iterator begin() { return static_cast<iterator>(nodePtr_->next); }//��Ϊ�������ڲ�ֻ��һ��list_node_pointer,���Կ���ֱ�ӽ��о�̬����ת��
		const_iterator cbegin() { return static_cast<const_iterator>(nodePtr_->next); }
		iterator rbegin() { return reverse_iterator(end()); }//��Ϊ�������ڲ�ֻ��һ��list_node_pointer,���Կ���ֱ�ӽ��о�̬����ת��
		const_iterator crbegin() { return reverse_iterator(cend()); }

		iterator end() { return static_cast<iterator>(nodePtr_); }//��Ϊ�������ڲ�ֻ��һ��list_node_pointer,���Կ���ֱ�ӽ��о�̬����ת��
		const_iterator cend() { return static_cast<const_iterator>(nodePtr_); }
		iterator rend() { return reverse_iterator(begin()); }//��Ϊ�������ڲ�ֻ��һ��list_node_pointer,���Կ���ֱ�ӽ��о�̬����ת��
		const_iterator crend() { return reverse_iterator(cbegin()); }
		
		reference front() { assert(!empty()); return *begin(); }
		reference back() { assert(!empty()); return *(nodePtr_->pre); }


		//-----------------------------------------------------�������-------------------------------------------------------------
		size_type size() const{ return static_cast<size_type>(LT::distance(begin(), end())); }
		bool empty() const{ return nodePtr_->next == nodePtr_; }
		size_type max_size() const{return static_cast<size_type>(-1);}

		void resize(size_type _newSize){ __resize(_newSize, T()); }
		void resize(size_type _newSize, const value_type& _value) { __resize(_newSize, _value); }
		//----------------------------------------------------�ڵ����---------------------------------------------------------------
		void push_back(const value_type& _value) { insert(end(), _value); }
		void push_back(const value_type&& _value) { __emplace(end(), _value); }

		void push_front(const value_type& _value) { insert(begin(), _value); }
		void push_front(const value_type&& _value) { __emplace(begin(), _value); }

		template<class ...Args>
		void emplace(iterator _pos, Args&&... _value) { __emplace(_pos,LT::forward<Args>(_value)...); }
		template <class ...Args>
		void emplace_front(Args&& ..._args) { __emplace(end(), LT::forward<Args>(_args)...); }
		template<class ...Args>
		void emplace_back(Args&& ..._args) { __emplace(begin(), LT::forward<Args>(_args)...); }

		void assign(size_type _n, value_type& _value) { __assignN(_n, _value); }
		template<class InputIter,
				typename std::enable_if<LT::is_input_iterator<InputIter>::value, int>::type = 0 >
		void assign(InputIter _itBegin, InputIter _itEnd) { __assignIt(_itBegin, _itEnd); }
		void assign(std::initializer_list<T> _ilist) { __assignIt( _ilist.begin(), _ilist.end()); }
		iterator insert(iterator& _pos, const value_type& _value) {
			//insert���ز���Ԫ�صĵ�ַ
			auto preNode = _pos.nodePtr_->pre;
			auto newNode = __allocate_one_node_mem();
			__construct_one_node(newNode, _value, preNode, _pos.nodePtr_);
			preNode->next = newNode;
			_pos->pre = newNode;
			return static_cast<iterator> (newNode);
		}

		iterator insert(iterator& _pos, size_type _n, const value_type& _value) {
			auto preNode = _pos.nodePtr_->pre;
			
			list_node_pointer newNode (_pos.nodePtr_->pre);
			while (_n) {
				newNode = __allocate_one_node_mem();
				__construct_one_node(newNode, _value, preNode, _pos.nodePtr_);
				preNode->next = newNode;
				newNode->pre = preNode;
				preNode = newNode;	
				--_n;
			}
			newNode->next = _pos.nodePtr_;
			_pos.nodePtr ->pre = newNode;
			return newNode->next;
		}

		iterator insert(iterator& _pos, value_type&& _n) {
			list_node_pointer preNode = _pos.nodePtr_->pre;
			list_node_pointer newNode = __allocate_one_node_mem();//ʹ����ֵ���ð汾
			__construct_one_node(newNode, LT::move(_n), preNode, _pos.nodePtr_);
			preNode->next = newNode;
			_pos.nodePtr_->pre = newNode;
			return static_cast<iterator>(newNode);
		}

		template<class InputIterator,
				typename std::enable_if<LT::is_input_iterator<InputIterator>::value, int>::type = 0>
		iterator insert(iterator _pos, InputIterator _itBegin, InputIterator _itEnd) {
			auto preNode = _pos.nodePtr_->pre;

			list_node_pointer newNode(_pos.nodePtr_->pre);
			size_type n = LT::distance(_itBegin, _itEnd);
			while (n) {
				newNode = __allocate_one_node_mem();
				__construct_one_node(newNode, *_itBegin, preNode, _pos.nodePtr_);
				++_itBegin;
				preNode->next = newNode;
				newNode->pre = preNode;
				preNode = newNode;
				--n;
			}
			newNode->next = _pos.nodePtr_;
			_pos.nodePtr_->pre = newNode;
			return newNode->next;
		}

		iterator erase(iterator _pos) {
			assert(_pos != end());
			list_node_pointer preNode = _pos.nodePtr_->pre;
			list_node_pointer nextNode = _pos.nodePtr_->next;
			preNode->next = preNode;
			nextNode->pre = nextNode;
			__destroy_one_node(_pos.nodePtr_);
			__deallocate_one_node_mem(_pos.nodePtr_);
			return static_cast<iterator>(nextNode);
		}

		iterator erase(iterator _itBeg, iterator _itEnd) {
			list_node_pointer preNode = _itBeg.nodePtr_->pre;
			list_node_pointer nextNode = _itEnd.nodePtr_;
			preNode->next = preNode;
			nextNode->pre = nextNode;
			while (_itBeg != _itEnd) {
				iterator tmp = _itBeg++;
				__destroy_one_node(tmp->nodePtr_);
				__deallocate_one_node_mem(tmp->nodePtr_);
			}
			
			return static_cast<iterator>(nextNode);
		}

		void clear() {//�������������β�������������нڵ�
			list_node_pointer cur = nodePtr_->next;
			while (cur != nodePtr_) {
				list_node_pointer tmp = cur;
				cur = cur->next;
				__destroy_one_node(tmp);
				__deallocate_one_node_mem(tmp);
			}
			nodePtr_->next = nodePtr_;
			nodePtr_->pre = nodePtr_;
		}
		void remove(const value_type& _value) {//�Ƴ�����ֵΪ_value������ڵ㡣
			iterator cur = begin();
			while (cur != end()) {
				if (*cur == _value) {
					iterator tmp = cur++;
					erase(tmp);
				}
				else {
					++cur;
				}
			}
		}

		template<class Op>
		void remove_if(Op _op) {
			iterator it = begin();
			while (it != end())
			{
				if (_op(*it)) {
					auto tmp = it;
					++it;
					erase(tmp);
				}
			}
		}
		void unique() {//ȥ�������������ظ�Ԫ�أ�����n������1�����ֻʣһ������1
			iterator next = begin();
			iterator cur = next++;
			while (next != end()) {
				if (*cur == *next) {
					erase(next);
				}
				else {
					cur = next;
				}
				next = cur + 1;
			}
		}

		void swap(list& _rhs) {
			swap(nodePtr_, _rhs.nodePtr);
		}
		//-------------------------------------------���нӿ�-----------------------------------------------------------------------
		//splice
		//��һ������ӵ��������_pos��ָλ��֮ǰ��_otherList���벻ͬ�� *this��ִ�иò�����_otherList����ɿ�����
		void splice(iterator _pos, list& _otherList) {
			if (!_otherList.empty()) {
				__transfer(_pos, _otherList.begin(), _otherList.end());
			}
		}
		//��it��ָ��Ԫ�أ��ӵ�_posǰ��
		void splice(iterator _pos, list&, iterator _it){
			iterator endIt = _it + 1;
			if (_pos != _it && _pos != endIt) {
				__transfer(_pos, _it, endIt);
			}
		}
		//����������ָ����ӵ�_posǰ��
		void splice(iterator _pos, list&, iterator _first, iterator _end) {
			if (_first != _end && _end != _pos && _first != _pos) {
				__transfer(_pos, _first, _end);
			}
		}

		//merge:�ϲ�������������,����ϲ�����һ����
		template<class Comp>
		void merge(list& _ls, Comp _cmp = LT::less<T>()) {
			if (_ls == *this) { return; }

			iterator beg1 = begin();
			iterator end1 = end();
			iterator beg2 = _ls.begin();
			iterator end2 = _ls.end();

			//ע��list������û�ж������С����Щ�ȽϷ�
			while (beg1 != end1 && beg2 != end2) {
				if (_cmp(*beg1, *beg2)) {
					++beg1;
				}
				else {
					//˵����Ҫ��2�ϲ���ȥ�ˡ�
					iterator tmpBeg2 = beg2;
					while (beg2 != end2 && _cmp(*beg2, *beg1)) {
						++beg2;
					}
					__transfer(beg1, tmpBeg2, beg2);
				}
				if (beg2 != end2) {
					__transfer(end1, beg2, end2);
				}
			}
		}

		//��ת����
		void reverse() {
			if ( nodePtr_->next == nodePtr_->pre) { return; }//size() == 0��size == 1��
			iterator beg = begin();
			iterator end = end();
			while (beg != end) {
				LT::swap(beg.nodePtr_->next, beg.nodePtr_->pre);
				--beg;
			}
			LT::swap(end.nodePtr_->next, end.nodePtr_->pre);
		}

		//��������
		template<class Comp>
		void sort(Comp _cmp =LT::less<T>()) {
			__sort(begin(), size(), _cmp);
		}
		//***************************************************************************************************************************
		//***************************************************�ڲ�ʵ��****************************************************************
		//***************************************************************************************************************************
		private:
		//---------------------------------------------------�ռ�����----------------------------------------------------------------
		typedef allocator<T> data_allocator;
		typedef allocator<list_node> node_allocator;
	
		//���һ���ڵ�Ŀռ䣬���ظýڵ�ָ��ýڵ��ָ��
		inline list_node_pointer __allocate_one_node_mem() {
			list_node_pointer node = node_allocator::allocate();
			return node;
		}
		//����һ���ڵ�Ŀռ�
		inline void __deallocate_one_node_mem(list_node_pointer _ptr) {
			node_allocator::deallocate(_ptr);
		}

		inline list_node_pointer __construct_one_node(list_node_pointer _ptr,
			const value_type& _value = T(), list_node_pointer _preNode = nullptr, list_node_pointer _nextNode = nullptr) {
			LT::construct(LT::address_of(_ptr->data), _value);
			_ptr->pre = _preNode;
			_ptr->next = _nextNode;
			return _ptr;
		}

		inline list_node_pointer __construct_one_node(list_node_pointer _ptr,
			value_type&& _value, list_node_pointer _preNode = nullptr, list_node_pointer _nextNode = nullptr) {
			LT::construct(LT::address_of(_ptr->data), LT::move(_value));
			_ptr->pre = _preNode;
			_ptr->next = _nextNode;
			return _ptr;
		}

		inline void __destroy_one_node(list_node_pointer _ptr) {
			LT::destroy(LT::address_of(_ptr->data));
		}

		//����β��㡣
		inline void __set_tail() {
			//����һ���ڵ㼴��;
			nodePtr_ = __allocate_one_node_mem();//���Բ���ʼ�������data;
			nodePtr_->next = nodePtr_;
			nodePtr_->pre = nodePtr_;
		}
		//--------------------------------------------��ʼ������----------------------------------------------------
		inline void __init() {
			__set_tail();
		}

		inline void __init(size_type _n, const value_type& _value) {
			nodePtr_ = __allocate_one_node_mem();
			for (; _n; --_n) {
				list_node_pointer cur = __allocate_one_node_mem();
				LT::construct(LT::address_of(cur), _value);
			}
			
		}

		template<class InputIterator>
		inline void __init(InputIterator _itBeg, InputIterator _itEnd) {
			__set_tail();
			size_type n = LT::distance(_itBeg, _itEnd);
			try {
				for (; n; --n, ++_itBeg) {
					insert(end(), _itBeg, _itEnd);
				}
			}
			catch(...){
				clear();
				__destroy_one_node(nodePtr_);
				__deallocate_one_node_mem(nodePtr_);
				nodePtr_ = nullptr;
			}
		}

		//������ʵ��
		inline void __uninit() {
			list_node_pointer cur = begin().nodePtr_;
			while (cur != nodePtr_) {
				list_node_pointer tmp = cur;
				cur = cur->next;
				__destroy_one_node(tmp);
				__deallocate_one_node_mem(tmp);
			}
			__deallocate_one_node_mem(nodePtr_);
			nodePtr_ = nullptr;
		}

		//��ֵassign��ʵ��
		inline void __assignN(size_type _n, const value_type& _value) {
			iterator cur = begin();
			while (cur != end() && _n) {
				*cur = _value;
				--_n;
			}
			//����ռ��ʣ
			while (cur != end()) {
				cur = erase(cur,end());
			}
			while (_n) {
					insert(end(), _value);
					--_n;
			}	
		}

		template<class InputIter>
		inline void __assignIt(InputIter _first, InputIter _end) {
			size_type n = static_cast<size_type>(LT::distance(_first, _end));
			iterator cur = begin();
			while (cur != end() && n) {
				*_first = *cur;
				--n;
				++_first;
			}
			if (cur != end()) {
				 erase(cur, end());
			}
			else if (n) {
				insert(end(),n,*_first);
				++_first;
			}
		}

		//resize��ʵ��
		inline void __resize(size_type _n, const value_type& _value) {
			iterator it = begin();
			for (; it != end() && _n; ++it, --_n) {}
			if (it != end()) { erase(it, end()); }
			while (_n)
			{
				emplace_back(_value);
			}
		}
		
		//emplace��ʵ��
		template<class ...Args>
		inline void __emplace(iterator _pos, Args&& ..._value) {
			list_node_pointer pre = _pos.nodePtr_->pre;
			//list_node_pointer newNode = 
		}
		//-------------------------------------------�ڲ��ӿ�---------------------------------------------------------
		void __transfer(iterator _pos, iterator _first, iterator _end) {//��[first,end)֮���Ԫ���Ƶ�_pos֮ǰ��������ͬһ��list�ڵ���������
			if (_pos != _end) {
				list_node_pointer preNode = _pos.nodePtr_->pre;
				list_node_pointer tailNode = _end->pre;

				_first.nodePtr_->pre->next = _end.nodePtr_;
				_end.nodePtr_->pre = _first.nodePtr_->pre;

				_first.nodePtr_->pre = preNode;
				preNode->next = _first;
				tailNode->next = _pos;
				_pos->pre = tailNode;
			}
		}

		//����
		template<class Comp>
		void __sort(iterator _itBegin, size_type _n, Comp _cmp) {
			if (_n == 1 || _n == 0) { return; }

			//ʹ�ù鲢����
			size_type half = _n / 2;
			iterator theNext = _itBegin + half;
			__sort(_itBegin, half, _cmp);
			__sort(theNext, _n - half, _cmp);
			//��ʱ�Ѿ����������������ˡ�
			
			while(_itBegin != _itBegin + half && theNext != _itBegin + _n) {
				if (_cmp(*_itBegin, *theNext)) {
					++_itBegin;
				}
				else {
				//˵����Ҫ��2�ϲ���ȥ�ˡ�
				iterator tmpBeg2 = _itBegin;
				while (theNext != _itBegin + _n && _cmp(*theNext, *_itBegin)) {
					++theNext;
				}
				__transfer(_itBegin, tmpBeg2, theNext);
				}
				if (theNext != _itBegin + _n) {
					__transfer(_itBegin + half, theNext, _itBegin + _n);
				}
			}

		}
	};
	
	//******************************************�ⲿ�����غ���****************************************
	template<class T>
	bool operator<(const list<T>& _lhs, const list<T>& _rhs) {
		return LT::lexicographical_compare(_lhs.cbegin(), _lhs.cend(), _rhs.cbegin(), _rhs.cend());
	}

	template<class T>
	bool operator>(const list<T>& _lhs, const list<T>& _rhs) {
		return LT::lexicographical_compare(_rhs.cbegin(), _rhs.cend(), _lhs.cbegin(), _lhs.cend());
	}
	template<class T>
	bool operator==(const list<T>& _lhs, const list<T>& _rhs) {
		auto it1 = _lhs.cbegin();
		auto it2 = _rhs.cbegin();
		while (it1 != _lhs.cend() && it2 != _rhs.cend())
		{
			if (*it1 != *it2) { return false; }
		}
		return it1 == _lhs.cend() && it2 = _rhs.cend();
	}
	template <class T>
	bool operator!=(const list<T>& _lhs, const list<T>& _rhs) {
		return !(_lhs == _rhs);
	}

	template <class T>
	bool operator<=(const list<T>& _lhs, const list<T>& _rhs)
	{
		return !(_rhs < _lhs);
	}

	template <class T>
	bool operator>=(const list<T>& _lhs, const list<T>& _rhs)
	{
		return !(_lhs < _rhs);
	}

	// swap
	template <class T>
	void swap(list<T>& _lhs, list<T>& _rhs) noexcept
	{
		_lhs.swap(_rhs);
	}
}