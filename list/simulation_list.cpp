#include<iostream>
#include<assert.h>
using namespace std;
namespace simulation_list
{

	template<class T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _val;

		__list_node(const T& x = T())
			: _next(nullptr)
			, _prev(nullptr)
			, _val(x)
		{}
	};


	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> Self;
		Node* _node;

		__list_iterator(Node* node = nullptr)//复制构造函数名字一定要是类名，不能是重命名后的名字Self
			:_node(node)
		{}

		bool operator!=(const Self& l)const
			//提问：括号内为什么要加const?个思：因为this指针本质是*const 类型，
			//而将两个元素进行比较的前提是类型要相同，因此也必须为const对象，
			//否则使用时编译器会匹配不到而报错
		{
			return _node != l._node;
		}

		bool operator==(const Self& l)const
		{
			return _node == l._node;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self operator++(int)
		{
			//Self tmp(*this);
			Self* tmp = this;
			_node = _node->_next;

			//return tmp;
			return *tmp;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self* tmp = this;
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

	template<class T>
	class list
	{
		typedef __list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}

		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}
		
		const_iterator end()const
		{
			return const_iterator(_head);
		}


		void push_back(const T& x)
		{
			//Node* newnode = new Node(x);
			//Node* tail = _head->_prev;

			//tail->_next = newnode;
			//newnode->_prev = tail;
			//newnode->_next = _head;
			//_head->_prev = newnode;

			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}


		iterator insert(iterator pos, const T& x)//在pos位置之前插入一个元素，返回新元素节点(pos上一个节点)
		{
			Node* newnode = new Node(x);
			Node* prev = pos._node->_prev;
			Node* cur = pos._node;

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			return iterator(newnode);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			prev->_next = next;
			next->_prev = prev;

			delete pos._node;

			return iterator(next);
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		bool empty()
		{
			return _head == _head->_next;
		}

		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		list(int n, const T& x)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

			for (int i = 0; i < n; i++)
				push_back(x);
		}

		list(const list<T>& lt)
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

			//当然也可以用范围for, 支持迭代器就支持范围for:
			//for (auto e : lt)
			//	push_back(e);
		}


		//list<T>& operator=(const list<T>& lt)
		//{
		//	if (*this != &lt)
		//	{
		//		clear();
		//		const_iterator it = lt.begin();
		//		while (it != lt.end())
		//		{
		//			push_back(*it);
		//			it++;
		//		}
		//	}
		//}

		list<T>& operator=(const list<T> lt)
		{
			std::swap(_head, lt._head);
			return *this;
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
	private:
		Node* _head;
	};
}

void Print_list(const simulation_list::list<int>& lt)
{
	simulation_list::list<int>::const_iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void testMylist1()
{
	simulation_list::list<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);

	lt.pop_back();
	lt.pop_back();
	lt.pop_back();

	simulation_list::list<int>lt2(lt);
	lt.clear();

	simulation_list::list<int>lt3 = lt2;
	
	Print_list(lt);
	Print_list(lt2);
	Print_list(lt3);
}
int main()
{
	testMylist1();
	return 0;
}

