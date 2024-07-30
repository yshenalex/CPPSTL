#define _CRT_SECURE_NO_WARNINGS
#include"BSTree.h"

void test1()
{
	K::BSTree<int> bst;

	bst.Insert(1);
	bst.Insert(5);
	bst.Insert(6);
	bst.Insert(10);
	bst.Insert(18);
	bst.Insert(3);
	bst.Insert(4);

	bst.InOrder();

	bst.Erase(1);
	bst.Erase(1);
	bst.InOrder();

	bst.Erase(10);
	bst.Erase(4);
	bst.Erase(6);
	bst.InOrder();

	bst.Insert(6);
	bst.Insert(10);
	bst.Insert(18);
	bst.Insert(3);
	bst.Insert(4);
	bst.InOrder();

	cout << "-------------" << endl;

	K::BSTree<int> bst2(bst);

	bst2.InOrder();

	K::BSTree<int> bst3 = bst2;
	bst3.Erase(18);
	bst3.InOrder();
	bst2.InOrder();
}

void test2()
{
	KV::BSTree<string, string>dict;
	dict.InOrder();

	dict.Insert("network", "网络");
	dict.Insert("system", "系统");
	dict.Insert("data", "数据");
	dict.Insert("disk", "磁盘");
	
	//字典查询
	string str;
	while (cin >> str)
	{
		KV::BSTreeNode<string, string>* ret = dict.Find(str);
		if (ret)
		{
			cout << ret->_value << endl;
		}
		else
		{
			cout << "查无此词" << endl;
		}
	}
}

void test3()
{

	//单词计数
	string a[] = { "apple","apple", "banana", "banana", "apple", "watermelon", "watermelon", "watermelon", "banana", "apple", "grapes", "apple", "banana", "apple", "apple", "apple" };

	KV::BSTree<string, int>dict;
	for (auto& e : a)
	{
		auto* ret = dict.Find(e);
		if (!ret)
			dict.Insert(e, 1);
		else
			ret->_value += 1;
	}

	dict.InOrder();

}

int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}