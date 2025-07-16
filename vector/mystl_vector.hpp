#include <iostream>
#include <cassert>

namespace mystl
{
    template <typename _Tp> //_Tp: type of element
    class vector
    {
    public:
        typedef _Tp *iterator;
        typedef const _Tp *const_iterator;

    public:
        vector();
        vector(const vector<_Tp> &__v);
        vector(size_t __n, const _Tp &__val = _Tp());
        vector<_Tp> &operator=(vector<_Tp> __v);
        ~vector();

        size_t capacity() const;
        size_t size() const;
        bool empty() const;
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        _Tp &operator[](size_t __pos);
        const _Tp &operator[](size_t __pos) const;

        void reserve(size_t __n);
        void resize(size_t __n, const _Tp &__val = _Tp());
        void push_back(const _Tp &__val);
        void pop_back();
        iterator insert(iterator __pos, const _Tp &__val);
        iterator erase(iterator __pos);

        // c++11新特性：
        vector(std::initializer_list<_Tp> __l);
        vector<_Tp> &operator=(std::initializer_list<_Tp> __l);
        vector(vector<_Tp> &&__v) noexcept;
        vector<_Tp> &operator=(vector<_Tp> &&__v) noexcept;
        void push_back(_Tp &&__val);
        iterator insert(iterator __pos, _Tp &&__val);

    private:
        iterator _M_start;
        iterator _M_finish;
        iterator _M_end_of_storage;
    };

    template <typename _Tp>
    vector<_Tp>::vector() : _M_start(nullptr), _M_finish(nullptr), _M_end_of_storage(nullptr) {}

    template <typename _Tp>
    vector<_Tp>::vector(const vector<_Tp> &__v) : _M_start(nullptr), _M_finish(nullptr), _M_end_of_storage(nullptr)
    {
        size_t size = __v.size();
        reserve(size);
        for (size_t i = 0; i < size; i++)
            push_back(__v[i]);
    }

    template <typename _Tp>
    vector<_Tp>::vector(size_t __n, const _Tp &__val) : _M_start(nullptr), _M_finish(nullptr), _M_end_of_storage(nullptr)
    {
        reserve(__n);
        for (size_t i = 0; i < __n; i++)
            push_back(__val);
    }

    template <typename _Tp>
    vector<_Tp> &vector<_Tp>::operator=(vector<_Tp> __v)
    {
        if (this != &__v)
        {
            std::swap(_M_start, __v._M_start);
            std::swap(_M_finish, __v._M_finish);
            std::swap(_M_end_of_storage, __v._M_end_of_storage);
        }
        return *this;
    }

    template <typename _Tp>
    vector<_Tp>::~vector()
    {
        delete[] _M_start;
        _M_start = _M_finish = _M_end_of_storage = nullptr;
    }

    template <typename _Tp>
    size_t vector<_Tp>::capacity() const
    {
        if (!_M_start)
            return 0;

        return _M_end_of_storage - _M_start;
    }

    template <typename _Tp>
    size_t vector<_Tp>::size() const
    {
        if (!_M_start)
            return 0;

        return _M_finish - _M_start;
    }

    template <typename _Tp>
    bool vector<_Tp>::empty() const
    {
        return _M_start == _M_finish;
    }

    template <typename _Tp>
    typename vector<_Tp>::iterator vector<_Tp>::begin()
    {
        return _M_start;
    }

    template <typename _Tp>
    typename vector<_Tp>::const_iterator vector<_Tp>::begin() const
    {
        return _M_start;
    }

    template <typename _Tp>
    typename vector<_Tp>::iterator vector<_Tp>::end()
    {
        return _M_finish;
    }

    template <typename _Tp>
    typename vector<_Tp>::const_iterator vector<_Tp>::end() const
    {
        return _M_finish;
    }

    template <typename _Tp>
    _Tp &vector<_Tp>::operator[](size_t __pos)
    {
        assert(__pos >= 0 && __pos < size());
        return *(_M_start + __pos);
    }

    template <typename _Tp>
    const _Tp &vector<_Tp>::operator[](size_t __pos) const
    {
        assert(__pos >= 0 && __pos < size());
        return *(_M_start + __pos);
    }

