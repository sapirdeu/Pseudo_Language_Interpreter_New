#ifndef PSEUDO_LANGUAGE_INTERPRETER_PRINTCOMMAND_H
#define PSEUDO_LANGUAGE_INTERPRETER_PRINTCOMMAND_H

#include <map>
#include <iostream>
#include "Command.h"
#include "../Tools/SymbolTable.h"


class PrintCommand: public Command{
    SymbolTable* symbolTable;
public:
    PrintCommand(SymbolTable *newSymbolTbl) {
        this->symbolTable = newSymbolTbl;
    }

    virtual void execute(vector<string>::iterator &it);
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_PRINTCOMMAND_H
