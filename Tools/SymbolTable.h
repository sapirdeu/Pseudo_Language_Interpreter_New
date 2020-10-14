#ifndef PSEUDO_LANGUAGE_INTERPRETER_SYMBOLTABLE_H
#define PSEUDO_LANGUAGE_INTERPRETER_SYMBOLTABLE_H

#include <map>
#include <string>
#include <string.h>
#include "VarType.h"
#include <stdio.h>
#include <iostream>

using namespace std;

class SymbolTable {
private:
    //varSymbols maps between variable from fly.txt to the suitable VarType*
    map<string, VarType*> varSymbols;
    //simSymbols maps between path in simulator to the suitable VarType*
    map<string, VarType*> simSymbols;
    //xmlMap contains all the <node> values from the generic_small.xml by index
    map<int,string> xmlMap;
    //simSymbols maps between path in simulator to the new value we
    // received from the simulator
    map<string, double> dataFromSim;


public:
    SymbolTable() {
        initializeXmlMap();
        initializeDataFromSim();
    }
    void insertToVarSymbol(string, VarType*);
    void insertToSimSymbol(string, VarType*);
    void updateSymbol(string, double);
    int isInVarSymbols(string);
    int isInSimSymbols(string);
    double getSymbolValue(string);
    string getSymbolOper(string);
    string getPath(string);
    map<string, VarType*> getVarSymbols();
    void initializeXmlMap();
    void initializeDataFromSim();
    void updateValuesFromXml(string);
    double getDataFromSimSymbolValue(string);
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_SYMBOLTABLE_H
