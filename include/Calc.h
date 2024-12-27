#pragma once
#include "Lexemes.h"
#include "stack.h"
#include <iostream>
using namespace std;
class Calc
{
public:
	double counting(stack<Table::pair> operationsP, stack<double> Variables);
	double Operator(const string& op, double a, double b);
	double Function(const string& func, double arg);
};
