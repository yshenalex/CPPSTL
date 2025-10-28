#include <vector>
#include <string>
#include <cassert>
namespace mystl
{
    using std::string;
    using std::vector;

    /**
     * @brief 模拟实现stl库的位图bitset
     * 
     * @tparam _N 位图位个数
     */
    template <size_t _N>
    class bitset
    {
    public:
        bitset();

        /**
         * @brief 将第i位设置为1
         * 
         * @param i 
         */
        void set(size_t i);

        /**
         * @brief 将第i位重置为0
         * 
         * @param i 
         */
        void reset(size_t i);

        /**
         * @brief 判断第i位是否已经设置了
         * 
         * @param i 
         * @return true 已经设置，即1
         * @return false 没有设置，即0
         */
        bool test(size_t i);

        /**
         * @brief 位图大小
         * 
         * @return size_t 
         */
        size_t size() const;

        /**
         * @brief 位图有效位个数(即存储1的位个数)
         * 
         * @return size_t 
         */
        size_t count() const;

        /**
         * @brief 位图用字符串形式显示
         * 
         * @return string 
         */
        string toString();

    private:
        vector<char> _bits;
        size_t _num;
    };

    template <size_t _N>
    bitset<_N>::bitset() : _num(0)
    {
        _bits.resize(_N / sizeof(char) + 1, 0);
    }

    template <size_t _N>
    void bitset<_N>::set(size_t i)
    {
        // 简化策略：断言
        assert(i < _N);

        size_t index = i / sizeof(char);
        size_t pos = i % sizeof(char);

        _bits[index] |= (1 << pos);
        _num++;
    }

    template <size_t _N>
    void bitset<_N>::reset(size_t i)
    {
        assert(i < _N);

        size_t index = i / sizeof(char);
        size_t pos = i % sizeof(char);

        _bits[index] &= ~(1 << pos);
        _num--;
    }

    template <size_t _N>
    bool bitset<_N>::test(size_t i)
    {
        assert(i < _N);
        size_t index = i / sizeof(char);
        size_t pos = i % sizeof(char);

        return _bits[index] & (1 << pos);
    }

    template <size_t _N>
    size_t bitset<_N>::size() const
    {
        return _N;
    }

    template <size_t _N>
    size_t bitset<_N>::count() const
    {
        return _num;
    }

    template <size_t _N>
    string bitset<_N>::toString()
    {
        string ret;
        size_t n = _N;
        while (n--)
        {
            ret += (test(n) == true ? '1' : '0');
        }
        return ret;
    }

}