    template <typename _Tp>
    void vector<_Tp>::reserve(size_t __n)
    {
        if (__n <= capacity())
            return;

        _Tp *tmp = new _Tp[__n];
        size_t sz = size();

        if (_M_start)
        {
            for (size_t i = 0; i < sz; i++)
                tmp[i] = std::move(_M_start[i]); // 使用移动语义, 对于int这种类型固然没用，但如果是自定义类或string等将可以提高效率

            delete[] _M_start;
        }

        _M_start = tmp;
        _M_finish = _M_start + sz;
        _M_end_of_storage = _M_start + __n;
    }
    template <typename _Tp>
    void vector<_Tp>::resize(size_t __n, const _Tp &__val)
    {
        if (__n > size())
        {
            reserve(__n);
            size_t old_size = size();
            for (size_t i = old_size; i < __n; i++)
                push_back(__val);
        }

        _M_finish = _M_start + __n;
    }
    template <typename _Tp>
    void vector<_Tp>::push_back(const _Tp &__val)
    {
        insert(_M_finish, __val);
    }
    template <typename _Tp>
    void vector<_Tp>::pop_back()
    {
        erase(_M_finish - 1);
    }
    template <typename _Tp>
    typename vector<_Tp>::iterator vector<_Tp>::insert(iterator __pos, const _Tp &__val)
    {
        assert(__pos >= _M_start && __pos <= _M_finish);

        if (_M_finish == _M_end_of_storage)
        {
            size_t len = __pos - _M_start; // 记录__pos偏移位置，防止迭代器失效(扩容后可能另辟空间)
            size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
            reserve(newCapacity);

            __pos = _M_start + len; // 更新__pos的值
        }

        iterator it = _M_finish;
        while (it != __pos)
        {
            *it = std::move(*(it - 1)); // 使用移动语义
            it--;
        }

        *__pos = __val;
        _M_finish++;

        return __pos;
    }
    template <typename _Tp>
    typename vector<_Tp>::iterator vector<_Tp>::erase(iterator __pos)
    {
        assert(!empty()); // 做空容器判断，否则可能存在未定义问题。比如，删除最后一个，使用_M_finish-1将越界。
        assert(__pos >= _M_start && __pos < _M_finish);

        iterator it = __pos;
        while ((it + 1) != _M_finish)
        {
            *it = std::move(*(it + 1));
            it++;
        }

        _M_finish--;
        return __pos;
    }

    template <typename _Tp>
    vector<_Tp>::vector(std::initializer_list<_Tp> __l) : _M_start(nullptr), _M_finish(nullptr), _M_end_of_storage(nullptr)
    {
        _M_start = new _Tp[__l.size()];
        _M_finish = _M_end_of_storage = _M_start + __l.size();
        iterator vit = _M_start;
        typename std::initializer_list<_Tp>::iterator it = __l.begin();
        while (it != __l.end())
        {
            *vit++ = *it++;
        }
    }

    template <typename _Tp>
    vector<_Tp> &vector<_Tp>::operator=(std::initializer_list<_Tp> __l)
    {
        vector<_Tp> tmp(__l);
        std::swap(tmp._M_start, this->_M_start);
        std::swap(tmp._M_finish, this->_M_finish);
        std::swap(tmp._M_end_of_storage, this->_M_end_of_storage);
        return *this;
    }

    template <typename _Tp>
    vector<_Tp>::vector(vector<_Tp> &&__v) noexcept
        : _M_start(__v._M_start), _M_finish(__v._M_finish), _M_end_of_storage(__v._M_end_of_storage)
    {
        __v._M_start = __v._M_finish = __v._M_end_of_storage = nullptr;
    }

    template <typename _Tp>
    vector<_Tp> &vector<_Tp>::operator=(vector<_Tp> &&__v) noexcept
    {
        if (this != &__v)
        {
            delete[] _M_start;
            _M_start = __v._M_start;
            _M_finish = __v._M_finish;
            _M_end_of_storage = __v._M_end_of_storage;

            __v._M_start = __v._M_finish = __v._M_end_of_storage = nullptr;
        }

        return *this;
    }

    template <typename _Tp>
    void vector<_Tp>::push_back(_Tp &&__val)
    {
        insert(_M_finish, std::move(__val));
    }

    template <typename _Tp>
    typename vector<_Tp>::iterator vector<_Tp>::insert(iterator __pos, _Tp &&__val)
    {
        assert(__pos >= _M_start && __pos <= _M_finish);
        if (_M_finish == _M_end_of_storage)
        {
            size_t len = __pos - _M_start;
            size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
            reserve(newCapacity);
        }
        iterator it = _M_finish;
        while (it != __pos)
        {
            *it = std::move(*(it - 1));
            it--;
        }

        *__pos = std::move(__val);
        _M_finish++;
        return __pos;
    }

};