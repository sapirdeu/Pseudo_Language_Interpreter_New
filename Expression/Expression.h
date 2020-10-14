#ifndef PSEUDO_LANGUAGE_INTERPRETER_EXPRESSION_H
#define PSEUDO_LANGUAGE_INTERPRETER_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_EXPRESSION_H
