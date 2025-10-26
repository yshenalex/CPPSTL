#include<iostream>
#include<cstring>
#include<assert.h>
using namespace std;

namespace simulation_string
{
	class string
	{
	public:
		typedef char* iterator;
		friend ostream& operator <<(ostream& out, const string& s);
		friend istream& operator>>(istream& in, string& s);
	public:

		//【1.迭代器】
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}


		//【2.1构造函数】
		string(const char* str = "")
		//此处不能给nullptr缺省值，因为下面strlen()将出现错误
		//而""表示空字符串，里面含有一个'\0'
		{
			if (nullptr == str)//如果传过来的是空指针，我们认为非法
			{
				assert(false);
				return;
			}
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//【2.2复制构造函数】
		//2.2.3复制构造函数传统写法：
		/*string(const string& s)
		{
			_str = new char[s._capacity + 1];
			_size = s._size;
			_capacity = s._capacity;
			strcpy(_str, s._str);
		}*/

		//2.2.4复制构造函数巧妙写法：
		void Swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		string(const string& s)
			:_str(nullptr)//若不置空，将是随机值，那后面调析构函数析构随机值就有问题了
			, _size(0)
			, _capacity(0)
		{
			string tmp(s._str);//巧妙利用局部变量在函数结束时销毁的特点
			Swap(tmp);
		}


		//【3.析构函数】
		~string()
		{
			delete[]_str;
			_str = nullptr;
			_size = _capacity = 0;
		}


		//【4.operator=】
		//4.1operator=的传统写法
		/*string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* tmp = new char[s._capacity + 1];
				strcpy(tmp, s._str);

				delete[]_str;
				_str = tmp;

				_size = s._size;
				_capacity = s._capacity;
			}

			return *this;
		}*/

		//4.2.1operator=的巧妙写法1
		/*string& operator=(const string& s)
		{
			if (this != &s)
			{
				string tmp(s);
				Swap(tmp);
			}
			return *this;
		}*/

		//4.2.2operator=的巧妙写法2
		string& operator=(string s)
		{
			Swap(s);
			return *this;
		}


		//【5.容量操作】
		//5.1
		size_t size()const
		{
			return _size;
		}

		//5.2
		size_t capacity()const
		{
			return _capacity;
		}
		
		//5.3
		bool empty()
		{
			return 0 == _size;
		}

		//5.4
		void reserve(size_t newCapacity)
		{
			if (newCapacity > _capacity)
			{
				char* tmp = new char[newCapacity + 1];
				strcpy(tmp, _str);

				delete[]_str;
				_str = tmp;
				_capacity = newCapacity;
			}
		}

		//5.5
		void resize(size_t newSize, char ch = '\0')
		{
			if (newSize >= _size)
			{
				reserve(newSize);
				for (size_t i = _size; i < _capacity; i++)
				{
					_str[i] = ch;
				}
			}
			else
			{
				_str[newSize] = '\0';
				_size = newSize;
			}

		}


		//【6.访问string对象函数】
		//6.1.1 operator[]
		//普通对象：可读可写
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		//6.1.2 operator[]
		//const对象：只读
		const char& operator[](size_t pos)const
		{
			assert(pos < _size);
			return _str[pos];
		}

		//6.2 c_str
		const char* c_str()const
		{
			return _str;
		}


		//【7.修改操作】
		//7.1
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
		}

		//7.2
		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			
			strcpy(_str + _size, str);
			_size += len;
		}

		//7.3.1 operator+=
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		//7.3.2 operator+=
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		//7.4.1 insert
		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);//pos=_size时，相当于尾插

			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			//挪动数据
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				end--;
			}
			_str[pos] = ch;
			_size++;


			return *this;
		}

		//7.4.2 insert
		string& insert(size_t pos, const char* str)
		{
			size_t len = strlen(str);
			assert(pos <= _size);//pos=_size时，相当于尾插
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			size_t end = _size + len;
			while (end >= pos + len)
			{
				_str[end] = _str[end - len];
				end--;
			}

			/*//问：如果下面这么写，问题出现在哪儿？
			int end = _size;
			while (end >= pos)
			{
				_str[end + len] = _str[end];
				end--;
			}
			//【问题】以上写法不支持当pos=0时插入
			//【理由】
			//当end减少为0的时候，此时end=0=pos,再进入循环，随后end减小为-1,
			//由于pos是size_t类型，而end是int类型，二者比较时，发生算术转换，
			//int向上转换为unsigned int(size_t),而-1对应为42亿多的数，最后陷入死循环
			//而原来的写法将end赋值为_size+len则将避免这种情况
			//【结论】因此，若真要上面那么写，则需要把pos强转为int,
			//即 while(end>=(int)pos)...*/

			strncpy(_str + pos, str, len);
			_size += len;

			return *this;
		}

		//7.5 erase
		string& erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);

			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}

			return *this;
		}

		//7.6.1 find
		size_t find(char ch, size_t pos = 0)const
		{
			assert(pos < _size);
			while (pos < _size)
			{
				if (_str[pos] == ch)
				{
					return pos;
				}
				pos++;
			}
			return npos;
		}

		//7.6.2 find
		size_t find(const char* str, size_t pos = 0)const
		{
			assert(pos < _size);
			const char* ptr = strstr(_str+pos, str);
			if (ptr == nullptr)
			{
				return npos;
			}
			else
			{
				return ptr - _str;
			}
		}

		//7.7
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}


		//【8.比较运算符重载】
		bool operator<(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}
		bool operator==(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}
		bool operator<=(const string& s)
		{
			return *this < s || *this == s;
		}
		bool operator>(const string& s)
		{
			return !(*this <= s);
		}
		bool operator>=(const string& s)
		{
			return !(*this < s);
		}
		bool operator!=(const string& s)
		{
			return !(*this == s);
		}

	private:
		const static size_t npos = -1;//静态对象
	private:
		char* _str;//
		size_t _size;
		size_t _capacity;

	};


	//【<<运算符重载】
	ostream& operator <<(ostream& out, const string& s)
	{
		//不能直接使用cout打印，因为string的字符串内部是可能包含\0的
		//如果直接cout时，是将_str当成char*打印，遇到内部的\0时后面的内容就不打印了

		for (size_t i = 0; i < s._size; i++)
		{
			out << s[i];
		}
		return out;
	}

	//【>>运算符重载】
	istream& operator>>(istream& in, string& s)
	{
		s.clear();
		while (1)
		{
			char ch;
			//in >> ch;
			//不能向上面这样写，因为输入时遇到空格和换行会被识别为字符串之间的分隔符，
			//从而跳过后不被下面if条件识别
			ch = in.get();
			if (ch == ' ' || ch == '\n')
			{
				return in;
			}
			else
			{
				s += ch;
			}
		}
	}

	//上面还可以延申出getline()函数：
	istream& getline(istream& in, string& s)
	{
		s.clear();
		while (1)
		{
			char ch;
			ch = in.get();
			if (ch == '\n')
			{
				return in;
			}
			else
			{
				s += ch;
			}
		}
	}


};

void testMystring1()
{
	simulation_string::string s = "Hello world!";
	s.insert(12, "xxxx");
	cout << s << endl;
}
int main()
{
	testMystring1();
	return 0;
}