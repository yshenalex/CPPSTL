#include "mystl_stack.hpp"
#include <iostream>
using std::cout;
using std::endl;
using mystl::stack;
int main()
{
	stack<int> st;
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