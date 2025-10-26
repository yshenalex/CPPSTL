#include<iostream>
#include<deque>
using namespace std;
namespace simulaton_stack
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
		const T& top()
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
		Container _con;
	};
}
int main()
{
	simulaton_stack::stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(5);
	st.push(6);

	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
	return 0;
}