#pragma once
#include <iostream>
#include <string>

using namespace std;

class Table
{
public:
	struct pair
	{
		string str;
		double value;
		string type;
		pair(string st = "", int zn = 0, string t = "unknown") : str(st), value(zn), type(t) {}
		pair(string st, double zn, string t) : str(st), value(zn), type(t) {}
	};
protected:
	pair* array = nullptr;
	int count = 0;
	size_t size;
	double capacity = 1.55;


public:

	Table(size_t size0 = 20);
	~Table();

	Table(const Table& tmp);
	Table& operator =(const Table& tmp);

	double SearchValue(string key);
	int  SearchName(string key);
	int SearchType(string key);


	int getCount();


	void add(pair tmp);
	void del(string key);

	int isEmpty();
	int isFull();
	pair operator [](int key);
	void repack();
};