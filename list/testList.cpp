#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;

void testList1()//Constructor
{

	list<int>l1;
	list<int>l2(4, 100);
	list<int>l3(l2);
	list<int>l4(l2.begin(), l2.end());//左开右闭区间构造


	//以数组为迭代器构造：
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
	list<int>l5(arr, arr + sizeof(arr) / sizeof(arr[0]));


	//列表格式初始化,C++11:
	list<int>l6{ 1,2,3,4,5 };

}

void PrintList(const list<int>& l)
{
	list<int>::const_iterator it = l.begin();
	while (it != l.end())
	{
		//*it *= 2;
		//会报错，const修饰对象不可修改

		cout <<*it<< " ";
		it++;
	}
	cout << endl;
}
void testList2()//遍历list
{
	list<int>l1(6, 10);
	
	
	//1.迭代器：
	//正向：
	list<int>::iterator it = l1.begin();
	//auto it = l1.begin();//C++11支持语法
	while (it != l1.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	//反向：
	list<int>::reverse_iterator rit = l1.rbegin();
	while (rit != l1.rend())
	{
		cout << *rit << " ";
		rit++;
	}
	cout << endl;

	//2.范围for:
	for (auto e : l1)
	{
		cout << e << " ";
	}
	cout << endl;

	//const_iterator迭代器
	PrintList(l1);
}
void testList3()//头插头删，尾插尾删
{
	int arr[] = { 1,2,3 };

	list<int>l(arr, arr + sizeof(arr) / sizeof(arr[0]));

	l.push_back(4);
	l.push_front(0);

	for (auto e : l)
	{
		cout << e << " ";
	}
	cout << endl;

	l.pop_back();
	l.pop_front();

	for (auto e : l)
	{
		cout << e << " ";
	}
	cout << endl;

}

void testList4_1()//insert与erase
{
	list<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);
	lt.push_back(7);

	PrintList(lt);

	//想在3之前插入一个20
	list<int>::iterator pos = find(lt.begin(), lt.end(), 3);
	if (pos != lt.end())
	{
		lt.insert(pos, 20);
	}
	PrintList(lt);

	//在pos位置前插入[v.begin(),v.end())区间的元素
	vector<int>v{ 7,8,9 };
	lt.insert(pos, v.begin(), v.end());
	PrintList(lt);

	//删除pos位置上的元素
	lt.erase(pos);
	PrintList(lt);

	//删除list中[begin,end)区间中的元素，即删除list所有元素
	lt.erase(lt.begin(), lt.end());
	PrintList(lt);

}
void testList4_2()//list VS vector
{
	list<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);
	lt.push_back(7);
	PrintList(lt);

	//想在3之前插入一个20,然后删除
	list<int>::iterator pos1 = find(lt.begin(), lt.end(), 3);
	if (pos1 != lt.end())
	{
		lt.insert(pos1, 20);
		lt.erase(pos1);
	}
	PrintList(lt);

	//如果是vector呢？
	vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	for (auto e : v)
		cout << e << " ";
	cout << endl;

	//想在3之前插入一个20，然后删除
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	if (pos != v.end())
	{
		v.insert(pos, 20);
		v.erase(pos);
	}
	//结果：报错
	//原因：vector与list结构不同。
	//erase之后，一移动，pos意义已变，更要命的是，可能会增容完全换了一块空间。
	//总结：对于vector其insert,erase都可能会失效，
	//对于list,erase会失效(节点释放还指向它的情况)
}

void testList5()//迭代器失效：pos失效
{
	list<int>l;
	l.push_back(0);
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	l.push_back(7);

	list<int>::iterator pos = find(l.begin(), l.end(),3);
	if (pos != l.end())
	{
		l.insert(pos, 30);
	}
	for (auto e : l)
	{
		cout << e << " ";
	}
	cout << endl;

	l.erase(pos);
	
	//会报错：
	//cout << *pos << endl;
	//pos删除后结点被释放，再访问就报错了
}

void testList6()//resize,swap,clear,
{
	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	list<int>l1(arr, arr + sizeof(arr) / sizeof(arr[0]));
	PrintList(l1);

	l1.resize(15,66);
	PrintList(l1);

	//交换l1与l2中元素
	list<int>l2;
	swap(l1, l2);
	PrintList(l1);
	PrintList(l2);

	//清空l2中的元素
	l2.clear();
	cout << l2.size() << endl;
}

void testList7()//使用remove(),sort()与unique()
{
	list<int>l;
	l.push_back(2);
	l.push_back(7);
	l.push_back(1);
	l.push_back(9);
	l.push_back(3);
	l.push_back(7);
	l.push_back(5);
	l.push_back(4);
	l.push_back(6);
	l.push_back(0);
	l.push_back(8);
	l.push_back(7);


	l.remove(10);
	PrintList(l);

	l.sort();
	PrintList(l);

	l.unique();//需要注意的是：使用unique去重前必须先排序
	PrintList(l);
}

int main()
{
	testList1();
	testList2();
	testList3();
	testList4_1();
	testList4_2();
	testList5();
	testList6();
	testList7();

	return 0;
}

