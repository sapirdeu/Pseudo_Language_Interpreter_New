#include "DefineVarCommand.h"
#include "../Expression/AllExpressions.h"
#include <stdlib.h>
#include <iostream>
#include "string.h"


bool DefineVarCommand::checkIsDouble(string inputString, double &result) {
    char* end;
    result = strtod(inputString.c_str(), &end);
    if (end == inputString.c_str() || *end != '\0') return false;
    return true;
}

void DefineVarCommand::execute(vector<string>::iterator &it){
    string name = *(++it);
    string oper = *(++it);
    string sim = "";
    double value;
    bool isSim = false;

    if (oper.compare("->") == 0 || oper.compare("<-") == 0){
        isSim = true;
        sim = *(++(++it));
        sim = sim.substr(1,sim.length()-2);
    } else {
        sim = "";
        string expression = *(++it);
        string inputSetVars;
        double result;
        bool isDouble = checkIsDouble(expression, result);

        if (this->symbolTable->isInVarSymbols(expression))
            value = this->symbolTable->getSymbolValue(expression);
        else if (isDouble){
            value = result;
        }
        else{
            Interpreter* interpreter = new Interpreter();
            Expression* exp = nullptr;
            try {
                int size = this->symbolTable->getVarSymbols().size();
                auto iter = this->symbolTable->getVarSymbols().begin();
                for (int i = 0; i < size; i++){
                    string currVar = iter->first;
                    if (expression.find(currVar)!=std::string::npos){
                        inputSetVars+=currVar+"="+to_string
                                (iter->second->getValue())+";";
                    }
                    iter++;
                }
                interpreter->setVariables(inputSetVars);
                exp = interpreter->interpret(expression);
                value = exp->calculate();
                delete exp;
            } catch (const char* e) {
                if (exp!= nullptr) {
                    delete exp;
                }
                std::cout << e << std::endl;
            }
        }
    }
    VarType* newVarType;
    if(!isSim){
        //create new VarType
        newVarType = new VarType(name, value, sim, oper);
        //add new object to the varSymbols map
        this->symbolTable->insertToVarSymbol(name, newVarType);
    } else {
        newVarType = new VarType(name, this->symbolTable->getDataFromSimSymbolValue(sim), sim, oper);
        this->symbolTable->insertToVarSymbol(name, newVarType);
        this->symbolTable->insertToSimSymbol(sim, newVarType);
    }
}
