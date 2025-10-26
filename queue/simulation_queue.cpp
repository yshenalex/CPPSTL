#include<iostream>
#include<deque>
using namespace std;
namespace simulation_queue
{
	template<class T, class Container = deque<T>>
	class queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_front();
		}
		const T& front()
		{
			return _con.front();
		}
		const T& back()
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
	simulation_queue::queue<int> q;
	q.push(1);
	q.push(3);
	q.push(5);
	q.push(7);
	q.push(8);
	q.push(2);
	q.push(9);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		cout << q.back() << " ";
		q.pop();
	}
	cout << endl;
	return 0;
}

