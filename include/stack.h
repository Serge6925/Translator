#pragma once
#include <iostream>

using namespace std;
template <class T>
class stack {
private:
	T* pMem;
	int size;
	int count;
	double capacity = 1.55;
public:
	stack(int sz = 20) {
		if (sz < 0)
			throw exception();
		size = sz;
		count = 0;
		pMem = new T[size];
		for (int i = 0; i < size; i++) {
			pMem[i] = T();
		}
	}
	stack(const stack& tmp) {
		size = tmp.size;
		count = tmp.count;
		pMem = new T[size];
		for (int i = 0; i < size; i++)
			pMem[i] = tmp.pMem[i];
	}

	stack& operator=(stack<T> tmp) {
		if (this == &tmp)
			return *this;
		if (size != tmp.size) {
			if (size != 0)
				delete[] pMem;
			size = tmp.size;
			pMem = new T[size];
		}
		count = tmp.count;
		for (int i = 0; i < size; i++)
			pMem[i] = tmp.pMem[i];
		return *this;
	}

	~stack() {
		delete[] pMem;
	}

	int is_full() {
		if (count == size)
			return 1;
		else
			return 0;
	}

	int is_empty() {
		if (count == 0)
			return 1;
		else
			return 0;
	}

	void push(T k) {
		if (count >= size)
			this->repack();
		pMem[count++] = k;
	}

	T top() {
		if (count > 0)
			return pMem[count - 1];
		else
			throw exception();
	}

	T pop() {
		if (count > 0)
			return pMem[--count];
		else
			throw exception();
	}

	int GetCount() {
		return count;
	}
	
	void repack()
	{
		size *= capacity;
		T* NewpMem = new T[size];
		for (int i = 0; i < count; i++)
		{
			NewpMem[i] = pMem[i];
		}
		delete[] pMem;
		pMem = NewpMem;
		NewpMem = nullptr;
	}
};
