#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <memory>

/**
 * @brief 使用拉链法解决哈希冲突，本代码依data-structrue仓库的HashTable.hpp改造
 *
 */
namespace SeparateChaining
{
	using std::cout;
	using std::endl;
	using std::make_pair;
	using std::pair;
	using std::string;
	using std::swap;
	using std::vector;

	/**
	 * @brief 默认数据类型映射为无符号整形的仿函数
	 *
	 * @tparam Key
	 */
	template <typename Key>
	struct DefaultHash
	{
		size_t operator()(const Key &x)
		{
			return static_cast<size_t>(x);
		}
	};

	/**
	 * @brief 对于字符串类型模板特化
	 *
	 */
	template <>
	struct DefaultHash<string>
	{
		size_t operator()(const string &s)
		{
			size_t hash = 0;
			for (auto &ch : s)
			{
				hash = hash * 131 + ch;
			}
			return hash;
		}
	};

	// 前向声明，迭代器与哈希表类互相使用
	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	class HashTable;

	/**
	 * @brief 哈希表节点
	 *
	 * @tparam T 节点存储数据类型
	 */
	template <typename T>
	struct __HashNode
	{
		// 节点存放数据
		T _data;
		// 指向下一节点指针
		__HashNode<T> *_next;

		__HashNode(T data = T())
			: _data(data), _next(nullptr)
		{
		}
	};

	/**
	 * @brief 哈希表迭代器
	 *
	 * @tparam Key 哈希表用于搜索查找的关键字
	 * @tparam Value 哈希表存储的数据类型
	 * @tparam Hash 哈希表元素数据类型映射为无符号整型仿函数
	 * @tparam KeyOfValue 通过哈希表存储的数据找到对应Key值的仿函数
	 * @tparam Ref 哈希表存储的数据类型引用
	 * @tparam Ptr 哈希表存储的数据类型指针
	 * @tparam HTPtr 哈希表的指针
	 */
	template <typename Key, typename Value, typename Hash, typename KeyOfValue, typename Ref, typename Ptr, typename HTPtr>
	// 作为HashTable友元，模板参数名不要与外层HashTable模板参数名相同，否则导致内层参数覆盖外层参数，编译器报错
	struct __HashTableIterator
	{
		using Node = __HashNode<Value>;
		using Self = __HashTableIterator<Key, Value, Hash, KeyOfValue, Ref, Ptr, HTPtr>;

		// 迭代器存储的节点指针
		Node *_node;
		// 迭代器所属的哈希表的指针
		HTPtr _hst;

		__HashTableIterator(Node *node, HTPtr hst)
			: _node(node), _hst(hst)
		{
		}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &(_node->_data);
		}

		bool operator==(const Self &it) const
		{
			return _node == it._node;
		}

		bool operator!=(const Self &it) const
		{
			return _node != it._node;
		}

