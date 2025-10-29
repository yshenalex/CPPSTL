#pragma once
#include <iostream>
#include <cassert>
namespace mystl
{

	template <class T>
	struct __list_node
	{
		__list_node<T> *_next;
		__list_node<T> *_prev;
		T _val;

		__list_node(const T &x = T())
			: _next(nullptr), _prev(nullptr), _val(x)
		{
		}
	};

	template <class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> Self;
		Node *_node;

		__list_iterator(Node *node = nullptr) // 复制构造函数名字一定要是类名，不能是重命名后的名字Self
			: _node(node)
		{
		}

		bool operator!=(const Self &l) const
		// 提问：括号内为什么要加const?个思：因为this指针本质是*const 类型，
		// 而将两个元素进行比较的前提是类型要相同，因此也必须为const对象，
		// 否则使用时编译器会匹配不到而报错
		{
			return _node != l._node;
		}

		bool operator==(const Self &l) const
		{
			return _node == l._node;
		}

		Self &operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self operator++(int)
		{
			// Self tmp(*this);
			Self *tmp = this;
			_node = _node->_next;

			// return tmp;
			return *tmp;
		}

		Self &operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self *tmp = this;
			_node = _node->_prev;
			return *tmp;
		}

		Ref operator*()
		{
			return _node->_val;
		}

		Ptr operator->()
		{
			return &_node->_val;
		}
	};

	template <class _Tp>
	class list
	{
	private:
		typedef __list_node<_Tp> Node;

	public:
		typedef __list_iterator<_Tp, _Tp &, _Tp *> iterator;
		typedef __list_iterator<_Tp, const _Tp &, const _Tp *> const_iterator;

	public:
		list();
		list(int n, const _Tp &x);
		list(const list<_Tp> &lt);
		list<_Tp> &operator=(const list<_Tp> lt);
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		void push_back(const _Tp &x);
		void push_front(const _Tp &x);
		void pop_back();
		void pop_front();
		iterator insert(iterator pos, const _Tp &x);
		iterator erase(iterator pos);
		bool empty() const;
		void clear();
		~list();

	private:
		Node *_head;
	};

	template <class _Tp>
	list<_Tp>::list()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}

	template <class _Tp>
	list<_Tp>::list(int n, const _Tp &x)
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;

		for (int i = 0; i < n; i++)
			push_back(x);
	}

	template <class _Tp>
	list<_Tp>::list(const list<_Tp> &lt)
	{
		_head = new Node();
		_head->_next = _head;
		_head->_prev = _head;

		const_iterator it = lt.begin();
		while (it != lt.end())
		{
			push_back(*it);
			it++;
		}

		// 当然也可以用范围for, 支持迭代器就支持范围for:
		// for (auto e : lt)
		//	push_back(e);
	}

	template <class _Tp>
	list<_Tp> &list<_Tp>::operator=(const list<_Tp> lt)
	{
		std::swap(_head, lt._head);
		return *this;
	}

	/*
		//【复制运算符重载的另一种实现方式】：
		template <class _Tp>
		list<_Tp> &list<_Tp>::operator=(const list<_Tp> &lt)
		{
			if (*this != &lt)
			{
				clear();
				const_iterator it = lt.begin();
				while (it != lt.end())
				{
					push_back(*it);
					it++;
				}
			}
		}
	*/
	template <class _Tp>
	typename list<_Tp>::iterator list<_Tp>::begin()
	{
		return iterator(_head->_next);
	}

	template <class _Tp>
	typename list<_Tp>::const_iterator list<_Tp>::begin() const
	{
		return const_iterator(_head->_next);
	}

	template <class _Tp>
	typename list<_Tp>::iterator list<_Tp>::end()
	{
		return iterator(_head);
	}

	template <class _Tp>
	typename list<_Tp>::const_iterator list<_Tp>::end() const
	{
		return const_iterator(_head);
	}
	template <class _Tp>
	void list<_Tp>::push_back(const _Tp &x)
	{
		/*
			//【单独实现或调用insert都可以】:
			Node* newnode = new Node(x);
			Node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		*/
		insert(end(), x);
	}
	template <class _Tp>
	void list<_Tp>::push_front(const _Tp &x)
	{
		insert(begin(), x);
	}

	template <class _Tp>
	void list<_Tp>::pop_back()
	{
		erase(--end());
	}

	template <class _Tp>
	void list<_Tp>::pop_front()
	{
		erase(begin());
	}

	template <class _Tp>
	typename list<_Tp>::iterator list<_Tp>::insert(iterator pos, const _Tp &x)
	{
		Node *newnode = new Node(x);
		Node *prev = pos._node->_prev;
		Node *cur = pos._node;

		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = cur;
		cur->_prev = newnode;

		return iterator(newnode); // 在pos位置之前插入一个元素，返回新元素节点(pos上一个节点)
	}

	template <class _Tp>
	typename list<_Tp>::iterator list<_Tp>::erase(typename list<_Tp>::iterator pos)
	{
		assert(pos != end());

		Node *prev = pos._node->_prev;
		Node *next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;

		delete pos._node;

		return iterator(next);
	}

	template <class _Tp>
	bool list<_Tp>::empty() const
	{
		return _head == _head->_next;
	}

	template <class _Tp>
	void list<_Tp>::clear()
	{
		iterator it = begin();
		while (it != end())
		{
			it = erase(it);
		}
	}

	template <class _Tp>
	list<_Tp>::~list()
	{
		clear();
		delete _head;
		_head = nullptr;
	}

}
