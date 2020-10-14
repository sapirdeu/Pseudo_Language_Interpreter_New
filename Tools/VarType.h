#ifndef PSEUDO_LANGUAGE_INTERPRETER_VARTYPE_H
#define PSEUDO_LANGUAGE_INTERPRETER_VARTYPE_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// we create a VarType object when we see a new var in fly.txt
class VarType{
private:
    string name;
    double value;
    string sim;
    string oper;

public:
    VarType(string newName, double newVal, string newSim, string newOper){
        this->name=newName;
        this->value=newVal;
        this->sim=newSim;
        this->oper=newOper;
    }
    double getValue();
    string getOper();
    string getSim();
    void setValue(double);
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_VARTYPE_H
