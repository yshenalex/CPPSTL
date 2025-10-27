#pragma once
#include "mystl_hashtable.hpp"

namespace mystl
{
	using SeparateChaining::HashTable;
	using SeparateChaining::DefaultHash;
	using std::pair;

	/**
	 * @brief 通过Value值找Key值，对于unordered_set只有value
	 *  
	 * @tparam _Tp 
	 */
	template<typename _Tp>
	struct SetKeyOfValue
	{
		const _Tp& operator()(const _Tp& x)
		{
			return x;
		}
	};

	/**
	 * @brief 模拟实现stl库的unordered_set
	 * 
	 * @tparam _Tp 存储元素数据类型
	 * @tparam _Hash 存储元素数据转换为无符号整型仿函数
	 */
	template<typename _Tp, typename _Hash = DefaultHash<_Tp>>
	class unordered_set
	{
	public:
		using iterator = typename HashTable<_Tp, _Tp, _Hash, SetKeyOfValue<_Tp>>::iterator;
		using const_iterator = typename HashTable<_Tp, _Tp, _Hash, SetKeyOfValue<_Tp>>::const_iterator;
	public:
		unordered_set() = default;
		pair<iterator, bool> insert(const _Tp& val);
		size_t erase(const _Tp& val);
		iterator find(const _Tp& val);
		const_iterator find(const _Tp& val) const;
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		bool empty()const;
		size_t size() const;
	private:
		unordered_set<_Tp, _Hash>& operator=(const unordered_set<_Tp, _Hash>&) = delete;
		unordered_set(const unordered_set<_Tp, _Hash>&) = delete;
	private:
		HashTable<_Tp, _Tp, _Hash, SetKeyOfValue<_Tp>> _hashtable;
	};


	template<typename _Tp, typename _Hash>
	pair<typename unordered_set<_Tp, _Hash>::iterator, bool> unordered_set<_Tp, _Hash>::insert(const _Tp& val)
	{
		return _hashtable.insert(val);
	}

	template<typename _Tp, typename _Hash>
	size_t unordered_set<_Tp, _Hash>::erase(const _Tp& val)
	{
		return _hashtable.erase(val);
	}

	template<typename _Tp, typename _Hash>
	typename unordered_set<_Tp, _Hash>::iterator unordered_set<_Tp, _Hash>::find(const _Tp& val)
	{
		return _hashtable.find(val);
	}

	template<typename _Tp, typename _Hash>
	typename unordered_set<_Tp, _Hash>::const_iterator unordered_set<_Tp, _Hash>::find(const _Tp& val) const
	{
		return _hashtable.find(val);
	}

	template<typename _Tp, typename _Hash>
	bool unordered_set<_Tp, _Hash>::empty()const
	{
		return _hashtable.empty();
	}


	template<typename _Tp, typename _Hash>
	size_t unordered_set<_Tp, _Hash>::size() const
	{
		return _hashtable.size();
	}

	template<typename _Tp, typename _Hash>
	typename unordered_set<_Tp, _Hash>::iterator unordered_set<_Tp, _Hash>::begin()
	{
		return _hashtable.begin();
	}

	template<typename _Tp, typename _Hash>
	typename unordered_set<_Tp, _Hash>::const_iterator unordered_set<_Tp, _Hash>::begin() const
	{
		return _hashtable.begin();
	}

	template<typename _Tp, typename _Hash>
	typename unordered_set<_Tp, _Hash>::iterator unordered_set<_Tp, _Hash>::end()
	{
		return _hashtable.end();
	}

	template<typename _Tp, typename _Hash>
	typename unordered_set<_Tp, _Hash>::const_iterator unordered_set<_Tp, _Hash>::end() const
	{
		return _hashtable.end();
	}

}