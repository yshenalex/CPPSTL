#pragma once
#include<iostream>
using namespace std;
//搜索二叉树：单独key型
namespace K
{
	template<class K>
	struct BSTreeNode
	{
		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};


	template<class K>
	class BSTree
	{
		typedef struct BSTreeNode<K> Node;
	public:
		BSTree()
			:_root(nullptr)
		{}


		BSTree(const BSTree<K>& t)
		{
			_root = _Copy(t._root);
		}

		//BSTree<K>& operator=(const BSTree<K>& t)
		//{
		//	_root = _Copy(t._root);

		//	return *this;
		//}

		BSTree<K>& operator=(BSTree<K> t)
		{
			swap(t._root, _root);
			return *this;
		}


		~BSTree()
		{
			_Destroy(_root);
			_root = nullptr;
		}


		Node* Find(const K& x)
		{
			Node* cur = _root;

			while (cur)
			{
				if (cur->_key > x)
				{
					cur = cur->_left;
				}
				else if (cur->_key < x)
				{
					cur = cur->_right;
				}
				else
				{
					return cur;
				}
			}

			return nullptr;
		}

		bool Insert(const K& x)
		{
			//根为空就直接创建新节点
			if (!_root)
			{
				_root = new Node(x);
				return true;
			}


			Node* parent = nullptr;//保存双亲节点，因为后面插入的时候需要知道双亲结点
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > x)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < x)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}

			//直到cur为空时就插入
			cur = new Node(x);
			if (parent->_key > x)//区别一下是哪种情况
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}

			return true;
		}

		bool Erase(const K& x)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > x)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < x)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//三种情况：
					//1、左为空
					//2、右为空
					//3、左右都非空->替换删除
					if (!cur->_left)
					{
						if (cur == _root)//处理特殊情况：一开始就删除根节点。不然就涉及parent空指针访问
						{
							_root = cur->_right;

						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}

						delete cur;
					}
					else if (!cur->_right)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}

						delete cur;
					}
					else
					{
						//右子树最小(左)节点
						parent = cur;//先赋值为cur，而不是nullptr
						Node* minRight = cur->_right;

						while (minRight->_left)
						{
							parent = minRight;
							minRight = minRight->_left;
						}

						cur->_key = minRight->_key;
						if (minRight == parent->_left)
						{
							parent->_left = minRight->_right;
						}
						else
						{
							parent->_right = minRight->_right;
						}
						delete minRight;
					}
					return true;
				}
			}

			return false;
		}



		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}


	private:
		Node* _Copy(Node* root)
		{
			if (!root)
				return nullptr;

			Node* newroot = new Node(root->_key);
			newroot->_left = _Copy(root->_left);
			newroot->_right = _Copy(root->_right);

			return newroot;
		}

		void _Destroy(Node* root)//析构函数没办法递归，故如此处理
		{
			if (!root)
				return;

			_Destroy(root->_left);
			_Destroy(root->_right);
			delete root;
		}

		void _InOrder(Node* root)
		{
			if (!root)
				return;

			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}

	private:
		Node* _root = nullptr;
	};


}

//搜索二叉树：key,value型
namespace KV
{
	template<class K,class V>
	struct BSTreeNode
	{
		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key, const V& value)
			:_left(nullptr)
			,_right(nullptr)
			,_key(key)
			,_value(value)
		{}
	};


	template<class K, class V>
	class BSTree
	{
		typedef BSTreeNode<K, V> Node;
	public:
		BSTree()
			:_root(nullptr)
		{}

		~BSTree()
		{
			_Destroy(_root);
			_root = nullptr;
		}

		bool Insert(const K& key, const V& value)
		{
			if (!_root)
			{
				_root = new Node(key, value);
				return true;
			}


			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}

			cur = new Node(key, value);
			if (parent->_key < key)
				parent->_right = cur;
			else
				parent->_left = cur;

			return true;
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else
				{
					return cur;
				}
			}

			return nullptr;
		}

		void InOrder()
		{
			_InOrder(_root);
		}
	private:
		void _Destroy(Node* root)
		{
			if (!root)
				return;

			_Destroy(root->_left);
			_Destroy(root->_right);
			delete root;
		}

		void _InOrder(Node* root)
		{
			if (!root)
				return;

			_InOrder(root->_left);
			cout << root->_key << ":" << root->_value << endl;
			_InOrder(root->_right);
		}

	private:
		Node* _root;
	};
}