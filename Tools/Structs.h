#ifndef PSEUDO_LANGUAGE_INTERPRETER_STRUCTS_H
#define PSEUDO_LANGUAGE_INTERPRETER_STRUCTS_H

#include <map>
#include <string>
#include <list>
#include "../Commands/Command.h"
#include "SymbolTable.h"
#include <thread>

using namespace std;

struct CheckConnection{
    bool isConnect;
};

struct ServerFinished{
    bool exit;
    std::vector<std::thread> threads;
};

struct FlightControl{
    vector<string> controlCommand;
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_STRUCTS_H
