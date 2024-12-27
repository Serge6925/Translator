#include "Trans.h"

Trans::Trans(string str)
{
    l.createLex(str);
    polish.toPolish(l, var);
}




expression::expression() {}

expression::expression(string& e) {
	newExpr(e);
}

void expression::newExpr() {
	string m;
	std::getline(cin, expr);
	newExpr();
}

void expression::newExpr(string& e) {
	expr = e;
	Trans t;
    try
    {
        Trans Tr(e);
        Tr.res = Tr.cal.counting(Tr.polish.GetOp(), Tr.polish.GetVal());
        if (Tr.l[1].type == "equalsign")
            Tr.var.GetTable().add(Table::pair(Tr.var[0].str, Tr.res, Tr.var[0].type));
        else
            cout << "Result:", Tr.res;
    }
    catch (string error_message)
    {
        cout << "e";
    }
}

screen::screen()
{
	expression expr;
    string input;
    do
    {
        std::getline(std::cin, input);
		expr.newExpr(string("a + (2 - b * 3) ^ c * d + 25 * e ^ (f * 3 + p)"));
        


    } while (input != "\0");
}