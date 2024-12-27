#pragma once

#include <unordered_map>
#include "stack.h"
#include "Table.h"
#include "Lexemes.h"

using namespace std;

class Poliz
{
private:
    const string protoType[7] = {
        "number",
        "variable",
        "constant",
        "function",
        "operator",
        "brackets",
        "equalsign"
    };
    stack<Table::pair> operationsP;
    stack<Table::pair> Variables;
    stack<double> Value;
    unordered_map<string, int> priority = { {"+", 0}, {"-", 0}, {"*", 1}, {"/", 1}, {"^", 2}, {"u-", 3}, {"u+", 3} };
    unordered_map<string, bool> assoc = { {"+", true}, {"-", true}, {"*", true}, {"/", true}, {"^", false} };
    int SwitchType(string buf);
public:
    void toPolish(Lexemes Lexem, Lexemes var);
    stack<Table::pair> GetOp();
    stack<double> GetVal();
};

