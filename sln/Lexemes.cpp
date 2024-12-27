#include "Lexemes.h"

Lexemes::Lexemes(size_t size0)
{
    size_t size = size0;
    Table LexFuncConst(size);
    string String;
    Table Lex(size);
    size_t pos = 0;
}
Lexemes Lexemes::createLex(string iStr)
{
    if (iStr.length() <= 0)
        throw exception("empty enter");
    LexFuncConst.add(Table::pair("pi", acos(-1), "constant"));
    LexFuncConst.add(Table::pair("pi", exp(1), "constant"));
    LexFuncConst.add(Table::pair("cos", 0, "function"));
    LexFuncConst.add(Table::pair("sin", 0, "function"));
    LexFuncConst.add(Table::pair("exp", 0, "function"));
    LexFuncConst.add(Table::pair("log", 0, "function"));
    LexFuncConst.add(Table::pair("tan", 0, "function"));
    LexFuncConst.add(Table::pair("sqrt", 0, "function"));
    string String = iStr;
    Table::pair NewPair;
    while (pos < String.length()
        && NewPair.type != "end")
    {
        NewPair = FindPair();
        if (NewPair.type == "unknown") throw string("invalid symbol");
        if (LexFuncConst.SearchName(NewPair.str) != -1)
        {
            size_t Num = LexFuncConst.SearchName(NewPair.str);
            if (LexFuncConst[Num].type == "constant")
                NewPair = Table::pair(Lex[Num].str, Lex[Num].value, "constant");
            else if (LexFuncConst[Num].type == "function")
                NewPair = Table::pair(Lex[Num].str, Lex[Num].value, "function");
        }
        Lex.add(NewPair);
    }
}
Table& Lexemes::GetTable()
{
    return Lex;
}
Table::pair Lexemes::FindPair()
{
    string str = String;
    while (pos < str.length() && isspace(str.at(pos))) pos++;
    if (pos >= str.length()) return Table::pair(string('\0'), 0, "end");;
    size_t Spos = pos;
    char current = str.at(pos);

    if (isalpha(current) || current == '_') {
        while (pos < str.length() && (isalpha(str.at(pos)) || isdigit(str.at(pos)) || str.at(pos) == '_'))
        {
            pos++;
        }
        return Table::pair(str.substr(Spos, pos - Spos), 0, "variable");
    }

    else if (isdigit(current))
    {
        int state = 0;
        while (pos < str.size()) {
            switch (state) {
            case 0:
                if (str.at(pos) == '0') state = 1;
                else if (isdigit(str.at(pos))) state = 2;
                else if (str.at(pos) == '.') state = 3;
                else state = 4;
                break;
            case 1:
                if (str.at(pos) == '.') state = 3;
                else if (isdigit(str.at(pos))) throw std::string("Your number is incorrect");
                else state = 4;
                break;
            case 2:
                if (isdigit(str.at(pos))) state = 2;
                else if (str.at(pos) == '.') state = 3;
                else state = 4;
                break;
            case 3:
                if (isdigit(str.at(pos))) state = 3;
                else if (str.at(pos) == '.') throw std::string("Your number is incorrect");
                else state = 4;
                break;
            }
            if (state == 4) break;
            pos++;
        }
        return Table::pair(str.substr(Spos, pos - Spos), stod(str.substr(Spos, pos - Spos)), "number");

    }

    else if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
        pos++;
        return Table::pair(string(1, current), 0, "operation");
    }
    else if (current == '(' || current == ')') {
        pos++;
        return Table::pair(string(1, current), 0, "brackets");
    }

    else if (current == '=') {
        pos++;
        Table::pair(string(1, current), 0, "equalsign");
    }

    return Table::pair(string(1, current), 0, "unknown");
}
Table::pair Lexemes::operator [](size_t sz)
{
    return Lex[sz];
}