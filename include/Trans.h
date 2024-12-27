#pragma once
#include "..\include\Lexemes.h"
#include "..\include\Calc.h"
#include "..\include\PolishE.h"
using namespace std;

class Trans
{
public:
    Lexemes l;
    Lexemes var;
    Poliz polish;
    Calc cal;
    double res;

public:
    Trans(string str = "");
    /*void SintAn(Lexemes l, const unordered_map<string, double>& variables, string& simpleStr, const double& lastResult);
    void LecsAn(const string& str, unordered_map<string, double>& variables, string& simpleStr, double& lastResult);*/
};
class expression {
private:

	double value = 0;

	bool isError;
	string expr;
	string simpleExpr = "";

	unordered_map<string, double> variables;


public:

	expression();

	expression(string& e);

	void newExpr();
	void newExpr(string& e);
};


class screen
{
private:
    Trans tr;
public:
    screen();
};
