#include "Table.h"


Table::Table(size_t size0) : size(size0)
{
	array = new pair[size];
	count = 0;
}


Table::~Table() {
	delete[] array;
}

Table::Table(const Table& tmp)
{
	size = tmp.size;
	count = tmp.count;
	array = new pair[size];
	for (int i = 0; i < size; i++)
	{
		array[i] = tmp.array[i];
	}
}

Table& Table::operator =(const Table& tmp)
{
	if (&tmp == this)
		return *this;
	delete[] this->array;
	size = tmp.size;
	count = tmp.count;
	array = new pair[size];
	for (int i = 0; i < count; i++)
		array[i] = tmp.array[i];
	return *this;
}

double Table::SearchValue(string key)
{
	for (int i = 0; i < count; i++)
		if (key == array[i].str)
			return array[i].value;
		else
			throw exception("Not in array");
}
int  Table::SearchName(string key)
{
	for (int i = 0; i < count; i++)
		if (key == array[i].str)
			return i;
	return -1;
}
int Table::SearchType(string key)
{
	for (int i = 0; i < count; i++)
		if (key == array[i].type)
			return i;
	return -1;
}

int Table::getCount()
{
	return count - 8;
}

void Table::add(pair tmp)
{
	int N = SearchName(tmp.str);
	if (N == -1)
		array[count++] = tmp;
	else
		array[N] = tmp;
}
void Table::del(string key)  //pop
{
	int res = SearchName(key);
	if (res != -1)
	{
		array[res] = array[--count];
	}
}
int Table::isEmpty() { return count == 0; }
int Table::isFull() { return count == size; }
Table::pair Table::operator [](int key)
{
	if (key >= 0 && key <= count)
		return array[key];
	else if (key == -1)
		return pair("0", 0, "unknown");
}
void Table::repack()
{
	size *= capacity;
	pair* Newarray = new pair[size];
	for (int i = 0; i < count; i++)
	{
		Newarray[i] = array[i];
	}
	delete[] array;
	array = Newarray;
	Newarray = nullptr;
}