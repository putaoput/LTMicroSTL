////@Author: Lin Tao
////@Email: putaopu@qq.com
//
//#pragma once
////��ͷ�ļ������ṩ�������ݽṹ:���������ģ�����ʽ����
////�ֱ���Ҫ��pair��ȡ��������ڵ���ƣ��������������ƣ��������Ƽ�������
////��ͷ�ļ��ĵ���������㣬������㷨ʵ�־��ο���Դ���룬���������ƿ�ܲο���Դ���룬�����ڲ�����ʵ���Ƕ������
////��֤�˴���ṹ����ȷ�������ڲ�ʵ��������п��ǲ���֮��
//
//#include <initializer_list>
//#include <cassert>
//
//#include "functional.h"
//#include "iterator.h"
//#include "memory.h"
//#include "type_traits.h"
//#include "allocator.h"
//
//namespace LT 
//{
//	//--------------------------����Ҫ���������ڵ���ɫ-------------------------------------------
//	typedef bool rb_tree_color_type;
//	static constexpr rb_tree_color_type red_node = false;
//	static constexpr rb_tree_color_type black_node = true;
//
//
//    //---------------------------------------forward declaration----------------------------------
//
//    template <class T> struct rb_tree_node_base;
//    template <class T> struct rb_tree_node;
//
//    template <class T> struct rb_tree_iterator;
//    template <class T> struct rb_tree_const_iterator;
//
//    //----------------------------------�����������ȡ---------------------------------------------------
//
//    //��pair����
//    template <class T, bool>
//    struct rb_tree_value_traits_impl
//    {
//        typedef T key_type;
//        typedef T mapped_type;
//        typedef T value_type;
//
//        template <class Ty>
//        static const key_type& get_key(const Ty& _value)
//        {
//            return _value;
//        }
//
//        template <class Ty>
//        static const value_type& get_value(const Ty& _value)
//        {
//            return _value;
//        }
//    };
//
//    //��pair����
//    template <class T>
//    struct rb_tree_value_traits_impl<T, true>
//    {
//        typedef typename std::remove_cv<typename T::first_type>::type key_type;
//        typedef typename T::second_type                               mapped_type;
//        typedef T                                                     value_type;
//
//        template <class Ty>
//        static const key_type& get_key(const Ty& _value)
//        {
//            return _value.first;
//        }
//
//        template <class Ty>
//        static const value_type& get_value(const Ty& _value)
//        {
//            return _value;
//        }
//    };
//
//    template <class T>
//    struct rb_tree_value_traits
//    {
//        static constexpr bool is_map = LT::is_pair<T>::_value;
//
//        typedef rb_tree_value_traits_impl<T, is_map> value_traits_type;
//
//        typedef typename value_traits_type::key_type    key_type;
//        typedef typename value_traits_type::mapped_type mapped_type;
//        typedef typename value_traits_type::value_type  value_type;
//
//        template <class Ty>
//        static const key_type& get_key(const Ty& _value)
//        {
//            return value_traits_type::get_key(_value);
//        }
//
//        template <class Ty>
//        static const value_type& get_value(const Ty& _value)
//        {
//            return value_traits_type::get_value(_value);
//        }
//    };
//
//    // rb tree node_ traits
//
//    template <class T>
//    struct rb_tree_node_traits
//    {
//        typedef rb_tree_color_type                 color_type;
//
//        typedef rb_tree_value_traits<T>            value_traits;
//        typedef typename value_traits::key_type    key_type;
//        typedef typename value_traits::mapped_type mapped_type;
//        typedef typename value_traits::value_type  value_type;
//
//        typedef rb_tree_node_base<T>* base_ptr;
//        typedef rb_tree_node<T>* node_ptr;
//    };
//
//    // --------------------------------rb tree �Ľڵ����--------------------------------
//
//    template <class T>
//    struct rb_tree_node_base
//    {
//        typedef rb_tree_color_type          color_type;
//        typedef rb_tree_node_base<T>*       base_ptr;
//        typedef rb_tree_node<T>*            node_ptr;
//
//        base_ptr   parent;  // ���ڵ�
//        base_ptr   left;    // ���ӽڵ�
//        base_ptr   right;   // ���ӽڵ�
//        color_type color;   // �ڵ���ɫ
//
//        base_ptr get_base_ptr()
//        {
//            return &*this;
//        }
//
//        node_ptr get_node_ptr()
//        {
//            return reinterpret_cast<node_ptr>(&*this);
//        }
//
//        node_ptr& get_node_ref()
//        {
//            return reinterpret_cast<node_ptr&>(*this);
//        }
//    };
//
//    template <class T>
//    struct rb_tree_node :public rb_tree_node_base<T>
//    {
//        typedef rb_tree_node_base<T>* base_ptr;
//        typedef rb_tree_node<T>* node_ptr;
//
//        T value_;  // �ڵ�ֵ
//
//        base_ptr get_base_ptr()
//        {
//            return static_cast<base_ptr>(&*this);
//        }
//
//        node_ptr get_node_ptr()
//        {
//            return &*this;
//        }
//    };
//
//    // ------------------------------------------------rb tree traits----------------------------------------------------
//
//    template <class T>
//    struct rb_tree_traits
//    {
//        typedef rb_tree_value_traits<T>            value_traits;
//
//        typedef typename value_traits::key_type    key_type;
//        typedef typename value_traits::mapped_type mapped_type;
//        typedef typename value_traits::value_type  value_type;
//
//        typedef value_type* pointer;
//        typedef value_type& reference;
//        typedef const value_type* const_pointer;
//        typedef const value_type& const_reference;
//
//        typedef rb_tree_node_base<T>               base_type;
//        typedef rb_tree_node<T>                    node_type;
//
//        typedef base_type*                         base_ptr;
//        typedef node_type*                         node_ptr;
//    };
//
//    // --------------------------------------rb tree �ĵ�����-------------------------------------------------
//
//    template <class T>
//    struct rb_tree_iterator_base :public LT::iterator<LT::bidirectional_iterator_tag, T>
//    {
//        typedef typename rb_tree_traits<T>::base_ptr  base_ptr;
//
//        base_ptr node_;  // ָ��ڵ㱾��
//
//        rb_tree_iterator_base() :node_(nullptr) {}
//
//        // ʹ������ǰ��
//        void inc()
//        {
//            if (node_->right != nullptr)
//            {
//                node_ = rb_tree_min(node_->right);
//            }
//            else
//            {  // ���û�����ӽڵ�
//                auto y = node_->parent;
//                while (y->right == node_)
//                {
//                    node_ = y;
//                    y = y->parent;
//                }
//                if (node_->right != y)  // Ӧ�ԡ�Ѱ�Ҹ��ڵ����һ�ڵ㣬�����ڵ�û�����ӽڵ㡱���������
//                    node_ = y;
//            }
//        }
//
//        // ʹ����������
//        void dec()
//        {
//            if (node_->parent->parent == node_ && rb_tree_is_red(node_))
//            { // ��� node_ Ϊ header
//                node_ = node_->right;  // ָ���������� max �ڵ�
//            }
//            else if (node_->left != nullptr)
//            {
//                node_ = rb_tree_max(node_->left);
//            }
//            else
//            {  // �� header �ڵ㣬Ҳ�����ӽڵ�
//                auto y = node_->parent;
//                while (node_ == y->left)
//                {
//                    node_ = y;
//                    y = y->parent;
//                }
//                node_ = y;
//            }
//        }
//
//        bool operator==(const rb_tree_iterator_base& _rhs) { return node_ == _rhs.node_; }
//        bool operator!=(const rb_tree_iterator_base& _rhs) { return node_ != _rhs.node_; }
//    };
//
//    template <class T>
//    struct rb_tree_iterator :public rb_tree_iterator_base<T>
//    {
//        typedef rb_tree_traits<T>                tree_traits;
//
//        typedef typename tree_traits::value_type value_type;
//        typedef typename tree_traits::pointer    pointer;
//        typedef typename tree_traits::reference  reference;
//        typedef typename tree_traits::base_ptr   base_ptr;
//        typedef typename tree_traits::node_ptr   node_ptr;
//
//        typedef rb_tree_iterator<T>              iterator;
//        typedef rb_tree_const_iterator<T>        const_iterator;
//        typedef iterator                         self;
//
//        using rb_tree_iterator_base<T>::node_;
//
//        // ���캯��
//        rb_tree_iterator() {}
//        rb_tree_iterator(base_ptr _x) { node_ = _x; }
//        rb_tree_iterator(node_ptr _x) { node_ = _x; }
//        rb_tree_iterator(const iterator& _rhs) { node_ = _rhs.node_; }
//        rb_tree_iterator(const const_iterator& _rhs) { node_ = _rhs.node_; }
//
//        // ���ز�����
//        reference operator*()  const { return node_->get_node_ptr()->_value; }
//        pointer   operator->() const { return &(operator*()); }
//
//        self& operator++()
//        {
//            this->inc();
//            return *this;
//        }
//        self operator++(int)
//        {
//            self tmp(*this);
//            this->inc();
//            return tmp;
//        }
//        self& operator--()
//        {
//            this->dec();
//            return *this;
//        }
//        self operator--(int)
//        {
//            self tmp(*this);
//            this->dec();
//            return tmp;
//        }
//    };
//
//
//    template <class T>
//    struct rb_tree_const_iterator :public rb_tree_iterator_base<T>
//    {
//        typedef rb_tree_traits<T>                     tree_traits;
//
//        typedef typename tree_traits::value_type      value_type;
//        typedef typename tree_traits::const_pointer   pointer;
//        typedef typename tree_traits::const_reference reference;
//        typedef typename tree_traits::base_ptr        base_ptr;
//        typedef typename tree_traits::node_ptr        node_ptr;
//
//        typedef rb_tree_iterator<T>                   iterator;
//        typedef rb_tree_const_iterator<T>             const_iterator;
//        typedef const_iterator                        self;
//
//        using rb_tree_iterator_base<T>::node_;
//
//        // ���캯��
//        rb_tree_const_iterator() {}
//        rb_tree_const_iterator(base_ptr _x) { node_ = _x; }
//        rb_tree_const_iterator(node_ptr _x) { node_ = _x; }
//        rb_tree_const_iterator(const iterator& _rhs) { node_ = _rhs.node_; }
//        rb_tree_const_iterator(const const_iterator& _rhs) { node_ = _rhs.node_; }
//
//        // ���ز�����
//        reference operator*()  const { return node_->get_node_ptr()->value; }
//        pointer   operator->() const { return &(operator*()); }
//
//        self& operator++()
//        {
//            this->inc();
//            return *this;
//        }
//        self operator++(int)
//        {
//            self tmp(*this);
//            this->inc();
//            return tmp;
//        }
//        self& operator--()
//        {
//            this->dec();
//            return *this;
//        }
//        self operator--(int)
//        {
//            self tmp(*this);
//            this->dec();
//            return tmp;
//        }
//    };
//
//    //----------------------------------------------------������㷨------------------------------------------------------------
//
//    //Ѱ����С�ڵ�ֵ
//    template <class NodePtr>
//    NodePtr rb_tree_min(NodePtr _x)  
//    {
//        while (_x->left != nullptr)
//        {
//            _x = _x->left;
//        }
//            
//        return _x;
//    }
//
//    //Ѱ�����ڵ�ֵ
//    template <class NodePtr>
//    NodePtr rb_tree_max(NodePtr _x)  
//    {
//        while (_x->right != nullptr)
//        {
//            _x = _x->right;
//        }
//            
//        return _x;
//    }
//
//    //�жϵ�ǰ�ڵ��ǲ���һ�������
//    template <class NodePtr>
//    bool rb_tree_is_lchild(NodePtr _node)  
//    {
//        return _node == _node->parent->left;
//    }
//
//    //�жϵ�ǰ�ڵ��ǲ��Ǻ�ɫ
//    template <class NodePtr>
//    bool rb_tree_is_red(NodePtr _node)  
//    {
//        return _node->color == red_node;
//    }
//
//    //�ѵ�ǰ�ڵ���Ϊ��ɫ
//    template <class NodePtr>
//    void rb_tree_set_black(NodePtr& _node)  
//    {
//        _node->color = black_node;
//    }
//
//    //�ѵ�ǰ�ڵ���Ϊ��ɫ
//    template <class NodePtr>
//    void rb_tree_set_red(NodePtr& _node)  
//    {
//        _node->color = red_node;
//    }
//
//    //���ص�ǰ�ڵ����һ���ڵ�
//    template <class NodePtr>
//    NodePtr rb_tree_next(NodePtr _node)  
//    {
//        if (_node->right != nullptr)
//        {
//            return rb_tree_min(_node->right);
//        }
//            
//        while (!rb_tree_is_lchild(_node))
//        {
//            _node = _node->parent;
//        }
//            
//        return _node->parent;
//    }
//
//    //---------------------------�����㷨---------------------------
//    /*---------------------------------------*\
//    |       p                         p       |
//    |      / \                       / \      |
//    |     _x   d    rotate left      y   d     |
//    |    / \       ===========>    / \        |
//    |   a   y                     _x   c       |
//    |      / \                   / \          |
//    |     b   c                 a   b         |
//    \*---------------------------------------*/
//    // ����������һΪ�����㣬������Ϊ���ڵ�
//    template <class NodePtr>
//    void rb_tree_rotate_left(NodePtr _x, NodePtr& _root)  
//    {
//        auto y = _x->right;  // y Ϊ _x �����ӽڵ�
//        _x->right = y->left;
//        if (y->left != nullptr)
//            y->left->parent = _x;
//        y->parent = _x->parent;
//
//        if (_x == _root)
//        { // ��� _x Ϊ���ڵ㣬�� y ���� _x ��Ϊ���ڵ�
//            _root = y;
//        }
//        else if (rb_tree_is_lchild(_x))
//        { // ��� _x �����ӽڵ�
//            _x->parent->left = y;
//        }
//        else
//        { // ��� _x �����ӽڵ�
//            _x->parent->right = y;
//        }
//        // ���� _x �� y �Ĺ�ϵ
//        y->left = _x;
//        _x->parent = y;
//    }
//
//    /*----------------------------------------*\
//    |     p                         p          |
//    |    / \                       / \         |
//    |   d   _x      rotate right   d   y        |
//    |      / \     ===========>      / \       |
//    |     y   a                     b   _x      |
//    |    / \                           / \     |
//    |   b   c                         c   a    |
//    \*----------------------------------------*/
//    // ����������һΪ�����㣬������Ϊ���ڵ�
//    template <class NodePtr>
//    void rb_tree_rotate_right(NodePtr _x, NodePtr& _root)  
//    {
//        auto y = _x->left;
//        _x->left = y->right;
//        if (y->right)
//            y->right->parent = _x;
//        y->parent = _x->parent;
//
//        if (_x == _root)
//        { // ��� _x Ϊ���ڵ㣬�� y ���� _x ��Ϊ���ڵ�
//            _root = y;
//        }
//        else if (rb_tree_is_lchild(_x))
//        { // ��� _x �����ӽڵ�
//            _x->parent->left = y;
//        }
//        else
//        { // ��� _x �����ӽڵ�
//            _x->parent->right = y;
//        }
//        // ���� _x �� y �Ĺ�ϵ
//        y->right = _x;
//        _x->parent = y;
//    }
//
//    // ����ڵ��ʹ rb tree ����ƽ�⣬����һΪ�����ڵ㣬������Ϊ���ڵ�
//    //
//    // case 1: �����ڵ�λ�ڸ��ڵ㣬�������ڵ�Ϊ��
//    // case 2: �����ڵ�ĸ��ڵ�Ϊ�ڣ�û���ƻ�ƽ�⣬ֱ�ӷ���
//    // case 3: ���ڵ������ڵ㶼Ϊ�죬��ڵ������ڵ�Ϊ�ڣ��游�ڵ�Ϊ�죬
//    //         Ȼ�����游�ڵ�Ϊ��ǰ�ڵ㣬��������
//    // case 4: ���ڵ�Ϊ�죬����ڵ�Ϊ NIL ���ɫ�����ڵ�Ϊ���ң����ӣ���ǰ�ڵ�Ϊ�ң��󣩺��ӣ�
//    //         �ø��ڵ��Ϊ��ǰ�ڵ㣬���Ե�ǰ�ڵ�Ϊ֧�����ң���
//    // case 5: ���ڵ�Ϊ�죬����ڵ�Ϊ NIL ���ɫ�����ڵ�Ϊ���ң����ӣ���ǰ�ڵ�Ϊ���ң����ӣ�
//    //         �ø��ڵ��Ϊ��ɫ���游�ڵ��Ϊ��ɫ�����游�ڵ�Ϊ֧���ң�����
//    //
//    // �ο�����: http://blog.csdn.net/v_JULY_v/article/details/6105630
//    //          http://blog.csdn.net/v_JULY_v/article/details/6109153
//    template <class NodePtr>
//    void rb_tree_insert_rebalance(NodePtr _x, NodePtr& _root)  
//    {
//        rb_tree_set_red(_x);  // �����ڵ�Ϊ��ɫ
//        while (_x != _root && rb_tree_is_red(_x->parent))
//        {
//            if (rb_tree_is_lchild(_x->parent))
//            { // ������ڵ������ӽڵ�
//                auto uncle = _x->parent->parent->right;
//                if (uncle != nullptr && rb_tree_is_red(uncle))
//                { // case 3: ���ڵ������ڵ㶼Ϊ��
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_black(uncle);
//                    _x = _x->parent->parent;
//                    rb_tree_set_red(_x);
//                }
//                else
//                { // ������ڵ������ڵ�Ϊ��
//                    if (!rb_tree_is_lchild(_x))
//                    { // case 4: ��ǰ�ڵ� _x Ϊ���ӽڵ�
//                        _x = _x->parent;
//                        rb_tree_rotate_left(_x, _root);
//                    }
//                    // ��ת���� case 5�� ��ǰ�ڵ�Ϊ���ӽڵ�
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_red(_x->parent->parent);
//                    rb_tree_rotate_right(_x->parent->parent, _root);
//                    break;
//                }
//            }
//            else  // ������ڵ������ӽڵ㣬�Գƴ���
//            {
//                auto uncle = _x->parent->parent->left;
//                if (uncle != nullptr && rb_tree_is_red(uncle))
//                { // case 3: ���ڵ������ڵ㶼Ϊ��
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_black(uncle);
//                    _x = _x->parent->parent;
//                    rb_tree_set_red(_x);
//                    // ��ʱ�游�ڵ�Ϊ�죬���ܻ��ƻ�����������ʣ��ǰ�ڵ�Ϊ�游�ڵ㣬��������
//                }
//                else
//                { // ������ڵ������ڵ�Ϊ��
//                    if (rb_tree_is_lchild(_x))
//                    { // case 4: ��ǰ�ڵ� _x Ϊ���ӽڵ�
//                        _x = _x->parent;
//                        rb_tree_rotate_right(_x, _root);
//                    }
//                    // ��ת���� case 5�� ��ǰ�ڵ�Ϊ���ӽڵ�
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_red(_x->parent->parent);
//                    rb_tree_rotate_left(_x->parent->parent, _root);
//                    break;
//                }
//            }
//        }
//        rb_tree_set_black(_root);  // ���ڵ���ԶΪ��
//    }
//
//    // ɾ���ڵ��ʹ rb tree ����ƽ�⣬����һΪҪɾ���Ľڵ㣬������Ϊ���ڵ㣬������Ϊ��С�ڵ㣬������Ϊ���ڵ�
//    // 
//    // �ο�����: http://blog.csdn.net/v_JULY_v/article/details/6105630
//    //          http://blog.csdn.net/v_JULY_v/article/details/6109153
//    template <class NodePtr>
//    NodePtr rb_tree_erase_rebalance(NodePtr z, NodePtr& _root, NodePtr& leftmost, NodePtr& rightmost)
//    {
//        // y �ǿ��ܵ��滻�ڵ㣬ָ������Ҫɾ���Ľڵ�
//        auto y = (z->left == nullptr || z->right == nullptr) ? z : rb_tree_next(z);
//        // _x �� y ��һ�����ӽڵ�� NIL �ڵ�
//        auto _x = y->left != nullptr ? y->left : y->right;
//        // xp Ϊ _x �ĸ��ڵ�
//        NodePtr xp = nullptr;
//
//        // y != z ˵�� z �������ǿ��ӽڵ㣬��ʱ y ָ�� z ������������ڵ㣬_x ָ�� y �����ӽڵ㡣
//        // �� y ���� z ��λ�ã��� _x ���� y ��λ�ã������ y ָ�� z
//        if (y != z)
//        {
//            z->left->parent = y;
//            y->left = z->left;
//
//            // ��� y ���� z �����ӽڵ㣬��ô z �����ӽڵ�һ��������
//            if (y != z->right)
//            { // _x �滻 y ��λ��
//                xp = y->parent;
//                if (_x != nullptr)
//                    _x->parent = y->parent;
//
//                y->parent->left = _x;
//                y->right = z->right;
//                z->right->parent = y;
//            }
//            else
//            {
//                xp = y;
//            }
//
//            // ���� y �� z �ĸ��ڵ� 
//            if (_root == z)
//                _root = y;
//            else if (rb_tree_is_lchild(z))
//                z->parent->left = y;
//            else
//                z->parent->right = y;
//            y->parent = z->parent;
//            LT::swap(y->color, z->color);
//            y = z;
//        }
//        // y == z ˵�� z ����ֻ��һ������
//        else
//        {
//            xp = y->parent;
//            if (_x)
//                _x->parent = y->parent;
//
//            // ���� _x �� z �ĸ��ڵ�
//            if (_root == z)
//                _root = _x;
//            else if (rb_tree_is_lchild(z))
//                z->parent->left = _x;
//            else
//                z->parent->right = _x;
//
//            // ��ʱ z �п���������ڵ�����ҽڵ㣬��������
//            if (leftmost == z)
//                leftmost = _x == nullptr ? xp : rb_tree_min(_x);
//            if (rightmost == z)
//                rightmost = _x == nullptr ? xp : rb_tree_max(_x);
//        }
//
//        // ��ʱ��y ָ��Ҫɾ���Ľڵ㣬_x Ϊ����ڵ㣬�� _x �ڵ㿪ʼ������
//        // ���ɾ���Ľڵ�Ϊ��ɫ����������û�б��ƻ����������������������_x Ϊ���ӽڵ�Ϊ������
//        // case 1: �ֵܽڵ�Ϊ��ɫ����ڵ�Ϊ�죬�ֵܽڵ�Ϊ�ڣ��������ң�������������
//        // case 2: �ֵܽڵ�Ϊ��ɫ���������ӽڵ㶼Ϊ��ɫ�� NIL�����ֵܽڵ�Ϊ�죬���ڵ��Ϊ��ǰ�ڵ㣬��������
//        // case 3: �ֵܽڵ�Ϊ��ɫ�����ӽڵ�Ϊ��ɫ�� NIL�����ӽڵ�Ϊ��ɫ�� NIL��
//        //         ���ֵܽڵ�Ϊ�죬�ֵܽڵ�����ӽڵ�Ϊ�ڣ����ֵܽڵ�Ϊ֧���ң���������������
//        // case 4: �ֵܽڵ�Ϊ��ɫ�����ӽڵ�Ϊ��ɫ�����ֵܽڵ�Ϊ���ڵ����ɫ�����ڵ�Ϊ��ɫ���ֵܽڵ�����ӽڵ�
//        //         Ϊ��ɫ���Ը��ڵ�Ϊ֧�����ң������������ʵ�����ɣ��㷨����
//        if (!rb_tree_is_red(y))
//        { // _x Ϊ��ɫʱ������������ֱ�ӽ� _x ��Ϊ��ɫ����
//            while (_x != _root && (_x == nullptr || !rb_tree_is_red(_x)))
//            {
//                if (_x == xp->left)
//                { // ��� _x Ϊ���ӽڵ�
//                    auto brother = xp->right;
//                    if (rb_tree_is_red(brother))
//                    { // case 1
//                        rb_tree_set_black(brother);
//                        rb_tree_set_red(xp);
//                        rb_tree_rotate_left(xp, _root);
//                        brother = xp->right;
//                    }
//                    // case 1 תΪΪ�� case 2��3��4 �е�һ��
//                    if ((brother->left == nullptr || !rb_tree_is_red(brother->left)) &&
//                        (brother->right == nullptr || !rb_tree_is_red(brother->right)))
//                    { // case 2
//                        rb_tree_set_red(brother);
//                        _x = xp;
//                        xp = xp->parent;
//                    }
//                    else
//                    {
//                        if (brother->right == nullptr || !rb_tree_is_red(brother->right))
//                        { // case 3
//                            if (brother->left != nullptr)
//                                rb_tree_set_black(brother->left);
//                            rb_tree_set_red(brother);
//                            rb_tree_rotate_right(brother, _root);
//                            brother = xp->right;
//                        }
//                        // תΪ case 4
//                        brother->color = xp->color;
//                        rb_tree_set_black(xp);
//                        if (brother->right != nullptr)
//                            rb_tree_set_black(brother->right);
//                        rb_tree_rotate_left(xp, _root);
//                        break;
//                    }
//                }
//                else  // _x Ϊ���ӽڵ㣬�Գƴ���
//                {
//                    auto brother = xp->left;
//                    if (rb_tree_is_red(brother))
//                    { // case 1
//                        rb_tree_set_black(brother);
//                        rb_tree_set_red(xp);
//                        rb_tree_rotate_right(xp, _root);
//                        brother = xp->left;
//                    }
//                    if ((brother->left == nullptr || !rb_tree_is_red(brother->left)) &&
//                        (brother->right == nullptr || !rb_tree_is_red(brother->right)))
//                    { // case 2
//                        rb_tree_set_red(brother);
//                        _x = xp;
//                        xp = xp->parent;
//                    }
//                    else
//                    {
//                        if (brother->left == nullptr || !rb_tree_is_red(brother->left))
//                        { // case 3
//                            if (brother->right != nullptr)
//                                rb_tree_set_black(brother->right);
//                            rb_tree_set_red(brother);
//                            rb_tree_rotate_left(brother, _root);
//                            brother = xp->left;
//                        }
//                        // תΪ case 4
//                        brother->color = xp->color;
//                        rb_tree_set_black(xp);
//                        if (brother->left != nullptr)
//                            rb_tree_set_black(brother->left);
//                        rb_tree_rotate_right(xp, _root);
//                        break;
//                    }
//                }
//            }
//            if (_x != nullptr)
//                rb_tree_set_black(_x);
//        }
//        return y;
//    }
//
//    //------------------------------------------------��������-----------------------------------------------------------------
//    template<class T, class Comp, class Alloc = LT::allocator<T>>
//    class rb_tree
//    {
//        //������������
//    public:
//        typedef rb_tree_traits<T>                        tree_traits;
//        typedef rb_tree_value_traits<T>                  value_traits;
//
//        typedef typename tree_traits::base_type          base_type;
//        typedef typename tree_traits::base_ptr           base_ptr;
//        typedef typename tree_traits::node_type          node_type;
//        typedef typename tree_traits::node_ptr           node_ptr;
//        typedef typename tree_traits::key_type           key_type;
//        typedef typename tree_traits::mapped_type        mapped_type;
//        typedef typename tree_traits::value_type         value_type;
//        typedef Comp                                     key_compare;
//
//        typedef T*                              pointer;
//        typedef const value_type*               const_pointer;
//        typedef typename T&                     reference;
//        typedef typename const T&               const_reference;
//        typedef typename size_t                 size_type;
//        typedef typename ptrdiff_t              difference_type;
//
//        typedef rb_tree_iterator<T>                      iterator;
//        typedef rb_tree_const_iterator<T>                const_iterator;
//        typedef LT::reverse_iterator<iterator>        reverse_iterator;
//        typedef LT::reverse_iterator<const_iterator>  const_reverse_iterator;
//
//
//        //��Ա����
//    private:
//        base_ptr header_;
//        size_type nodeCount_;
//        key_compare keyComp_;
//
//    //**************************************************************************************************************************************
//    //****************************************************�ⲿ�ӿ�********************************************************************
//    //**************************************************************************************************************************************
//    public:
//        //-----------------------------------�������---------------------------------------------------
//        rb_tree() { __init(); }
//
//        rb_tree(const rb_tree& rhs);
//        rb_tree(rb_tree&& rhs)  ;
//
//        rb_tree& operator=(const rb_tree& rhs);
//        rb_tree& operator=(rb_tree&& rhs);
//
//        ~rb_tree() { clear(); }
//
//    public:
//        // ��������ز���
//
//        iterator               begin()          
//        {
//            return  __leftmost();
//        }
//        const_iterator         begin()   const  
//        {
//            return __leftmost();
//        }
//        iterator               end()            
//        {
//            return header_;
//        }
//        const_iterator         end()     const  
//        {
//            return header_;
//        }
//
//        reverse_iterator       rbegin()         
//        {
//            return reverse_iterator(end());
//        }
//        const_reverse_iterator rbegin()  const  
//        {
//            return const_reverse_iterator(end());
//        }
//        reverse_iterator       rend()           
//        {
//            return reverse_iterator(begin());
//        }
//        const_reverse_iterator rend()    const  
//        {
//            return const_reverse_iterator(begin());
//        }
//
//        const_iterator         cbegin()  const  
//        {
//            return begin();
//        }
//        const_iterator         cend()    const  
//        {
//            return end();
//        }
//        const_reverse_iterator crbegin() const  
//        {
//            return rbegin();
//        }
//        const_reverse_iterator crend()   const  
//        {
//            return rend();
//        }
//
//        // ������ز���
//
//        bool      empty()    const   { return !node_count_; }
//        size_type size()     const   { return node_count_; }
//        size_type max_size() const   { return static_cast<size_type>(-1); }
//        // ����ɾ����ز���
//
// // emplace
//
//        template <class ...Args>
//        iterator  emplace_multi(Args&& ...args);
//
//        template <class ...Args>
//        LT::pair<iterator, bool> emplace_unique(Args&& ...args);
//
//        template <class ...Args>
//        iterator  emplace_multi_use_hint(iterator hint, Args&& ...args);
//
//        template <class ...Args>
//        iterator  emplace_unique_use_hint(iterator hint, Args&& ...args);
//
//        // insert
//
//        iterator  insert_multi(const value_type& value);
//        iterator  insert_multi(value_type&& value)
//        {
//            return emplace_multi(LT::move(value));
//        }
//
//        iterator  insert_multi(iterator hint, const value_type& value)
//        {
//            return emplace_multi_use_hint(hint, value);
//        }
//        iterator  insert_multi(iterator hint, value_type&& value)
//        {
//            return emplace_multi_use_hint(hint, LT::move(value));
//        }
//
//        template <class InputIterator>
//        void      insert_multi(InputIterator first, InputIterator last)
//        {
//            size_type n = LT::distance(first, last);
//            for (; n > 0; --n, ++first)
//                insert_multi(end(), *first);
//        }
//
//        LT::pair<iterator, bool> insert_unique(const value_type& value);
//        LT::pair<iterator, bool> insert_unique(value_type&& value)
//        {
//            return emplace_unique(LT::move(value));
//        }
//
//        iterator  insert_unique(iterator hint, const value_type& value)
//        {
//            return emplace_unique_use_hint(hint, value);
//        }
//        iterator  insert_unique(iterator hint, value_type&& value)
//        {
//            return emplace_unique_use_hint(hint, LT::move(value));
//        }
//
//        template <class InputIterator>
//        void      insert_unique(InputIterator first, InputIterator last)
//        {
//            size_type n = LT::distance(first, last);
//            THROW_LENGTH_ERROR_IF(node_count_ > max_size() - n, "rb_tree<T, Comp>'s size too big");
//            for (; n > 0; --n, ++first)
//                insert_unique(end(), *first);
//        }
//
//        // erase
//
//        iterator  erase(iterator hint);
//
//        size_type erase_multi(const key_type& key);
//        size_type erase_unique(const key_type& key);
//
//        void      erase(iterator first, iterator last);
//
//        void      clear();
//
//        // rb_tree ��ز���
//
//        iterator       find(const key_type& key);
//        const_iterator find(const key_type& key) const;
//
//        size_type      count_multi(const key_type& key) const
//        {
//            auto p = equal_range_multi(key);
//            return static_cast<size_type>(LT::distance(p.first, p.second));
//        }
//        size_type      count_unique(const key_type& key) const
//        {
//            return find(key) != end() ? 1 : 0;
//        }
//
//        iterator       lower_bound(const key_type& key);
//        const_iterator lower_bound(const key_type& key) const;
//
//        iterator       upper_bound(const key_type& key);
//        const_iterator upper_bound(const key_type& key) const;
//
//        LT::pair<iterator, iterator>
//            equal_range_multi(const key_type& key)
//        {
//            return LT::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
//        }
//        LT::pair<const_iterator, const_iterator>
//            equal_range_multi(const key_type& key) const
//        {
//            return LT::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
//        }
//
//        LT::pair<iterator, iterator>
//            equal_range_unique(const key_type& key)
//        {
//            iterator it = find(key);
//            auto next = it;
//            return it == end() ? LT::make_pair(it, it) : LT::make_pair(it, ++next);
//        }
//        LT::pair<const_iterator, const_iterator>
//            equal_range_unique(const key_type& key) const
//        {
//            const_iterator it = find(key);
//            auto next = it;
//            return it == end() ? LT::make_pair(it, it) : LT::make_pair(it, ++next);
//        }
//
//        void swap(rb_tree& rhs)  ;
//    public:
//        Alloc get_allocator()const
//        {
//            return Alloc();
//        }
//    //**************************************************************************************************************************************
//    //****************************************************�ڲ�ʵ��********************************************************************
//    //**************************************************************************************************************************************
//    private:
//        // ����������������ȡ�ø��ڵ㣬��С�ڵ�����ڵ�
//        base_ptr& __root()      const { return header_->parent; }
//        base_ptr& __leftmost()  const { return header_->left; }
//        base_ptr& __rightmost() const { return header_->right; }
//    
//    private:
//        //-----------------------------------------�ڴ�������-----------------------------------------------------------------------
//        
//        typedef LT::allocator<base_type>        base_allocator;
//        typedef LT::allocator<node_type>        node_allocator;
//
//         node_ptr __get_one_node_mem()
//        {
//            //���һ���ڵ��С���ڴ����򣬵��ǲ���ʼ��,�������ʧ�ܣ�������ָ�룬�����жϳ���
//            node_ptr newNode = node_allocator::allocate();
//            assert(newNode);
//            return newNode;
//        }
//         template<class ...Args>
//         inline void __construct_one_node_mem(node_ptr _node, Args&& ..._args)
//         {
//             LT::construct(LT::address_of(*node), LT::forward<Args>(_args)...);
//         }
//
//         inline void __set_one_base_mem(base_ptr _node, )
//        //
//        //-----------------------------------------������ص��ڲ�ʵ��---------------------------------------------------------------
//        inline void __init()
//        {//�޲����½�һ����
//
//        }
//    };
//
//};
