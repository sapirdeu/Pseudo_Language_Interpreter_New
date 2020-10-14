#ifndef PSEUDO_LANGUAGE_INTERPRETER_CONNECTCOMMAND_H
#define PSEUDO_LANGUAGE_INTERPRETER_CONNECTCOMMAND_H

#include "Command.h"
#include "../Tools/Structs.h"
#include <vector>
#include <strings.h>


//class ConnectCommand
class ConnectCommand : public Command{
private:
    CheckConnection* checkConnection;
    FlightControl* flightControl;
    ServerFinished* clientFinished;

public:
    ConnectCommand(CheckConnection* newCheckConnection, FlightControl*
    newFlightControl, ServerFinished* newClientFinished){
        checkConnection = newCheckConnection;
        flightControl = newFlightControl;
        clientFinished = newClientFinished;
    }

    virtual void execute(vector<string>::iterator &);
    void* clientFunc(int);
    void func(char*, ssize_t, int);
};

//this struct is the input to the function of the server thread
struct socketClientArguments {
    string ip;
    int port;
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_CONNECTCOMMAND_H
