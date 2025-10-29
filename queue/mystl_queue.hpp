#pragma once
#include "mystl_heap.hpp"
#include <vector>
#include <cstddef>
#include <deque>

namespace mystl
{
	using std::deque;

	/**
	 * @brief 模拟实现stl的queue适配器
	 *
	 * @tparam T 元素数据类型
	 * @tparam Container 容器，默认使用双端队列deque
	 */
	template <typename _Tp, typename _Sequence = deque<_Tp>>
	class queue
	{
	public:
		void push(const _Tp &x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_front();
		}
		const _Tp &front()
		{
			return _con.front();
		}
		const _Tp &back()
		{
			return _con.back();
		}
		bool empty()
		{
			return _con.empty();
		}
		size_t size()
		{
			return _con.size();
		}

	protected:
		_Sequence _con;
	};
} // namespace mystl

namespace mystl
{
	using std::vector;

	/**
	 * @brief 小于比较器
	 * 
	 * @tparam T 
	 */
	template <typename T>
	struct Less
	{
		bool operator()(const T &x, const T &y) const
		{
			return x < y;
		}
	};

	/**
	 * @brief 大于比较器
	 * 
	 * @tparam T 
	 */
	template <typename T>
	struct Greater
	{
		bool operator()(const T &x, const T &y) const
		{
			return x > y;
		}
	};

	/**
	 * @brief 模拟实现stl库的priority_queue优先级队列
	 * 
	 * @tparam _Tp 数据类型
	 * @tparam _Sequence 容器，默认为vector
	 * @tparam _Compare 比较器，默认为小于比较器，建立大根堆
	 */
	template <typename _Tp, typename _Sequence = vector<_Tp>, typename _Compare = Less<_Tp>>
	class priority_queue
	{
	public:
		priority_queue();
		
		/**
		 * @brief 指定优先级队列比较器
		 * 
		 * @param com 比较器
		 */
		explicit priority_queue(const _Compare &com);
		
		/**
		 * @brief 将[first, last)区间元素复制下来，建立一个优先级队列
		 * 
		 * @tparam _InputIterator 迭代器
		 * @param first 起始迭代器
		 * @param last 末尾迭代器
		 */
		template <typename _InputIterator>
		explicit priority_queue(_InputIterator first, _InputIterator last);
		
		/**
		 * @brief 插入元素
		 * 
		 * @param val 
		 */
		void push(const _Tp &val);
		void push(_Tp &&val);

		/**
		 * @brief 删除优先级队列首元素(堆顶)
		 * 
		 */
		void pop();

		/**
		 * @brief 获取优先级队列首元素(堆顶)
		 * 
		 * @return const _Tp& 
		 */
		const _Tp &top() const;

		/**
		 * @brief 优先级队列大小
		 * 
		 * @return size_t 
		 */
		size_t size() const;

		/**
		 * @brief 判断优先级队列是否为空
		 * 
		 * @return true 空
		 * @return false 非空
		 */
		bool empty() const;

	protected:
		// 底层容器
		_Sequence _c;
		// 比较器
		_Compare _comp;
	};

	template <typename _Tp, typename _Sequence, typename _Compare>
	priority_queue<_Tp, _Sequence, _Compare>::priority_queue() : _c(), _comp()
	{
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	priority_queue<_Tp, _Sequence, _Compare>::priority_queue(const _Compare &com) : _c(), _comp(com)
	{
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	template <typename _InputIterator>
	priority_queue<_Tp, _Sequence, _Compare>::priority_queue(_InputIterator first, _InputIterator last)
		: _c(first, last), _comp()
	{
		mystl::make_heap(_c.begin(), _c.end(), _comp);
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	void priority_queue<_Tp, _Sequence, _Compare>::push(const _Tp &val)
	{
		_c.push_back(val); // 在末尾插入元素，接着把区间内的所有元素交给堆算法调整
		mystl::push_heap(_c.begin(), _c.end(), _comp);
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	void priority_queue<_Tp, _Sequence, _Compare>::push(_Tp &&val)
	{
		_c.push_back(std::move(val));
		mystl::push_heap(_c.begin(), _c.end(), _comp);
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	void priority_queue<_Tp, _Sequence, _Compare>::pop()
	{
		mystl::pop_heap(_c.begin(), _c.end(), _comp); // 调用堆删除算法(交换、调整)
		_c.pop_back(); // 堆顶要删除的元素已经保存在容器末尾，直接删除
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	const _Tp &priority_queue<_Tp, _Sequence, _Compare>::top() const
	{
		return _c.front();
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	size_t priority_queue<_Tp, _Sequence, _Compare>::size() const
	{
		return _c.size();
	}

	template <typename _Tp, typename _Sequence, typename _Compare>
	bool priority_queue<_Tp, _Sequence, _Compare>::empty() const
	{
		return _c.size() == 0;
	}

} // namespce mystl
