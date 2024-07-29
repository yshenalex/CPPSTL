#define _CRT_SECURE_NO_WARNINGS
#include<assert.h>
#include<iostream>
using namespace std;


namespace simulation_vector
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin()const
		{
			return _start;
		}
		const_iterator end()const
		{
			return _finish;
		}

		T& operator[](size_t pos)
		{
			assert(pos >= 0 && pos < size());
			return _start[pos];
		}
		const T& operator[](size_t pos)const
		{
			assert(pos >= 0 && pos < size());
			return _start[pos];
		}

		void Swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}

		vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			reserve(v.capacity());
			for (const auto& e : v)
				push_back(e);
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		vector(size_t n, const T&val=T())
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}


		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}

		size_t capacity()const
		{
			return _endofstorage - _start;
		}

		size_t size()const
		{
			return _finish - _start;
		}

		bool empty()const
		{
			return _finish == _start;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* tmp = new T[n];
				int sz = size();

				if (_start)
				{
					//memcpy(tmp, _start, sizeof(T) * sz);
					for (int i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}

					delete[] _start;
				}

				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, T val = T())
		{
			if (n > capacity())
				reserve(n);

			if (n > size())
			{
				iterator it = _finish;
				while (it != _start + n)
				{
					*it = val;
					it++;
				}
			}

			_finish = _start + n;
		}

		void push_back(const T& val)
		{
			if (_finish == _endofstorage)
			{
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
			}

			*_finish = val;
			_finish++;
		}

		void pop_back()
		{
			assert(!empty());
			_finish--;
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start && pos <= _finish);

			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);

				pos = _start + len;
			}

			iterator it = _finish;
			while (pos != it)
			{
				*it = *(it - 1);
				it--;
			}

			*it = val;
			_finish++;

			return pos;
		}

		void push_front(const T& val)
		{
			insert(_start, val);
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);

			iterator it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				it++;
			}
			
			_finish--;

			return pos;
		}

		void pop_front()
		{
			erase(_start);
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
}
void PrintVector(simulation_vector::vector<int>& v)
{
	for (auto e : v)
		cout << e << " ";
	cout << endl;
}
void testMyVector1()
{
	simulation_vector::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	PrintVector(v);
	simulation_vector::vector<int>::iterator pos = find(v.begin(), v.end(), 1);
	if (pos != v.end())
	{
		v.insert(pos, 100);
	}
	v.pop_front();
	v.pop_front();
	v.pop_front();
	PrintVector(v);
	v.push_front(10);
	v.push_front(10);
	v.push_front(10);

	PrintVector(v);
	v.pop_back();
	v.pop_back();
	v.pop_back();
	v.pop_back();

	simulation_vector::vector<int>t = v;

	PrintVector(t);
}

int main()
{
	testMyVector1();

	return 0;
}





