#include "SetCommand.h"
#include <iostream>

bool SetCommand::checkIsDouble(string inputString, double &result) {
    char* end;
    result = strtod(inputString.c_str(), &end);
    if (end == inputString.c_str() || *end != '\0') return false;
    return true;
}

void SetCommand::execute(vector<string>::iterator &it){
    string var = *it;
    string newValue = *(++(++it));
    string finalString = "set ";
    string path = this->symbolTable->getPath(var);
    finalString += path.substr(0, path.length());
    finalString += " ";

    double result;
    bool isNum;

    isNum = checkIsDouble(newValue, result);
    if (isNum){
        finalString += newValue;
        this->symbolTable->updateSymbol(var, stod(newValue));
    }

    else{
        finalString += to_string(this->symbolTable->getSymbolValue(var));
    }
    finalString += "\r\n";

    if (isNum)
        this->symbolTable->updateSymbol(var, stod(newValue));
    this->flightControl->controlCommand.push_back(finalString);

    if (finalString[0] != 's' || this->flightControl->controlCommand.at
            (this->flightControl->controlCommand.size()-1)[0] != 's'){
        exit(1);
    }
}