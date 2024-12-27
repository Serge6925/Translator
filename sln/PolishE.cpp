#include "PolishE.h"

int Poliz::SwitchType(string buf)
{
    for (int i = 0; i < 7; ++i)
        if (buf == protoType[i])
            return i;
    return -1;
}

void Poliz::toPolish(Lexemes Lexem, Lexemes var)
{
    stack<Table::pair> operators;
    bool expectUnary = true;

    for (size_t i = Lexem.GetTable().SearchType("equalsign") + 1; i < Lexem.GetTable().getCount(); i++) {
        switch (SwitchType(Lexem[i].type)) {
        case 0: //"number"
        {
            Variables.push(Lexem[i]);
            Value.push(Variables.pop().value);
            break;
        }
        case 1://"variable"
        {
            Variables.push(Table::pair(Lexem[i].str, var[var.GetTable().SearchName(Lexem[i].str)].value, Lexem[i].type));
            Value.push(Variables.pop().value);
            break;
        }
        case 2://"constant"
        {
            Variables.push(Lexem[i]);
            Value.push(Variables.pop().value);
            break;
        }
        case 3://"function"
        {
            operators.push(Lexem[i]);
            expectUnary = true;
            break;
        }
        case 4://"operators
        {
            std::string op = Lexem[i].str;

            if (expectUnary) {
                if (op == "-") op = "u-";
                else if (op == "+") op = "u+";
            }

            while (!operators.is_empty() && operators.top().type != "brackets" && ((assoc[op] && priority[op] <= priority[operators.top().str]) || (!assoc[op] && priority[op] < priority[operators.top().str])))
            {

                operationsP.push(operators.top());
                operators.pop();
            }

            operators.push(Table::pair(op, 0, "operator"));
            expectUnary = true;
            break;
        }

        case 5://"brackets"
        {
            if (Lexem[i].str == "(") {
                operators.push(Lexem[i]);
                expectUnary = true;
            }
            else if (Lexem[i].str == ")") {
                while (!operators.is_empty() && operators.top().str != "(")
                {
                    operationsP.push(operators.top());
                    operators.pop();
                }

                operators.pop();

                if (!operators.is_empty() && operators.top().type == "function")
                {
                    operationsP.push(operators.top());
                    operators.pop();
                }
                expectUnary = false;
            }

            break;
        }
        }

        while (!operators.is_empty()) {
            if (operators.top().type == "brackets") {
                throw string("error with brackets");
            }
            operationsP.push(operators.pop());
        }
    }
}
stack<Table::pair> Poliz::GetOp() {return operationsP;}
stack<double> Poliz::GetVal() {return Value;}