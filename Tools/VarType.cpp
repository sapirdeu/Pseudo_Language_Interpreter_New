#include "VarType.h"

double VarType:: getValue(){
    return this->value;
}

void VarType:: setValue(double val){
    this->value=val;
}

string VarType::getOper(){
    return this->oper;
}

string VarType::getSim(){
    return this->sim;
}