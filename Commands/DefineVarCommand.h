#ifndef PSEUDO_LANGUAGE_INTERPRETER_DEFINEVARCOMMAND_H
#define PSEUDO_LANGUAGE_INTERPRETER_DEFINEVARCOMMAND_H

#include <map>
#include <string.h>
#include <vector>
#include "../Tools/SymbolTable.h"
#include "Command.h"
#include "../Tools/VarType.h"

using namespace std;

class DefineVarCommand: public Command {
    SymbolTable *symbolTable;

public:
    DefineVarCommand(SymbolTable *newVarsSymbols) {
        this->symbolTable = newVarsSymbols;
    }

    virtual void execute(vector<string>::iterator &);

    bool checkIsDouble(string, double &);
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_DEFINEVARCOMMAND_H
