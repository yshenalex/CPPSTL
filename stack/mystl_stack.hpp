#pragma once
#include<iostream>
#include<deque>
namespace mystl
{
	using std::deque;
	/**
	 * @brief 模拟实现stl库的stack适配器，默认基于双端队列容器
	 * 
	 * @tparam _Tp 数据类型
	 * @tparam _Sequence 底层容器
	 */
	template<class _Tp, class _Sequence = deque<_Tp>>
	class stack
	{
	public:
		void push(const _Tp& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
		const _Tp& top()
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

	private:
		_Sequence _con;
	};
}
