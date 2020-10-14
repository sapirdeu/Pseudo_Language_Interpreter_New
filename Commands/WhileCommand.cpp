#include "WhileCommand.h"
#include "../Expression/AllExpressions.h"
#include "../Tools/VarType.h"
#include <map>

bool WhileCommand::checkIsDouble(string inputString, double &result) {
    char* end;
    result = strtod(inputString.c_str(), &end);
    if (end == inputString.c_str() || *end != '\0') return false;
    return true;
}

void WhileCommand::cal(string leftString, string rightString){
    double result;
    double value;
    string inputSetVars;
    bool isDouble = checkIsDouble(rightString, result);

    if (this->symbolTable->isInVarSymbols(rightString))
        value = this->symbolTable->getSymbolValue(rightString);
    else if (isDouble){
        value = result;
    }
    else{
        Interpreter* interpreter = new Interpreter();
        Expression* exp = nullptr;
        try {
            int size = this->symbolTable->getVarSymbols().size();
            auto iter = this->symbolTable->getVarSymbols().begin();
            for (int i = 0; i< size; i++){
                string currVar = iter->first;
                if (rightString.find(currVar)!=std::string::npos){
                    inputSetVars+=currVar+"="+to_string
                            (iter->second->getValue())+";";
                }
                iter++;
            }
            interpreter->setVariables(inputSetVars);
            exp = interpreter->interpret(rightString);
            value = exp->calculate();
            delete exp;
        } catch (const char* e) {
            if (exp!= nullptr) {
                delete exp;
            }
            std::cout << e << std::endl;
        }
    }

    //add new object to the varSymbols map
    if (this->symbolTable->isInVarSymbols(leftString))
        this->symbolTable->updateSymbol(leftString, value);
}

// the method receives a condition and checks if it's correct (satisfied)
bool WhileCommand::isCondCorrect(vector<string>::iterator &it) {
    Interpreter *interpreter = new Interpreter();
    Expression *expRight = nullptr;
    Expression *expLeft = nullptr;

    string exL = *(++it);
    string op = *(++it);
    string exR = *(++it);
    string inputSetVars = "";
    double valueRight;
    double valueLeft;
    --(--(--it));
    try {
        map<string, VarType *> map1 = this->symbolTable->getVarSymbols();
        int size = map1.size();
        auto iter = map1.begin();
        for (int i = 0; i< size; i++){
            string currVar = iter->first;
            if ((exR.find(currVar) != std::string::npos) || (exL.find(currVar) != std::string::npos)) {
                inputSetVars += currVar + "=" + to_string(iter->second->getValue()) + ";";
            }
            iter++;
        }

        interpreter->setVariables(inputSetVars);

        expRight = interpreter->interpret(exR);
        valueRight = expRight->calculate();
        delete expRight;

        expLeft = interpreter->interpret(exL);
        valueLeft = expLeft->calculate();
        delete expLeft;

    } catch (const char *e) {
        if (expRight != nullptr) {
            delete expRight;
        } else if (expLeft != nullptr) {
            delete expLeft;
        }
        std::cout << e << std::endl;
    }

    if (op.compare("==") == 0) {
        return valueLeft == valueRight;
    } else if (op.compare("!=") == 0) {
        return valueLeft != valueRight;
    } else if (op.compare("<=") == 0) {
        return valueLeft <= valueRight;
    } else if (op.compare(">=") == 0) {
        return valueLeft >= valueRight;
    } else if (op.compare("<") == 0) {
        return valueLeft < valueRight;
    } else if (op.compare(">") == 0) {
        return valueLeft > valueRight;
    }

    return false;
}

void WhileCommand::execute(vector<string>::iterator &it) {
    while (this->isCondCorrect(it)) {
        for (unsigned int i = 0; i < this->scope.size(); i++) {
            string firstToken = this->scope.at(i)[0];
            // if the first token is a command
            if (this->commandsMap.count(firstToken)) {
                auto iter = this->scope.at(i).begin();
                Command *command = this->commandsMap.find(firstToken)->second;
                command->execute(iter);
            }
                // if the first token is an exisiting var
            else if (this->symbolTable->isInVarSymbols(firstToken)) {
                string lastToken = this->scope.at(i)[2];
                // if the last token is also an existing var
                if (this->symbolTable->isInVarSymbols(lastToken)) {
                    this->symbolTable->updateSymbol(firstToken, this->symbolTable->getSymbolValue(lastToken));
                } else {
                    // the last token is a number or an expression
                    this->cal(firstToken, lastToken);
                }
                // if the operator is '->' we need to update the simulator
                if (this->symbolTable->getSymbolOper(firstToken).compare("->") == 0) {
                    auto iter = this->scope.at(i).begin();
                    Command *setCommand = this->commandsMap.find("set")->second;
                    setCommand->execute(iter);
                }
            }
        }
    }
    this->scope.clear();
}