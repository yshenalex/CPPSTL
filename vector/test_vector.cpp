#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void testVector1()//vector的构造
{

	vector<int>v1;//无参构造
	vector<int>v2(6, 66);//构造并初始化66个6
	vector<int>v3(v1);//复制构造
	vector<int>v4(v2.begin(), v2.end());//使用迭代器进行初始化构造

}
void PrintVector(const vector<int>& v)
{
	//const对象是用const迭代器进行遍历
	vector<int>::const_iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void testVector2()//vector遍历——与string类似
{
	vector<int>v1(5, 10);

	//1.使用operator[]
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
		//v.at(i) *= 2;
		//[]与at()的区别：前者用assert断言，后者遇错误时会抛异常
	}
	cout << endl;

	//2.1使用迭代器：
	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	//2.2当然也可以使用反向迭代器：
	vector<int>::reverse_iterator rit = v1.rbegin();
	while (rit != v1.rend())
	{
		cout << *rit << " ";
		rit++;
	}
	cout << endl;

	//2.3注意const对象遍历是用const_iterator迭代器，且不能修改对象
	PrintVector(v1);

	//3.范围for
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}
void testVector3()//容量函数
{
	vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	v.resize(4);

	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	cout << "v.capacity()=" << v.capacity() << endl;
	cout << "v.size()=" << v.size() << endl;
	cout << endl;

	v.resize(11, 0);
	cout << "v.capacity()=" << v.capacity() << endl;
	cout << "v.size()=" << v.size() << endl;

}

void testVector4()//push_back与pop_back
{
	vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.pop_back();
	v.pop_back();
	v.pop_back();

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

}
void testVector5()//find与insert
{
	vector<int>v;
	v.push_back(1);
	v.push_back(20);
	v.push_back(3);
	v.push_back(40);
	v.push_back(5);
	v.push_back(60);
	v.push_back(7);

	v.insert(v.begin() + 1, 4);
	v.insert(v.begin() + 3, 66);

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	vector<int>::iterator it = find(v.begin(), v.end(), 5);
	if (it != v.end())
	{
		v.insert(it, 30);//find位置之前插入
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;


}
void testVector6()//迭代器失效
{
	vector<int>v;
	for (size_t i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//情况一：由于增容导致失效：可能是push_back,resize,reserve,insert等
	//由于增容，可能释放旧空间，再开辟新空间，但是迭代器it没变，还是原来的位置，由此造成非法访问
	//vector<int>::iterator it = v.begin();
	//v.push_back(1);
	//v.push_back(2);
	//v.push_back(3);
	//v.push_back(4);
	//v.push_back(5);

	//while (it != v.end())
	//{
	//	(*it) *= 2;
	//	it++;
	//}


	//情况二：
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if ((*it) % 2 == 0)
		{
			//v.erase(it);

			//以[0,1,2,3,4,5,6,7,8,9]为例，删除2这个偶数后，
			//vector对象数据会挪动，此时失效的原因是it位置不对了，
			//it++相当于跳过了3的位置，在vs编译器中会报错，是编译检查的，
			//而在gcc中，不会报错，只是答案会出错

			//解决方案——利用erase()返回值
			it = v.erase(it);
		}

		it++;
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

}
int main()
{
	testVector1();
	testVector2();
	testVector3();
	testVector4();
	testVector5();
	testVector6();
	return 0;
}

