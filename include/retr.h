#pragma once

#include <iostream>
#include <unordered_map>
#include "parser.h"
#include "Leks.h"
#include "pol.h"
#include "stack.h"
#include "Analisis.h"
#include "ariph.h"

using namespace std;

class Retr
{
private:
    Leksems l;
    Parser  p;
    Polski polish;
    typeExpression typeExp;
    RPNCalculator cal;
public:

    void setTypeExp(const vector<token>& tokens, const unordered_map<string, double>& variables, string& simpleStr, const double& lastResult) {

        size_t countEquals = 0;
        for (const auto& token : tokens) {
            if (token.value == "=") ++countEquals;
        }

        if (p.checkSim(tokens) && p.checkVarInEXPR(tokens, variables) && lastResult != NOTHING) {
            typeExp = typeExpression::SIMPLE;
        }

        else if (countEquals == 1 && tokens.size() == 1 && simpleStr.size() != 0) {
            typeExp = typeExpression::EQUAL;
        }

        else if (countEquals == 1 && tokens[0].type == tokenType::VARIABLE && tokens[1].value == "=") {
            vector<token> subTokens(tokens.begin() + 2, tokens.end());
            if (p.parserExp(subTokens) && p.checkVarInEXPR(subTokens, variables)) {
                typeExp = typeExpression::SET;
            }
        }

        else if (countEquals == 0 && p.parserExp(tokens) && p.checkVarInEXPR(tokens, variables)) {
            typeExp = typeExpression::EXPRESSION;
        }

        else {
            typeExp = typeExpression::ERROR;
        }
    }


    double logic(const string& str, unordered_map<string, double>& variables, string& simpleStr, double& lastResult) {

        if (str.empty()) throw string("try to type an expression");
        vector<token> tokens = l.createTokens(str); 
        setTypeExp(tokens, variables, simpleStr, lastResult);

        if (typeExp == typeExpression::SIMPLE) {
            simpleStr = str;
            token newToken(tokenType::NUMBER, to_string(lastResult));
            tokens.insert(tokens.begin(), newToken);
            result = cal.evaluate(polish.toPolish(tokens), variables);
        }

        else if (typeExp == typeExpression::EQUAL) {
            Leksems le;
            vector<token> tokens = le.makeTokens(simpleStr);
            token newToken(tokenType::NUMBER, to_string(lastResult));
            tokens.insert(tokens.begin(), newToken);
            result = cal.evaluate(polish.toPolish(tokens), variables);
        }

        else if (typeExp == typeExpression::SET) {

            if (tokens[0].type == tokenType::CONST) {
                throw std::string("This is const. You can't change it.");
            }

            else if (tokens[0].type == tokenType::FUNCTION) {
                throw std::string("This is function. You can't change it.");
            }


            vector<token> subTokens(tokens.begin() + 2, tokens.end());
            variables[tokens[0].value] = cal.evaluate(polish.toPolish(subTokens), variables);
            result = ;

        }

        else if (typeExp == typeExpression::EXPRESSION) {

            result = cal.evaluate(polish.toPolish(tokens), variables);

        }

        else if (typeExp == typeExpression::ERROR) {
            throw std::string("expression is wrong");
        }

        return result;
    }
};

