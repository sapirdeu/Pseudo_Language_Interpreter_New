#ifndef PSEUDO_LANGUAGE_INTERPRETER_ALLEXPRESSIONS_H
#define PSEUDO_LANGUAGE_INTERPRETER_ALLEXPRESSIONS_H

#include "Expression.h"
#include <stack>
#include <string>
#include <iostream>
#include <map>


using namespace std;


// Value Class
class Value : public Expression{
private:
    double val;
public:
    Value(double newVal): val(newVal) {}
    virtual double calculate();
    ~Value() {};
};


//Variable Class
class Variable : public Expression{
private:
    string name;
    double value;
public:
    Variable(string newName, double newVar): name(newName), value(newVar) {}
    double calculate();
    Variable& operator++();
    Variable& operator++(int);
    Variable& operator--();
    Variable& operator--(int);
    Variable& operator+=(double);
    Variable& operator-=(double);
    ~Variable() {};
};


//UnaryOperator Class
class UnaryOperator : public Expression{
protected:
    Expression *ex;
public:
    UnaryOperator(Expression *newEx): ex(newEx){};
    //double calculate()=0;
    ~UnaryOperator() {delete ex;};
};


//UMinus Class
class UMinus : public UnaryOperator{
public:
    UMinus(Expression *newValue);
    double calculate();
    ~UMinus() {};
};


//UPlus Class
class UPlus : public UnaryOperator{
public:
    UPlus(Expression *newValue);
    double calculate();
    ~UPlus() {};
};


//BinaryOperator Class
class BinaryOperator : public Expression{
protected:
    Expression *right;
    Expression *left;
public:
    BinaryOperator(Expression *newLeft, Expression *newRight);
    ~BinaryOperator() {delete(right); delete(left);};
};


//Plus Class
class Plus : public BinaryOperator{
public:
    Plus(Expression *newLeft, Expression *newRight);
    double calculate();
    ~Plus() {};
};


//Minus Class
class Minus : public BinaryOperator{
public:
    Minus(Expression *newLeft, Expression *newRight);
    double calculate();
    ~Minus() {};
};


//Mul Class
class Mul : public BinaryOperator{
public:
    Mul(Expression *newLeft, Expression *newRight);
    double calculate();
    ~Mul() {};
};


//Div Class
class Div : public BinaryOperator{
public:
    Div(Expression *newLeft, Expression *newRight);
    double calculate();
    ~Div() {};
};


//Interpreter Class
class Interpreter{
private:
    map<string,string> mapping;
public:
    int isOperator(char);
    int isOperand(char);
    int isNumber(string);
    int operatorPriority(string);
    int comparePriority(string, string);
    string convertInitPostfix(string);
    double postfixCalculateBinary(double, char, double);
    double postfixCalculateUnary(double, char);
    string findNewToken(string, int);
    string setValueToVar(string);
    Expression* interpret(string);
    void checkValidSet(string, string);
    void checkValidExp(string);
    void setVariables(string);
    bool isDoubleOperator(string);
    string noDoubleOperator(string);
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_ALLEXPRESSIONS_H
