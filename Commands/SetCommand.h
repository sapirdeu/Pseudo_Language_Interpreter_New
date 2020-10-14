#ifndef PSEUDO_LANGUAGE_INTERPRETER_SETCOMMAND_H
#define PSEUDO_LANGUAGE_INTERPRETER_SETCOMMAND_H

#include "Command.h"
#include "../Tools/Structs.h"
#include "../Tools/SymbolTable.h"

class SetCommand: public Command {
private:
    FlightControl* flightControl;
    SymbolTable* symbolTable;

public:
    SetCommand(FlightControl* newFlightControl, SymbolTable* newSymbolTable){
        this->flightControl = newFlightControl;
        this->symbolTable = newSymbolTable;
    }

    virtual void execute(vector<string>::iterator &);
    bool checkIsDouble(string, double &);
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_SETCOMMAND_H
