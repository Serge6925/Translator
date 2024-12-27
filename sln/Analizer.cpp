//#include "Analizer.h"
//#pragma once
//
//#include <vector>
//#include <iostream>
//#include <string>
//#include "stack.h"
//#include <stdexcept>
//#include "Lexemes.h"
//
//using namespace std;
//
//class Parser
//{
//public:
//
//private:
//    string instance;
//    stack<char> operations;
//    stack<char> TypeSymb;
//    bool checkSim(const vector<token>& tokens)
//    {
//        if (tokens.size() == 2 && tokens[0].type == tokenType::OPERATOR && (tokens[1].type == tokenType::NUMBER || tokens[1].type == tokenType::VARIABLE)) {
//
//            if (tokens[0].value == "/" && tokens[1].value == "0") {
//                throw std::string("division by zero");
//            }
//            else {
//                return true;
//            }
//
//        }
//        else if (tokens.size() == 3 && tokens[0].value == "*" && tokens[1].value == "*" && (tokens[1].type == tokenType::NUMBER || tokens[1].type == tokenType::VARIABLE)) {
//            return true;
//        }
//        return false;
//    }
//
//    bool parserExp(const vector<token>& tokens) {
//
//        size_t state = 0;
//        size_t parCount = 0;
//
//        for (const token& tok : tokens) {
//
//            switch (state) {
//            case 0:
//                if (tok.type == tokenType::FUNCTION) { state = 6; }
//                else if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
//                else if (tok.value == "+" || tok.value == "-") { state = 1; }
//                else if (tok.value == "(") { ++parCount; }
//                else if (tok.value == ")") { --parCount; }
//                else return false;
//                break;
//            case 1:
//                if (tok.value == "(") { ++parCount; state = 0; }
//                else if (tok.type == tokenType::FUNCTION) { state = 6; }
//                else if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
//                else return false;
//                break;
//            case 2:
//                if (tok.type == tokenType::OPERATOR) { state = 4; }
//                else if (tok.value == ")") { --parCount; state = 5; }
//                else return false;
//                break;
//            case 3:
//                if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
//                else if (tok.type == tokenType::FUNCTION) { state = 6; }
//                else return false;
//                break;
//            case 4:
//                if (tok.value == "(") { ++parCount; state = 0; }
//                else if (tok.type == tokenType::FUNCTION) { state = 6; }
//                else if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
//                else if (tok.type == tokenType::OPERATOR) { state = 3; }
//                else return false;
//                break;
//            case 5:
//                if (tok.value == ")") { --parCount; }
//                else if (tok.type == tokenType::OPERATOR) { state = 1; }
//                else return false;
//                break;
//            case 6:
//                if (tok.value == "(") { ++parCount; state = 0; }
//                else return false;
//                break;
//            default: break;
//            }
//
//        }
//
//        if (tokens[tokens.size() - 1].type == tokenType::OPERATOR) {
//            throw std::string("where is second number?");
//        }
//
//        else if (parCount == 0) {
//            return true;
//        }
//
//        else {
//            throw std::string("expression is wrong");
//        }
//    }
//
//    bool checkVarInEXPR(const vector<token>& tokens, const unordered_map<string, double>& variables) {
//
//        for (const token& token : tokens) {
//
//            if (token.type == tokenType::VARIABLE && !variables.count(token.value)) {
//                throw std::string("That variable don't realise");
//            }
//
//        }
//
//        return true;
//
//    }
//
//    void setTypeExp(const vector<token>& tokens, const unordered_map<string, double>& variables, string& simpleStr, const double& lastResult) {
//
//
//        size_t countEquals = 0;
//        for (const auto& token : tokens) {
//            if (token.value == "=") ++countEquals;
//        }
//
//        if (p.checkSim(tokens) && p.checkVarInEXPR(tokens, variables) && lastResult != NOTHING) {
//            typeExp = typeExpression::SIMPLE;
//        }
//
//        else if (countEquals == 1 && tokens.size() == 1 && simpleStr.size() != 0) {
//            typeExp = typeExpression::EQUAL;
//        }
//
//        else if (countEquals == 1 && tokens[0].type == tokenType::VARIABLE && tokens[1].value == "=") {
//            vector<token> subTokens(tokens.begin() + 2, tokens.end());
//            if (p.parserExp(subTokens) && p.checkVarInEXPR(subTokens, variables)) {
//                typeExp = typeExpression::SET;
//            }
//        }
//
//        else if (countEquals == 0 && p.parserExp(tokens) && p.checkVarInEXPR(tokens, variables)) {
//            typeExp = typeExpression::EXPRESSION;
//        }
//
//        else {
//            typeExp = typeExpression::ERROR;
//        }
//    }
//};