#include<iostream>
#include<string>
using namespace std;
void teststring1()//Construct string object
{
	string s1;
	string s2("Hello world!");
	string s3(s2);//用s2拷贝构造s3
	
	string s4 = "Hello world!";
	//此处本质是隐藏类型转换，相当于之前把double赋值给int,发生隐式类型转换
	
	string s5(10, 'a');

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
}
void teststring2()//Capacity：size,capacity,empty
{
	string s1("Hello world!");

	cout<<"s1.size()="<<s1.size() << endl;
	cout <<"s1.capacity()="<< s1.capacity() << endl;//返回空间大小；注：增容后会有内存对齐的因素
	cout <<"s1.empty()="<<s1.empty() << endl;//判断字符串是否为空
	
	cout << "-------------------------" << endl;
	s1.clear();//注：删除后只改变size大小，不会改变底层空间capacity的大小
	cout << "s1调用clear()后：s1=" << s1 << endl;
	cout << "s1调用clear()后：s1.capacity()=" << s1.capacity() << endl;
}
void teststring3()
{
	string s1("Hello world!");
	string s2("Hello!");

	s1.reserve(5);
	s2.reserve(20);

	//【1】reserve(size_t res_arg=0)：为string预留空间，不改变有效元素个数
	//【2】当reserve的参数小于string的底层空间总大小时，reserve不会改变容量大小。
	// 利用reserve可以提高插入数据效率，避免增容带来的开销
}
void teststring4()
{
	string s1("Hello world!");

	s1.resize(15); //将s中有效字符个数增加到15个，多出位置用缺省值'\0'进行填充
	cout << s1 << endl;
	s1.resize(50, 'x');
	cout << s1 << endl;
	// resize(size_t n) 与 resize(size_t n, char c)都是将字符串中有效字符个数改变到n个，
	// 不同的是当字符个数增多时：resize(n)用\0来填充多出的元素空间，resize(size_t n, char c)用字符c来填充多出的元素空间。
	// 注意：resize在改变元素个数时，如果是将元素个数增多，可能会改变底层容量的大小，如果是将元素个数减少，底层空间总大小不变。

}
void teststring7()//观察string插入数据时，增容情况
{
	string s;
	s.reserve(100);//利用reserve可以提高插入数据效率，避免增容带来的开销

	size_t sz = s.capacity();
	cout << "capacity changed:" << sz << endl;
	cout << "size:" << s.size() << endl;
	cout << "push_back:" << "Hello world!" << endl;

	for (int i = 0; i < 500; i++)
	{
		s.push_back('x');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed:" << sz << endl;
		}
	}

	//调用reserve(100)时，capacity并不一定等于100，因为要考虑内存对齐
	//在vs2022编译器中，string每次增容为原来的1.5倍
}
void teststring5()//三种遍历string的方法
{
	string s1("Hello world!");
	const string s2 = s1;//只读

	//1.for+operator[]——最常用
	for (size_t i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
	}
	cout << endl << endl;

	//2.迭代器
	//(1)可读可写
	string::iterator it1 = s1.begin();
	while (it1 != s1.end())
	{
		cout << *it1 << " ";
		it1++;
	}
	cout << endl << endl;

	//(2)c++11后还可以使用auto定义迭代器，让编译器推导迭代器的类型
	auto rit = s1.rbegin();
	while(rit!=s1.rend())//此处尝试逆序打印
	{
		cout << *rit << " ";
		rit++;//利用rbegin和rend时，此处仍然是++而非--
	}
	cout << endl << endl;

	//(3)只读
	string::const_iterator it2 = s2.begin();
	while (it2 != s2.end())
	{
		cout << *it2 << " ";
		it2++;
	}
	cout << endl << endl;

	//3.范围for
	for (auto ch : s1)
	{
		cout << ch << " ";
	}
	cout << endl << endl;

}

void teststring6()//string插入追加函数、operator+=操作、c_str函数
{
	string s;
	s.push_back('H');//在s后面插入一个字符
	s.append("ello ");//在s后面追加一个字符串
	s += 'w';//在s后面插入一个字符
	s += "orld!";//在s后面追加一个字符串

	cout << s << endl;
	cout << s.c_str() << endl;//以C语言的方式打印字符串

}
void teststring8()//查找等相关函数
{
	string file("stirng.cpp");
	size_t pos = file.find('.');//从前往后找第一个字符'.'
	string suffix(file.substr(pos, file.size() - pos));//在string对象中从pos位置开始，截取n个字符，然后将其返回
	cout << suffix << endl;

	// npos是string里面的一个静态成员变量
	// static const size_t npos = -1;

}
void teststring9()
{

	//应用举例：
	// (1)取出url的域名
	string url("http://www.cplusplus.com/reference/string/string/find/");
	cout << url << endl;
	size_t start = url.find("://");
	if (start == string::npos)
	{
		cout << "invalid url" << endl;
		return;
	}
	start += 3;
	size_t finish = url.find('/', start);
	string address = url.substr(start, finish - start);
	cout << address << endl;

	//(2)删除url协议后缀
	size_t pos = url.find("://");
	url.erase(0, pos + 3);
	cout << url << endl;
}
int main()
{
	//teststr1();
	//teststring2();
	//teststring3();
	//teststring4();
	//teststring5();
	//teststring6();
	//teststring7();
	//teststring8();
	teststring9();


	return 0;
}

