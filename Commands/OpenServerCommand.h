#ifndef PSEUDO_LANGUAGE_INTERPRETER_OPENSERVERCOMMAND_H
#define PSEUDO_LANGUAGE_INTERPRETER_OPENSERVERCOMMAND_H

#include "Command.h"
#include "../Tools/SymbolTable.h"
#include "../Tools/Structs.h"
#include <vector>
#include <strings.h>

//class OpenServerCommand
class OpenServerCommand : public Command{
private:
    CheckConnection* checkConnection;
    ServerFinished* serverFinished;
    SymbolTable* symbolTable;

public:
    OpenServerCommand(CheckConnection* newCheckConnection, SymbolTable*
    newsymbolTable, ServerFinished* newServerFinished){
        checkConnection = newCheckConnection;
        symbolTable = newsymbolTable;
        serverFinished = newServerFinished;
    }
    void* serverFunc(int);
    virtual void execute(vector<string>::iterator &);
};

//this struct is the input to the function of the server thread
struct socketServerArguments {
    int port;
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_OPENSERVERCOMMAND_H
