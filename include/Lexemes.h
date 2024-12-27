#pragma once

#include <iostream>
#include "stack.h"
#include <string> 
#include "Table.h"
using namespace std;

class Lexemes
{
    private:
        Table LexFuncConst;
        size_t size = 30;
        string String;
        Table Lex;
        size_t pos = 0;
    public:
        Lexemes(size_t size = 20);
        Lexemes createLex(string str);
        Table& GetTable();
        Table::pair FindPair();
        Table::pair operator [](size_t sz);
};

