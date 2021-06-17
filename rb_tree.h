////@Author: Lin Tao
////@Email: putaopu@qq.com
//
//#pragma once
////该头文件负责提供基本数据结构:红黑树。以模板的形式定义
////分别主要有pair萃取，红黑树节点设计，红黑树迭代器设计，红黑树设计几个部分
////该头文件的迭代器，结点，红黑树算法实现均参考开源代码，红黑树类设计框架参考开源代码，但是内部具体实现是独立完成
////保证了大体结构的正确，但是内部实现难免会有考虑不周之处
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
//	//--------------------------首先要定义红黑树节点颜色-------------------------------------------
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
//    //----------------------------------红黑树类型萃取---------------------------------------------------
//
//    //非pair类型
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
//    //是pair类型
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
//    // --------------------------------rb tree 的节点设计--------------------------------
//
//    template <class T>
//    struct rb_tree_node_base
//    {
//        typedef rb_tree_color_type          color_type;
//        typedef rb_tree_node_base<T>*       base_ptr;
//        typedef rb_tree_node<T>*            node_ptr;
//
//        base_ptr   parent;  // 父节点
//        base_ptr   left;    // 左子节点
//        base_ptr   right;   // 右子节点
//        color_type color;   // 节点颜色
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
//        T value_;  // 节点值
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
//    // --------------------------------------rb tree 的迭代器-------------------------------------------------
//
//    template <class T>
//    struct rb_tree_iterator_base :public LT::iterator<LT::bidirectional_iterator_tag, T>
//    {
//        typedef typename rb_tree_traits<T>::base_ptr  base_ptr;
//
//        base_ptr node_;  // 指向节点本身
//
//        rb_tree_iterator_base() :node_(nullptr) {}
//
//        // 使迭代器前进
//        void inc()
//        {
//            if (node_->right != nullptr)
//            {
//                node_ = rb_tree_min(node_->right);
//            }
//            else
//            {  // 如果没有右子节点
//                auto y = node_->parent;
//                while (y->right == node_)
//                {
//                    node_ = y;
//                    y = y->parent;
//                }
//                if (node_->right != y)  // 应对“寻找根节点的下一节点，而根节点没有右子节点”的特殊情况
//                    node_ = y;
//            }
//        }
//
//        // 使迭代器后退
//        void dec()
//        {
//            if (node_->parent->parent == node_ && rb_tree_is_red(node_))
//            { // 如果 node_ 为 header
//                node_ = node_->right;  // 指向整棵树的 max 节点
//            }
//            else if (node_->left != nullptr)
//            {
//                node_ = rb_tree_max(node_->left);
//            }
//            else
//            {  // 非 header 节点，也无左子节点
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
//        // 构造函数
//        rb_tree_iterator() {}
//        rb_tree_iterator(base_ptr _x) { node_ = _x; }
//        rb_tree_iterator(node_ptr _x) { node_ = _x; }
//        rb_tree_iterator(const iterator& _rhs) { node_ = _rhs.node_; }
//        rb_tree_iterator(const const_iterator& _rhs) { node_ = _rhs.node_; }
//
//        // 重载操作符
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
//        // 构造函数
//        rb_tree_const_iterator() {}
//        rb_tree_const_iterator(base_ptr _x) { node_ = _x; }
//        rb_tree_const_iterator(node_ptr _x) { node_ = _x; }
//        rb_tree_const_iterator(const iterator& _rhs) { node_ = _rhs.node_; }
//        rb_tree_const_iterator(const const_iterator& _rhs) { node_ = _rhs.node_; }
//
//        // 重载操作符
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
//    //----------------------------------------------------红黑树算法------------------------------------------------------------
//
//    //寻找最小节点值
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
//    //寻找最大节点值
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
//    //判断当前节点是不是一个左儿子
//    template <class NodePtr>
//    bool rb_tree_is_lchild(NodePtr _node)  
//    {
//        return _node == _node->parent->left;
//    }
//
//    //判断当前节点是不是红色
//    template <class NodePtr>
//    bool rb_tree_is_red(NodePtr _node)  
//    {
//        return _node->color == red_node;
//    }
//
//    //把当前节点设为黑色
//    template <class NodePtr>
//    void rb_tree_set_black(NodePtr& _node)  
//    {
//        _node->color = black_node;
//    }
//
//    //把当前节点设为红色
//    template <class NodePtr>
//    void rb_tree_set_red(NodePtr& _node)  
//    {
//        _node->color = red_node;
//    }
//
//    //返回当前节点的下一个节点
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
//    //---------------------------调整算法---------------------------
//    /*---------------------------------------*\
//    |       p                         p       |
//    |      / \                       / \      |
//    |     _x   d    rotate left      y   d     |
//    |    / \       ===========>    / \        |
//    |   a   y                     _x   c       |
//    |      / \                   / \          |
//    |     b   c                 a   b         |
//    \*---------------------------------------*/
//    // 左旋，参数一为左旋点，参数二为根节点
//    template <class NodePtr>
//    void rb_tree_rotate_left(NodePtr _x, NodePtr& _root)  
//    {
//        auto y = _x->right;  // y 为 _x 的右子节点
//        _x->right = y->left;
//        if (y->left != nullptr)
//            y->left->parent = _x;
//        y->parent = _x->parent;
//
//        if (_x == _root)
//        { // 如果 _x 为根节点，让 y 顶替 _x 成为根节点
//            _root = y;
//        }
//        else if (rb_tree_is_lchild(_x))
//        { // 如果 _x 是左子节点
//            _x->parent->left = y;
//        }
//        else
//        { // 如果 _x 是右子节点
//            _x->parent->right = y;
//        }
//        // 调整 _x 与 y 的关系
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
//    // 右旋，参数一为右旋点，参数二为根节点
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
//        { // 如果 _x 为根节点，让 y 顶替 _x 成为根节点
//            _root = y;
//        }
//        else if (rb_tree_is_lchild(_x))
//        { // 如果 _x 是右子节点
//            _x->parent->left = y;
//        }
//        else
//        { // 如果 _x 是左子节点
//            _x->parent->right = y;
//        }
//        // 调整 _x 与 y 的关系
//        y->right = _x;
//        _x->parent = y;
//    }
//
//    // 插入节点后使 rb tree 重新平衡，参数一为新增节点，参数二为根节点
//    //
//    // case 1: 新增节点位于根节点，令新增节点为黑
//    // case 2: 新增节点的父节点为黑，没有破坏平衡，直接返回
//    // case 3: 父节点和叔叔节点都为红，令父节点和叔叔节点为黑，祖父节点为红，
//    //         然后令祖父节点为当前节点，继续处理
//    // case 4: 父节点为红，叔叔节点为 NIL 或黑色，父节点为左（右）孩子，当前节点为右（左）孩子，
//    //         让父节点成为当前节点，再以当前节点为支点左（右）旋
//    // case 5: 父节点为红，叔叔节点为 NIL 或黑色，父节点为左（右）孩子，当前节点为左（右）孩子，
//    //         让父节点变为黑色，祖父节点变为红色，以祖父节点为支点右（左）旋
//    //
//    // 参考博客: http://blog.csdn.net/v_JULY_v/article/details/6105630
//    //          http://blog.csdn.net/v_JULY_v/article/details/6109153
//    template <class NodePtr>
//    void rb_tree_insert_rebalance(NodePtr _x, NodePtr& _root)  
//    {
//        rb_tree_set_red(_x);  // 新增节点为红色
//        while (_x != _root && rb_tree_is_red(_x->parent))
//        {
//            if (rb_tree_is_lchild(_x->parent))
//            { // 如果父节点是左子节点
//                auto uncle = _x->parent->parent->right;
//                if (uncle != nullptr && rb_tree_is_red(uncle))
//                { // case 3: 父节点和叔叔节点都为红
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_black(uncle);
//                    _x = _x->parent->parent;
//                    rb_tree_set_red(_x);
//                }
//                else
//                { // 无叔叔节点或叔叔节点为黑
//                    if (!rb_tree_is_lchild(_x))
//                    { // case 4: 当前节点 _x 为右子节点
//                        _x = _x->parent;
//                        rb_tree_rotate_left(_x, _root);
//                    }
//                    // 都转换成 case 5： 当前节点为左子节点
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_red(_x->parent->parent);
//                    rb_tree_rotate_right(_x->parent->parent, _root);
//                    break;
//                }
//            }
//            else  // 如果父节点是右子节点，对称处理
//            {
//                auto uncle = _x->parent->parent->left;
//                if (uncle != nullptr && rb_tree_is_red(uncle))
//                { // case 3: 父节点和叔叔节点都为红
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_black(uncle);
//                    _x = _x->parent->parent;
//                    rb_tree_set_red(_x);
//                    // 此时祖父节点为红，可能会破坏红黑树的性质，令当前节点为祖父节点，继续处理
//                }
//                else
//                { // 无叔叔节点或叔叔节点为黑
//                    if (rb_tree_is_lchild(_x))
//                    { // case 4: 当前节点 _x 为左子节点
//                        _x = _x->parent;
//                        rb_tree_rotate_right(_x, _root);
//                    }
//                    // 都转换成 case 5： 当前节点为左子节点
//                    rb_tree_set_black(_x->parent);
//                    rb_tree_set_red(_x->parent->parent);
//                    rb_tree_rotate_left(_x->parent->parent, _root);
//                    break;
//                }
//            }
//        }
//        rb_tree_set_black(_root);  // 根节点永远为黑
//    }
//
//    // 删除节点后使 rb tree 重新平衡，参数一为要删除的节点，参数二为根节点，参数三为最小节点，参数四为最大节点
//    // 
//    // 参考博客: http://blog.csdn.net/v_JULY_v/article/details/6105630
//    //          http://blog.csdn.net/v_JULY_v/article/details/6109153
//    template <class NodePtr>
//    NodePtr rb_tree_erase_rebalance(NodePtr z, NodePtr& _root, NodePtr& leftmost, NodePtr& rightmost)
//    {
//        // y 是可能的替换节点，指向最终要删除的节点
//        auto y = (z->left == nullptr || z->right == nullptr) ? z : rb_tree_next(z);
//        // _x 是 y 的一个独子节点或 NIL 节点
//        auto _x = y->left != nullptr ? y->left : y->right;
//        // xp 为 _x 的父节点
//        NodePtr xp = nullptr;
//
//        // y != z 说明 z 有两个非空子节点，此时 y 指向 z 右子树的最左节点，_x 指向 y 的右子节点。
//        // 用 y 顶替 z 的位置，用 _x 顶替 y 的位置，最后用 y 指向 z
//        if (y != z)
//        {
//            z->left->parent = y;
//            y->left = z->left;
//
//            // 如果 y 不是 z 的右子节点，那么 z 的右子节点一定有左孩子
//            if (y != z->right)
//            { // _x 替换 y 的位置
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
//            // 连接 y 与 z 的父节点 
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
//        // y == z 说明 z 至多只有一个孩子
//        else
//        {
//            xp = y->parent;
//            if (_x)
//                _x->parent = y->parent;
//
//            // 连接 _x 与 z 的父节点
//            if (_root == z)
//                _root = _x;
//            else if (rb_tree_is_lchild(z))
//                z->parent->left = _x;
//            else
//                z->parent->right = _x;
//
//            // 此时 z 有可能是最左节点或最右节点，更新数据
//            if (leftmost == z)
//                leftmost = _x == nullptr ? xp : rb_tree_min(_x);
//            if (rightmost == z)
//                rightmost = _x == nullptr ? xp : rb_tree_max(_x);
//        }
//
//        // 此时，y 指向要删除的节点，_x 为替代节点，从 _x 节点开始调整。
//        // 如果删除的节点为红色，树的性质没有被破坏，否则按照以下情况调整（_x 为左子节点为例）：
//        // case 1: 兄弟节点为红色，令父节点为红，兄弟节点为黑，进行左（右）旋，继续处理
//        // case 2: 兄弟节点为黑色，且两个子节点都为黑色或 NIL，令兄弟节点为红，父节点成为当前节点，继续处理
//        // case 3: 兄弟节点为黑色，左子节点为红色或 NIL，右子节点为黑色或 NIL，
//        //         令兄弟节点为红，兄弟节点的左子节点为黑，以兄弟节点为支点右（左）旋，继续处理
//        // case 4: 兄弟节点为黑色，右子节点为红色，令兄弟节点为父节点的颜色，父节点为黑色，兄弟节点的右子节点
//        //         为黑色，以父节点为支点左（右）旋，树的性质调整完成，算法结束
//        if (!rb_tree_is_red(y))
//        { // _x 为黑色时，调整，否则直接将 _x 变为黑色即可
//            while (_x != _root && (_x == nullptr || !rb_tree_is_red(_x)))
//            {
//                if (_x == xp->left)
//                { // 如果 _x 为左子节点
//                    auto brother = xp->right;
//                    if (rb_tree_is_red(brother))
//                    { // case 1
//                        rb_tree_set_black(brother);
//                        rb_tree_set_red(xp);
//                        rb_tree_rotate_left(xp, _root);
//                        brother = xp->right;
//                    }
//                    // case 1 转为为了 case 2、3、4 中的一种
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
//                        // 转为 case 4
//                        brother->color = xp->color;
//                        rb_tree_set_black(xp);
//                        if (brother->right != nullptr)
//                            rb_tree_set_black(brother->right);
//                        rb_tree_rotate_left(xp, _root);
//                        break;
//                    }
//                }
//                else  // _x 为右子节点，对称处理
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
//                        // 转为 case 4
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
//    //------------------------------------------------红黑树设计-----------------------------------------------------------------
//    template<class T, class Comp, class Alloc = LT::allocator<T>>
//    class rb_tree
//    {
//        //照例定义类型
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
//        //成员变量
//    private:
//        base_ptr header_;
//        size_type nodeCount_;
//        key_compare keyComp_;
//
//    //**************************************************************************************************************************************
//    //****************************************************外部接口********************************************************************
//    //**************************************************************************************************************************************
//    public:
//        //-----------------------------------构造相关---------------------------------------------------
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
//        // 迭代器相关操作
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
//        // 容量相关操作
//
//        bool      empty()    const   { return !node_count_; }
//        size_type size()     const   { return node_count_; }
//        size_type max_size() const   { return static_cast<size_type>(-1); }
//        // 插入删除相关操作
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
//        // rb_tree 相关操作
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
//    //****************************************************内部实现********************************************************************
//    //**************************************************************************************************************************************
//    private:
//        // 以下三个函数用于取得根节点，最小节点和最大节点
//        base_ptr& __root()      const { return header_->parent; }
//        base_ptr& __leftmost()  const { return header_->left; }
//        base_ptr& __rightmost() const { return header_->right; }
//    
//    private:
//        //-----------------------------------------内存分配相关-----------------------------------------------------------------------
//        
//        typedef LT::allocator<base_type>        base_allocator;
//        typedef LT::allocator<node_type>        node_allocator;
//
//         node_ptr __get_one_node_mem()
//        {
//            //获得一个节点大小的内存区域，但是不初始化,如果分配失败，遇到空指针，将会中断程序
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
//        //-----------------------------------------构造相关的内部实现---------------------------------------------------------------
//        inline void __init()
//        {//无参数新建一颗树
//
//        }
//    };
//
//};