		Self &operator++()
		{
			// 该节点所在链表下直接后继不为空，则直接更改为后继节点
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// 如果为空，则应该去寻找哈希表的后续第一个非空链表头节点
				size_t pos = _hst->_hash(KeyOfValue()(_node->_data));
				bool flag = false; // 标记位，是否找到了非空链表头节点
				for (int i = pos + 1; i < _hst->_buckets.size(); i++)
				{
					if ((_hst->_buckets)[i])
					{
						_node = _hst->_buckets[i];
						flag = true;
						break;
					}
				}

				// 后面没有了，直接置为空
				if (!flag)
					_node = nullptr;
			}

			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this); // 使用默认拷贝构造函数
			++(*this);
			return tmp;
		}
	};

	/**
	 * @brief 哈希表
	 * 
	 * @tparam _Key 哈希表用于搜索查找的关键字
	 * @tparam _Value 哈希表存储的数据类型
	 * @tparam _Hash 哈希表元素数据类型映射为无符号整型仿函数
	 * @tparam _KeyOfValue 通过哈希表存储的数据找到对应Key值的仿函数
	 */
	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	class HashTable
	{
	private:
		using Node = __HashNode<_Value>;
		
		// 迭代器是哈希表的友元
		template <typename Key, typename Value, typename Hash, typename KeyOfValue, typename Ref, typename Ptr, typename HTPtr>
		friend struct __HashTableIterator;

	public:
		using Self = HashTable<_Key, _Value, _Hash, _KeyOfValue>;
		using iterator = __HashTableIterator<_Key, _Value, _Hash, _KeyOfValue, _Value &, _Value *, Self *>;
		using const_iterator = __HashTableIterator<_Key, _Value, _Hash, _KeyOfValue, const _Value &, const _Value *, const Self *>;

	public:
		HashTable();
		/**
		 * @brief 插入一个元素
		 * 
		 * @param data 
		 * @return pair<iterator, bool> 插入位置迭代器和是否插入成功布尔类型构成的pair
		 */
		pair<iterator, bool> insert(const _Value &data);

		/**
		 * @brief 删除一个元素
		 * 
		 * @param key 要删除的元素的Key值
		 * @return 1 成功
		 * @return 0 失败
		 */
		size_t erase(const _Key &key);

		/**
		 * @brief 通过Key值查找元素
		 * 
		 * @param key 通过Key值查找
		 * @return iterator 成功就是元素的迭代器，失败则是end()
		 */
		iterator find(const _Key &key);
		/**
		 * @brief 通过Key值查找元素
		 * 
		 * @param key 通过Key值查找
		 * @return const_iterator 成功就是元素的迭代器，失败则是end()
		 */
		const_iterator find(const _Key &key) const;

		/**
		 * @brief 得到哈希表首元素
		 * 
		 * @return iterator 首元素迭代器，若无元素，则是end()
		 */
		iterator begin();

		/**
		 * @brief 得到哈希表首元素
		 * 
		 * @return const_iterator 首元素迭代器，若无元素，则是end()
		 */
		const_iterator begin() const;

		/**
		 * @brief 哈希表末尾元素下一个元素，也即是iterator/const_iterator(nullptr, ...)
		 * 
		 * @return iterator 指向空节点迭代器
		 */
		iterator end();

		/**
		 * @brief 哈希表末尾元素下一个元素，也即是iterator/const_iterator(nullptr, ...)
		 * 
		 * @return const_iterator 指向空节点迭代器
		 */
		const_iterator end() const;

		/**
		 * @brief 哈希表大小
		 * 
		 * @return size_t 
		 */
		size_t size() const;

		/**
		 * @brief 哈希表是否为空
		 * 
		 * @return true 成功
		 * @return false 失败
		 */
		bool empty() const;

		~HashTable();

	private:
		/**
		 * @brief 哈希函数，先调用仿函数Hash()()将Key值转换为无符号整型，然后再将整型对哈希表桶数除留取余
		 * 
		 * @param key 传入的Key值
		 * @return size_t [0, buckets.size() - 1]范围内的无符号整型
		 */
		size_t _hash(const _Key &key) const;
		
		/**
		 * @brief 再散列，扩容操作，将哈希表扩容后，重新把元素挂入新的哈希表中
		 * 
		 */
		void _rehashing();

		/**
		 * @brief 借用stl库的实现。获取下一个合适的素数作为哈希表桶个数
		 * 
		 * @param n 原有的个数
		 * @return size_t 新的可以作为哈希表桶个数的素数
		 */
		size_t _next_prime(size_t n) const;

	private:
		// 底层使用vector存储哈希桶
		vector<Node *> _buckets;
		// 哈希表有效数据个数
		size_t _n;
	};

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	HashTable<_Key, _Value, _Hash, _KeyOfValue>::HashTable() : _n(0)
	{
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	pair<typename HashTable<_Key, _Value, _Hash, _KeyOfValue>::iterator, bool> HashTable<_Key, _Value, _Hash, _KeyOfValue>::insert(const _Value &data)
	{
		if (_buckets.size() == 0)					  // 哈希表第一次插入数据时初始化空间
			_buckets.resize(_next_prime(0), nullptr); // 实际不是初始化为0，而是53，详看_next_prime定义

		iterator it = find(_KeyOfValue()(data));
		if (it != end())
			return make_pair(it, false);

		if (_n == _buckets.size()) // 如果插入的数据个数与哈希表桶数(链表个数之和)相等就扩容
			_rehashing();

		size_t pos = _hash(_KeyOfValue()(data));
		// OPTIMIZE: 此处可以按序插入，形成有序链表，这样查找效率为提高
		// 头插法
		Node *newNode = new Node(data);
		newNode->_next = _buckets[pos];
		_buckets[pos] = newNode;
		_n++;

		return make_pair(iterator(newNode, this), true);
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	size_t HashTable<_Key, _Value, _Hash, _KeyOfValue>::erase(const _Key &key)
	{
		// 无数据，直接返回0
		if (_n == 0)
			return 0;

		// 先计算元素所在的哈希桶标号
		size_t pos = _hash(key);

		// 遍历链表删除
		Node *parent = nullptr;
		Node *cur = _buckets[pos];
		while (cur)
		{
			if (_KeyOfValue()(cur->_data) == key)
			{
				if (parent)
					parent->_next = cur->_next;
				else
					_buckets[pos] = cur->_next; // parent为空说明是链头

				delete cur;
				_n--;
				return 1;
			}

			parent = cur;
			cur = cur->_next;
		}

		return 0;
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	typename HashTable<_Key, _Value, _Hash, _KeyOfValue>::iterator HashTable<_Key, _Value, _Hash, _KeyOfValue>::find(const _Key &key)
	{
		// 无数据，直接返回iterator(nullptr, this), 也就是end()
		if (_n == 0)
			return iterator(nullptr, this);

		// 先计算元素理应所在的哈希桶标号
		size_t pos = _hash(key);
		// 遍历对应链表查找
		Node *cur = _buckets[pos];
		while (cur)
		{
			if (_KeyOfValue()(cur->_data) == key)
				return iterator(cur, this);

			cur = cur->_next;
		}
		return end();
	}
	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	typename HashTable<_Key, _Value, _Hash, _KeyOfValue>::const_iterator HashTable<_Key, _Value, _Hash, _KeyOfValue>::find(const _Key &key) const
	{
		// 无数据，直接返回指向末尾迭代器, 也就是end()
		if (_n == 0)
			return end();

		size_t pos = _hash(key);
		Node *cur = _buckets[pos];
		while (cur)
		{
			if (_KeyOfValue()(cur->_data) == key)
				return const_iterator(cur, this);
			cur = cur->_next;
		}
		return end();
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	typename HashTable<_Key, _Value, _Hash, _KeyOfValue>::iterator HashTable<_Key, _Value, _Hash, _KeyOfValue>::begin()
	{
		for (int i = 0; i < _buckets.size(); i++)
		{
			if (_buckets[i])
				return iterator(_buckets[i], this);
		}
		return iterator(nullptr, this);
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	typename HashTable<_Key, _Value, _Hash, _KeyOfValue>::const_iterator HashTable<_Key, _Value, _Hash, _KeyOfValue>::begin() const
	{
		for (int i = 0; i < _buckets.size(); i++)
		{
			if (_buckets[i])
				return const_iterator(_buckets[i], this);
		}
		return const_iterator(nullptr, this);
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	typename HashTable<_Key, _Value, _Hash, _KeyOfValue>::iterator HashTable<_Key, _Value, _Hash, _KeyOfValue>::end()
	{
		return iterator(nullptr, this); // end我们设计为iterator(nullptr, this)
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	typename HashTable<_Key, _Value, _Hash, _KeyOfValue>::const_iterator HashTable<_Key, _Value, _Hash, _KeyOfValue>::end() const
	{
		return const_iterator(nullptr, this);
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	size_t HashTable<_Key, _Value, _Hash, _KeyOfValue>::size() const
	{
		return _n;
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	bool HashTable<_Key, _Value, _Hash, _KeyOfValue>::empty() const
	{
		return _n == 0;
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	HashTable<_Key, _Value, _Hash, _KeyOfValue>::~HashTable()
	{
		// 把每个链表分别析构
		for (int i = 0; i < _buckets.size(); i++)
		{
			Node *cur = _buckets[i];
			while (cur)
			{
				Node *next = cur->_next;
				delete cur;
				cur = next;
			}
			// 不要忘记把哈希表各个初始节点置空，否则析构函数调用时将导致重复释放资源错误
			_buckets[i] = nullptr;
		}
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	size_t HashTable<_Key, _Value, _Hash, _KeyOfValue>::_hash(const _Key &key) const
	{
		return _Hash()(key) % _buckets.size();
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	void HashTable<_Key, _Value, _Hash, _KeyOfValue>::_rehashing()
	{
		HashTable<_Key, _Value, _Hash, _KeyOfValue> newHashTable;

		// 我们希望哈希表长度为素数
		int newSize = _next_prime(_buckets.size());
		newHashTable._buckets.resize(newSize, nullptr);

		// 原哈希表的数据逐个重新插入到新哈希表中
		for (int i = 0; i < _buckets.size(); i++)
		{
			Node *cur = _buckets[i];
			// 此处不直接调用insert，而是直接将当前哈希表的节点链到新哈希表上，减少拷贝，提高效率
			while (cur)
			{
				Node *next = cur->_next;

				size_t pos = newHashTable._hash(_KeyOfValue()(cur->_data));
				cur->_next = newHashTable._buckets[pos];
				newHashTable._buckets[pos] = cur;
				newHashTable._n++;

				cur = next;
			}
			// 不要忘记把哈希表各个初始节点置空，否则析构函数调用时将导致重复释放资源错误
			_buckets[i] = nullptr;
		}

		this->_n = 0;

		swap(*this, newHashTable);
	}

	template <typename _Key, typename _Value, typename _Hash, typename _KeyOfValue>
	size_t HashTable<_Key, _Value, _Hash, _KeyOfValue>::_next_prime(size_t n) const
	{
		static const int __stl_num_primes = 28;
		static const size_t __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291};

		for (int i = 0; i < __stl_num_primes; ++i)
		{
			if (__stl_prime_list[i] > n)
			{
				return __stl_prime_list[i];
			}
		}

		return __stl_prime_list[__stl_num_primes - 1];
	}
}