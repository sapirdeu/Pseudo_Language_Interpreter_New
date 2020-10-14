#include "PrintCommand.h"

void PrintCommand::execute(vector<string>::iterator &it){
    if (it[1].at(0) == '\"'){
        cout<< it[1].substr(1,it[1].length()-2) <<endl;
    } else {
        cout<< this->symbolTable->getSymbolValue(it[1]) << endl;
    }
}