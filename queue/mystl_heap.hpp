#pragma once
#include <cstddef>
#include <utility>
namespace mystl
{

    using std::swap;

    /**
     * @brief 向下调整算法
     *
     * @tparam _RandomIt 支持随机存取迭代器
     * @tparam _Compare 比较器
     * @param first 起始位置
     * @param len 从其实位置开始的末尾长度
     * @param root 需要调整的节点相对于root的偏移量(即数组下标)
     * @param comp 比较器
     */
    template <typename _RandomIt, typename _Compare>
    void adjust_heap_down(_RandomIt first, size_t len, size_t root, _Compare comp)
    {
        size_t parent = root;
        size_t child = root * 2 + 1;

        while (child < len)
        {
            if (child + 1 < len && comp(*(first + child), *(first + child + 1)))
            {
                child++;
            }

            if (comp(*(first + parent), *(first + child)))
            {
                swap(*(first + parent), *(first + child));
                parent = child;
                child = parent * 2 + 1;
            }
            else
            {
                break;
            }
        }
    }

    /**
     * @brief 向上调整算法
     *
     * @tparam _RandomIt 支持随机存取迭代器
     * @tparam _Compare 比较器
     * @param first 起始迭代器
     * @param child 需要向上调整的节点相对于起始迭代器的偏移量(即下标)
     * @param comp 比较器
     */
    template <typename _RandomIt, typename _Compare>
    void adjust_heap_up(_RandomIt first, size_t child, _Compare comp)
    {

        size_t parent = (child - 1) / 2;

        while (child > 0)
        {
            if (comp(*(first + parent), *(first + child)))
            {
                swap(*(first + parent), *(first + child));
            }
            else
            {
                break;
            }

            child = parent;
            parent = (child - 1) / 2;
        }
    }

    /**
     * @brief 在[first, last)区间建堆
     *
     * @tparam _RandomIt 支持随机存取迭代器
     * @tparam _Compare 比较器
     * @param first 堆的底层空间的起始位置迭代器
     * @param last 堆底层空间的末尾位置迭代器
     * @param comp 比较器
     */
    template <typename _RandomIt, typename _Compare>
    void make_heap(_RandomIt first, _RandomIt last, _Compare comp)
    {
        // 如果区间只有1个或0个元素，则直接返回，不管
        if (last - first < 2)
            return;

        size_t n = last - first;
        for (size_t i = (n - 1 - 1) / 2;; i--)
        {
            // 从第一个分支节点开始，各自向下调整为堆
            mystl::adjust_heap_down(first, n, i, comp);

            if (i == 0)
                break;
        }
    }

    /**
     * @brief 堆的插入。将插在末尾的数据向上调整到合适位置
     *
     * @tparam _RandomIt 支持随机存取迭代器
     * @tparam _Compare 比较器
     * @param first 堆的底层空间的起始位置迭代器
     * @param last 堆底层空间的末尾位置迭代器
     * @param comp 比较器
     */
    template <typename _RandomIt, typename _Compare>
    void push_heap(_RandomIt first, _RandomIt last, _Compare comp)
    {
        if (last - first < 2)
            return;

        size_t pos = last - first - 1;
        mystl::adjust_heap_up(first, pos, comp); // 将插在末尾的数据向上调整到合适位置
    }

    /**
     * @brief 堆的删除。将堆顶的数据与堆末尾的元素调换，借助针对堆顶调用向下调整算法调整为堆
     *
     * @tparam _RandomIt 支持随机存取迭代器
     * @tparam _Compare 比较器
     * @param first 堆的底层空间的起始位置迭代器
     * @param last 堆底层空间的末尾位置迭代器
     * @param comp 比较器
     */
    template <typename _RandomIt, typename _Compare>
    void pop_heap(_RandomIt first, _RandomIt last, _Compare comp)
    {
        if (last - first < 2)
            return;

        swap(*first, *(last - 1));
        mystl::adjust_heap_down(first, last - first - 1, 0, comp);
    }

    /**
     * @brief 堆排序。将[first, last)排为有序
     *
     * @tparam _RandomIt 支持随机存取迭代器
     * @tparam _Compare 比较器
     * @param first 堆的底层空间的起始位置迭代器
     * @param last 堆底层空间的末尾位置迭代器
     * @param comp 比较器
     */
    template <typename _RandomIt, typename _Compare>
    void sort_heap(_RandomIt first, _RandomIt last, _Compare comp)
    {
        if (last - first < 2)
            return;

        mystl::make_heap(first, last, comp); // 区间的数据先建堆
        size_t n = last - first;
        for (size_t i = 0; i < n; i++)
        {
            // 不断将堆顶的元素置换到末尾，然后在视末尾节点已经不在的视图下调整其他元素为堆，循环。
            mystl::pop_heap(first, last - i, comp);
        }
    }

} // namespace mystl
