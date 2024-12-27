#include "Calc.h"


double Calc::counting(stack<Table::pair> operationsP, stack<double> Variables)
{
    while ((! operationsP.is_empty()) && (!Variables.is_empty()))
    {
        if (operationsP.top().type == "function" || operationsP.top().type == "operator" && operationsP.top().str[0] == 'u')
        {
            Variables.push(Function(operationsP.pop().str, Variables.pop()));
        }
        else if (operationsP.top().type == "operator")
            Variables.push(Operator(operationsP.pop().str, Variables.pop(), Variables.pop()));
        else {
            throw std::string("invalid operation");
        }
    }
    if (!operationsP.is_empty()) throw std::string("you lost an operation");
    return Variables.top();
}

double Calc::Operator(const string& op, double a, double b)
{
    if (op == "+")
        return a + b;
    if (op == "-")
        return a - b;
    if (op == "*")
        return a * b;
    if (op == "/")
    {
        if (b == 0) throw std::string("division by zero");
        return a / b;
    }
    if (op == "^")
        return pow(a, b);
}

double Calc::Function(const string& func, double arg)
{
    if (func == "u-")
        return -arg;
    if (func == "u+")
        return arg;
    if (func == "sin")
        return sin(arg);
    if (func == "cos")
        return cos(arg);
    if (func == "exp")
        return exp(arg);
    if (func == "log")
    {
        if (arg < 0) throw std::string("indefinite logarithm");
        return log(arg);
    }
    if (func == "tan")
        return tan(arg);
    if (func == "sqrt")
    {
        if (arg < 0) throw std::string("imaginary number");
        return sqrt(arg);
    }
    throw string("don't found function");
}