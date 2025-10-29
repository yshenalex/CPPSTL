#include "mystl_queue.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <string>

using mystl::Greater;
using mystl::Less;
using mystl::priority_queue;
using mystl::queue;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 测试queue基本功能
void test1()
{
	cout << "=== Testing queue basic functionality ===" << endl;
	queue<int> q;

	assert(q.empty() == true);
	assert(q.size() == 0);
	cout << "   Empty queue test passed - empty: " << q.empty() << ", size: " << q.size() << endl;

	cout << "Pushing elements: 1, 2, 3" << endl;
	q.push(1);
	q.push(2);
	q.push(3);

	assert(q.empty() == false);
	assert(q.size() == 3);
	assert(q.front() == 1);
	assert(q.back() == 3);
	cout << "   Queue state: empty=" << q.empty() << ", size=" << q.size()
		 << ", front=" << q.front() << ", back=" << q.back() << endl;

	cout << "Testing pop operation..." << endl;
	q.pop();
	assert(q.front() == 2);
	assert(q.size() == 2);
	cout << "   After first pop - front=" << q.front() << ", size=" << q.size() << endl;

	cout << "Popping remaining elements..." << endl;
	q.pop();
	q.pop();
	assert(q.empty() == true);
	cout << "   After all pops - empty=" << q.empty() << ", size=" << q.size() << endl;

	cout << "Queue basic test passed!" << endl
		 << endl;
}

// 测试priority_queue
void test2()
{
	cout << "=== Testing priority_queue basic functionality ===" << endl;
	priority_queue<int> pq;

	assert(pq.empty() == true);
	assert(pq.size() == 0);
	cout << "   Empty priority queue test passed" << endl;

	cout << "Inserting elements: 3, 1, 4, 2" << endl;
	pq.push(3);
	pq.push(1);
	pq.push(4);
	pq.push(2);

	cout << "Testing heap top and size..." << endl;
	assert(pq.size() == 4);
	assert(pq.top() == 4); // 大顶堆，最大元素在顶
	cout << "   After inserts - size=" << pq.size() << ", top=" << pq.top() << endl;

	cout << "Testing pop operations..." << endl;
	pq.pop();
	cout << "   After first pop - top=" << pq.top() << " (expected: 3)" << endl;
	assert(pq.top() == 3);

	pq.pop();
	cout << "   After second pop - top=" << pq.top() << " (expected: 2)" << endl;
	assert(pq.top() == 2);

	pq.pop();
	cout << "   After third pop - top=" << pq.top() << " (expected: 1)" << endl;
	assert(pq.top() == 1);

	pq.pop();
	assert(pq.empty() == true);
	cout << "   After all pops - empty=" << pq.empty() << endl;

	cout << "Priority queue basic test passed!" << endl
		 << endl;
}

// 测试priority_queue的迭代器构造函数
void test3()
{
	cout << "=== Testing priority_queue iterator constructor ===" << endl;
	vector<int> vec = {5, 2, 7, 1, 9};
	cout << "1. Creating vector with elements: 5, 2, 7, 1, 9" << endl;

	cout << "2. Constructing priority_queue from vector iterators..." << endl;
	priority_queue<int> pq(vec.begin(), vec.end());

	cout << "3. Testing constructed priority queue..." << endl;
	assert(pq.size() == 5);
	assert(pq.top() == 9); // 构造后应维持堆结构
	cout << "   Constructed heap - size=" << pq.size() << ", top=" << pq.top() << " (largest element)" << endl;

	cout << "4. Testing pop operations..." << endl;
	pq.pop();
	cout << "   After first pop - top=" << pq.top() << " (expected: 7)" << endl;
	assert(pq.top() == 7);

	pq.pop();
	cout << "   After second pop - top=" << pq.top() << " (expected: 5)" << endl;
	assert(pq.top() == 5);

	cout << "Priority queue iterator constructor test passed!" << endl
		 << endl;
}

// 测试priority_queue的右值引用push
void test4()
{
	cout << "=== Testing priority_queue rvalue push ===" << endl;
	priority_queue<string> pq;

	cout << "1. Testing rvalue push operations..." << endl;
	cout << "   Pushing string(\"apple\")..." << endl;
	pq.push(string("apple"));

	cout << "   Pushing \"banana\" (implicit conversion to rvalue)..." << endl;
	pq.push("banana"); // 隐式转换为右值

	cout << "   Pushing std::move(string(\"cherry\"))..." << endl;
	pq.push(std::move(string("cherry")));

	cout << "2. Testing heap state..." << endl;
	assert(pq.size() == 3);
	assert(pq.top() == "cherry"); // 字典序最大
	cout << "   After pushes - size=" << pq.size() << ", top=\"" << pq.top() << "\" (lexicographically largest)" << endl;

	cout << "3. Testing pop operations..." << endl;
	pq.pop();
	assert(pq.top() == "banana");
	cout << "   After first pop - top=\"" << pq.top() << "\" (expected: banana)" << endl;

	cout << "Priority queue rvalue push test passed!" << endl
		 << endl;
}

// 测试边界情况（空队列操作）
void test5()
{
	cout << "=== Testing edge cases ===" << endl;
	queue<int> q;
	priority_queue<int> pq;

	cout << "1. Testing pop on empty queues (should not crash)..." << endl;
	cout << "   Popping from empty queue..." << endl;
	q.pop();
	cout << "   Popping from empty priority_queue..." << endl;
	pq.pop();
	cout << "   Empty pop operations completed without crash" << endl;

	cout << "2. Testing front/back/top on empty queues (should not crash)..." << endl;
	q.front();
	q.back();
	pq.top();

	cout << "Edge cases test passed!" << endl
		 << endl;
}
#include <queue>
int main()
{
	cout << "Starting STL Queue Tests..." << endl;
	cout << "============================" << endl
		 << endl;

	test1();
	test2();
	test3();
	test4();
	test5();

	cout << "============================" << endl;
	cout << "All tests passed!" << endl;
	cout << "============================" << endl;

	return 0;
}