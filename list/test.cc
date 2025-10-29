#include "mystl_list.hpp"
using mystl::list;
using std::cout;
using std::endl;
void Print_list(const list<int>& lt)
{
	typename list<int>::const_iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void testMylist1()
{
	list<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);

	lt.pop_back();
	lt.pop_back();
	lt.pop_back();

	list<int>lt2(lt);
	lt.clear();

	list<int>lt3 = lt2;
	
	Print_list(lt);
	Print_list(lt2);
	Print_list(lt3);
}
int main()
{
	testMylist1();
	return 0;
}
