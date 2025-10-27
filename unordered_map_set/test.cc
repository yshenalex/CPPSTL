#include "mystl_unordered_map.hpp"
#include "mystl_unordered_set.hpp"

#include <string>
#include <iostream>
using namespace std;
using namespace mystl;

void test1()
{
	cout << "=== Test1: Basic Insert and Iterate ===" << endl;
	unordered_map<int, int> map;
	map.insert(make_pair(1, 10));
	map.insert(make_pair(2, 20));
	map.insert(make_pair(3, 30));
	map.insert(make_pair(4, 40));
	map.insert(make_pair(5, 50));

	auto it = map.begin();
	while (it != map.end()) {
		cout << it->first << ":" << it->second << " ";
		++it;
	}
	cout << "\nSize: " << map.size() << "\n" << endl;

}
void test2()
{
	cout << "=== Test2: operator[] Access and Overwrite ===" << endl;
	unordered_map<string, string> strMap;
	// 用[]插入新键值对
	strMap["name"] = "Alice";
	strMap["age"] = "20";
	strMap["gender"] = "female";

	// 输出初始值
	cout << "Before overwrite: " << endl;
	cout << "name: " << strMap["name"] << ", age: " << strMap["age"] << endl;

	// 用[]覆盖已有值
	strMap["age"] = "21";
	// 访问不存在的键（会自动插入默认值）
	cout << "After overwrite: " << endl;
	cout << "age: " << strMap["age"] << ", address: " << strMap["address"] << endl;
	// 验证size（初始3个+新增1个=4个）
	cout << "Size: " << strMap.size() << "\n" << endl;
}
void test3()
{
	cout << "=== Test3: Find and Erase ===" << endl;
	unordered_map<int, double> numMap;
	// 插入测试数据
	numMap.insert(make_pair(10, 3.14));
	numMap.insert(make_pair(20, 6.28));
	numMap.insert(make_pair(30, 9.42));
	numMap.insert(make_pair(40, 12.56));

	// 查找存在的键
	auto findIt1 = numMap.find(20);
	if (findIt1 != numMap.end()) {
		cout << "Found key 20: " << findIt1->first << ":" << findIt1->second << endl;
	}

	// 查找不存在的键
	auto findIt2 = numMap.find(50);
	if (findIt2 == numMap.end()) {
		cout << "Key 50 not found" << endl;
	}

	// 删除存在的键
	size_t eraseCnt1 = numMap.erase(30);
	cout << "Erase key 30: " << (eraseCnt1 == 1 ? "Success" : "Failed") << endl;
	// 删除不存在的键
	size_t eraseCnt2 = numMap.erase(50);
	cout << "Erase key 50: " << (eraseCnt2 == 0 ? "Success (no such key)" : "Failed") << endl;

	// 遍历删除后的元素
	cout << "Elements after erase: ";
	for (auto it = numMap.begin(); it != numMap.end(); ++it) {
		cout << it->first << ":" << it->second << " ";
	}
	cout << "\nSize: " << numMap.size() << "\n" << endl;
}

void test4()
{
	cout << "=== Test4: Rehashing (Auto Resize) ===" << endl;
	unordered_map<int, int> bigMap;
	// 插入超过初始桶数（53）的数据，触发多次扩容
	for (int i = 1; i <= 60; ++i) {
		bigMap.insert(make_pair(i, i * 10));
	}

	// 验证size是否正确（60个元素）
	cout << "Total elements: " << bigMap.size() << endl;
	// 验证所有元素均可正常遍历（无丢失）
	size_t count = 0;
	for (auto it = bigMap.begin(); it != bigMap.end(); ++it) {
		count++;
		// 每10个元素输出一次，避免输出过长
		if (count % 10 == 0) {
			cout << it->first << ":" << it->second << " ";
		}
	}
	cout << "\nTraversed count: " << count << " (should equal size)\n" << endl;
}
void test5()
{
	cout << "=== Test5: Empty Table and Const Iterator ===" << endl;
	// 测试空表状态
	unordered_map<int, string> emptyMap;
	cout << "Is emptyMap empty? " << (emptyMap.empty() ? "Yes" : "No") << endl;
	cout << "emptyMap size: " << emptyMap.size() << endl;

	// 插入数据后测试const迭代器
	emptyMap.insert(make_pair(1, "apple"));
	emptyMap.insert(make_pair(2, "banana"));
	emptyMap.insert(make_pair(3, "cherry"));

	// const对象必须用const_iterator遍历
	const unordered_map<int, string> &constMap = emptyMap;
	cout << "Const map elements: ";
	for (auto it = constMap.begin(); it != constMap.end(); ++it) {
		cout << it->first << ":" << it->second << " ";
	}
	cout << "\nIs constMap empty? " << (constMap.empty() ? "Yes" : "No") << "\n" << endl;
}

