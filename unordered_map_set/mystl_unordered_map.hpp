#pragma once
#include "mystl_hashtable.hpp"

namespace mystl
{
    using SeparateChaining::DefaultHash;
    using SeparateChaining::HashTable;
    using std::make_pair;
    using std::pair;

    /**
     * @brief 通过Value值找到Key值
     *
     * @tparam _Key
     * @tparam _Value
     */
    template <typename _Key, typename _Value>
    struct MapKeyOfValue
    {
        const _Key &operator()(const pair<const _Key, _Value> &kv)
        {
            return kv.first;
        }
    };

    /**
     * @brief 模拟实现stl库的unordered_map
     * 
     * @tparam _Key 
     * @tparam _Value 
     * @tparam _Hash Key值变换为无符号整型的仿函数
     */
    template <typename _Key, typename _Value, typename _Hash = DefaultHash<_Key>>
    class unordered_map
    {
    public:
        using iterator = typename HashTable<_Key, pair<const _Key, _Value>, _Hash, MapKeyOfValue<_Key, _Value>>::iterator;
        using const_iterator = typename HashTable<_Key, pair<const _Key, _Value>, _Hash, MapKeyOfValue<_Key, _Value>>::const_iterator;

    public:
        unordered_map() = default;
        pair<iterator, bool> insert(const pair<const _Key, _Value> &kv);
        size_t erase(const _Key &key);
        size_t size();
        size_t size() const;
        bool empty();
        bool empty() const;
        iterator find(const _Key &key);
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        _Value &operator[](const _Key &key);

    private:
        // 直接删除，暂不考虑复制操作(省略深浅拷贝逻辑):
        unordered_map(const unordered_map<_Key, _Value> &) = delete;
        unordered_map<_Key, _Value> &operator=(const unordered_map<_Key, _Value> &) = delete;

    private:
        HashTable<_Key, pair<const _Key, _Value>, _Hash, MapKeyOfValue<_Key, _Value>> _hashtable;
    };

    template <typename _Key, typename _Value, typename _Hash>
    pair<typename unordered_map<_Key, _Value, _Hash>::iterator, bool> unordered_map<_Key, _Value, _Hash>::insert(const pair<const _Key, _Value> &kv)
    {
        return _hashtable.insert(kv);
    }

    template <typename _Key, typename _Value, typename _Hash>
    size_t unordered_map<_Key, _Value, _Hash>::erase(const _Key &key)
    {
        return _hashtable.erase(key);
    }

    template <typename _Key, typename _Value, typename _Hash>
    size_t unordered_map<_Key, _Value, _Hash>::size()
    {
        return _hashtable.size();
    }

    template <typename _Key, typename _Value, typename _Hash>
    size_t unordered_map<_Key, _Value, _Hash>::size() const
    {
        return _hashtable.size();
    }

    template <typename _Key, typename _Value, typename _Hash>
    bool unordered_map<_Key, _Value, _Hash>::empty()
    {
        return _hashtable.empty();
    }

    template <typename _Key, typename _Value, typename _Hash>
    bool unordered_map<_Key, _Value, _Hash>::empty() const
    {
        return _hashtable.empty();
    }

    template <typename _Key, typename _Value, typename _Hash>
    typename unordered_map<_Key, _Value, _Hash>::iterator unordered_map<_Key, _Value, _Hash>::find(const _Key &key)
    {
        return _hashtable.find(key);
    }

    template <typename _Key, typename _Value, typename _Hash>
    typename unordered_map<_Key, _Value, _Hash>::iterator unordered_map<_Key, _Value, _Hash>::begin()
    {
        return _hashtable.begin();
    }

    template <typename _Key, typename _Value, typename _Hash>
    typename unordered_map<_Key, _Value, _Hash>::const_iterator unordered_map<_Key, _Value, _Hash>::begin() const
    {
        return _hashtable.begin();
    }

    template <typename _Key, typename _Value, typename _Hash>
    typename unordered_map<_Key, _Value, _Hash>::iterator unordered_map<_Key, _Value, _Hash>::end()
    {
        return _hashtable.end();
    }

    template <typename _Key, typename _Value, typename _Hash>
    typename unordered_map<_Key, _Value, _Hash>::const_iterator unordered_map<_Key, _Value, _Hash>::end() const
    {
        return _hashtable.end();
    }

    template <typename _Key, typename _Value, typename _Hash>
    _Value &unordered_map<_Key, _Value, _Hash>::operator[](const _Key &key)
    {
        // 直接调用哈希表插入操作，如果本来就存在，就返回原来的引用，不存在就插入新值
        pair<iterator, bool> ret = _hashtable.insert(make_pair(key, _Value()));
        return ret.first->second; // 我们存储的是键值对，因此需要返回键值对的second
    }
}