void test6()
{
	cout << "=== Test6: Basic Insert and Iterate ===" << endl;
	unordered_set<int> set;
	set.insert(10);
	set.insert(20);
	set.insert(30);
	set.insert(40);
	set.insert(50);

	auto it = set.begin();
	while (it != set.end()) {
		cout << *it << " ";
		++it;
	}
	cout << "\nSize: " << set.size() << "\n" << endl;
}

void test7()
{
	cout << "=== Test7: Duplicate Insert and Contains Check ===" << endl;
	unordered_set<string> strSet;
	// 插入重复元素（应自动去重）
	strSet.insert("apple");
	strSet.insert("banana");
	strSet.insert("apple");  // 重复插入
	strSet.insert("orange");
	strSet.insert("banana"); // 重复插入

	// 遍历验证去重结果
	cout << "Elements: ";
	for (const auto& elem : strSet) {
		cout << elem << " ";
	}
	cout << endl;

	// 检查元素是否存在
	cout << "Contains 'apple'? " << (strSet.find("apple") != strSet.end() ? "Yes" : "No") << endl;
	cout << "Contains 'grape'? " << (strSet.find("grape") != strSet.end() ? "Yes" : "No") << endl;
	cout << "Size (should be 3): " << strSet.size() << "\n" << endl;
}

void test8()
{
	cout << "=== Test8: Find and Erase ===" << endl;
	unordered_set<double> numSet;
	// 插入测试数据
	numSet.insert(3.14);
	numSet.insert(6.28);
	numSet.insert(9.42);
	numSet.insert(12.56);

	// 查找存在的元素
	auto findIt1 = numSet.find(6.28);
	if (findIt1 != numSet.end()) {
		cout << "Found element: " << *findIt1 << endl;
	}

	// 查找不存在的元素
	auto findIt2 = numSet.find(2.718);
	if (findIt2 == numSet.end()) {
		cout << "Element 2.718 not found" << endl;
	}

	// 删除存在的元素
	size_t eraseCnt1 = numSet.erase(9.42);
	cout << "Erase 9.42: " << (eraseCnt1 == 1 ? "Success" : "Failed") << endl;
	// 删除不存在的元素
	size_t eraseCnt2 = numSet.erase(2.718);
	cout << "Erase 2.718: " << (eraseCnt2 == 0 ? "Success (no such element)" : "Failed") << endl;

	// 遍历删除后的元素
	cout << "Elements after erase: ";
	for (const auto& elem : numSet) {
		cout << elem << " ";
	}
	cout << "\nSize: " << numSet.size() << "\n" << endl;
}

void test9()
{
	cout << "=== Test9: Rehashing (Auto Resize) ===" << endl;
	unordered_set<int> bigSet;
	// 插入超过初始桶数的数据，触发扩容
	for (int i = 1; i <= 60; ++i) {
		bigSet.insert(i);
	}

	// 验证元素数量
	cout << "Total elements: " << bigSet.size() << endl;
	// 验证所有元素可遍历（无丢失）
	size_t count = 0;
	for (const auto& elem : bigSet) {
		count++;
		// 每10个元素输出一次
		if (count % 10 == 0) {
			cout << elem << " ";
		}
	}
	cout << "\nTraversed count: " << count << " (should equal size)\n" << endl;
}

void test10()
{
	cout << "=== Test10: Empty Set and Const Iterator ===" << endl;
	// 测试空集合状态
	unordered_set<string> emptySet;
	cout << "Is emptySet empty? " << (emptySet.empty() ? "Yes" : "No") << endl;
	cout << "emptySet size: " << emptySet.size() << endl;

	// 插入数据后测试const迭代器
	emptySet.insert("red");
	emptySet.insert("green");
	emptySet.insert("blue");

	// const对象必须用const_iterator遍历
	const unordered_set<string>& constSet = emptySet;
	cout << "Const set elements: ";
	for (auto it = constSet.begin(); it != constSet.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\nIs constSet empty? " << (constSet.empty() ? "Yes" : "No") << "\n" << endl;
}

int main()
{
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();

	test6();
    test7();
    test8();
    test9();
	test10();
	return 0;
}