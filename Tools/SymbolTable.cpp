#include "SymbolTable.h"

// the method recieves key and value and inserts it to map of var symbols,
// if exists calls updateSymbol function.
void SymbolTable::insertToVarSymbol(string key, VarType* value){
    if (!this->varSymbols.count(key)) {
        this->varSymbols.insert(pair<string, VarType *>(key, value));
    } else {
        updateSymbol(key,value->getValue());
    }
}

// the method recieves key and value and inserts it to map of sim symbols,
// if exists calls updateSymbol function.
void SymbolTable::insertToSimSymbol(string key, VarType* value){
    if (!this->simSymbols.count(key)) {
        this->simSymbols.insert(pair<string, VarType *>(key, value));
    } else {
        updateSymbol(key,value->getValue());
    }
}

// the method receives key and value and if the key exists- updates the new
// value in the maps.
void SymbolTable::updateSymbol(string key, double value){
    if (this->varSymbols.count(key)){
        this->varSymbols.find(key)->second->setValue(value);
    }
    else if (this->simSymbols.count(key)){
        this->simSymbols.find(key)->second->setValue(value);
    }
}

int SymbolTable::isInVarSymbols(string key){
    return this->varSymbols.count(key);
}

int SymbolTable::isInSimSymbols(string key){
    return this->simSymbols.count(key);
}

// the method returns the symbol value (in case it exists in one of the maps)
double SymbolTable::getSymbolValue(string key){
    if (isInVarSymbols(key))
        return this->varSymbols.find(key)->second->getValue();
    else if(this->simSymbols.count(key)){
        return this->simSymbols.find(key)->second->getValue();
    }
}

// the method returns the symbol oper (->, <-, =) (in case it exists in one of
// the maps)
string SymbolTable::getSymbolOper(string key){
    if (isInVarSymbols(key))
        return this->varSymbols.find(key)->second->getOper();
    else if(this->simSymbols.count(key)){
        return this->simSymbols.find(key)->second->getOper();
    }
}

// the method returns the path of the symbol in the simulator
string SymbolTable::getPath(string key){
    if (this->simSymbols.count(key))
        return this->simSymbols.find(key)->second->getSim();
    else if (this->varSymbols.count(key))
        return this->varSymbols.find(key)->second->getSim();
}


// the method returns the varSymbol map
map<string, VarType*> SymbolTable::getVarSymbols(){
    return this->varSymbols;
}

// the method initializes the map of variables from the simulator by index
void SymbolTable::initializeXmlMap(){
    this->xmlMap.insert(pair<int, string>(0,
                                          "/instrumentation/airspeed-indicator/indicated-speed-kt"));

    this->xmlMap.insert(pair<int, string>(1,
                                          "/sim/time/warp"));

    this->xmlMap.insert(pair<int, string>(2,
                                          "/controls/switches/magnetos"));

    this->xmlMap.insert(pair<int, string>(3,
                                          "/instrumentation/heading-indicator/offset-deg"));

    this->xmlMap.insert(pair<int, string>(4,
                                          "/instrumentation/altimeter/indicated-altitude-ft"));

    this->xmlMap.insert(pair<int, string>(5,
                                          "/instrumentation/altimeter/pressure-alt-ft"));

    this->xmlMap.insert(pair<int, string>(6,
                                          "/instrumentation/attitude-indicator/indicated-pitch-deg"));

    this->xmlMap.insert(pair<int, string>(7,
                                          "/instrumentation/attitude-indicator/indicated-roll-deg"));

    this->xmlMap.insert(pair<int, string>(8,
                                          "/instrumentation/attitude-indicator/internal-pitch-deg"));

    this->xmlMap.insert(pair<int, string>(9,
                                          "/instrumentation/attitude-indicator/internal-roll-deg"));

    this->xmlMap.insert(pair<int, string>(10,
                                          "/instrumentation/encoder/indicated-altitude-ft"));

    this->xmlMap.insert(pair<int, string>(11,
                                          "/instrumentation/encoder/pressure-alt-ft"));

    this->xmlMap.insert(pair<int, string>(12,
                                          "/instrumentation/gps/indicated-altitude-ft"));

    this->xmlMap.insert(pair<int, string>(13,
                                          "/instrumentation/gps/indicated-ground-speed-kt"));

    this->xmlMap.insert(pair<int, string>(14,
                                          "/instrumentation/gps/indicated-vertical-speed"));

    this->xmlMap.insert(pair<int, string>(15,
                                          "/instrumentation/heading-indicator/indicated-heading-deg"));

    this->xmlMap.insert(pair<int, string>(16,
                                          "/instrumentation/magnetic-compass/indicated-heading-deg"));

    this->xmlMap.insert(pair<int, string>(17,
                                          "/instrumentation/slip-skid-ball/indicated-slip-skid"));

    this->xmlMap.insert(pair<int, string>(18,
                                          "/instrumentation/turn-indicator/indicated-turn-rate"));

    this->xmlMap.insert(pair<int, string>(19,
                                          "/instrumentation/vertical-speed-indicator/indicated-speed-fpm"));

    this->xmlMap.insert(pair<int, string>(20, "/controls/flight/aileron"));

    this->xmlMap.insert(pair<int, string>(21,
                                          "/controls/flight/elevator"));

    this->xmlMap.insert(pair<int, string>(22, "/controls/flight/rudder"));

    this->xmlMap.insert(pair<int, string>(23, "/controls/flight/flaps"));

    this->xmlMap.insert(pair<int, string>(24,
                                          "/controls/engines/engine/throttle"));

    this->xmlMap.insert(pair<int, string>(25,
                                          "/controls/engines/current-engine/throttle"));

    this->xmlMap.insert(pair<int, string>(26,
                                          "/controls/switches/master-avionics"));

    this->xmlMap.insert(pair<int, string>(27,
                                          "/controls/switches/starter"));

    this->xmlMap.insert(pair<int, string>(28,
                                          "/engines/active-engine/auto-start"));

    this->xmlMap.insert(pair<int, string>(29,
                                          "/controls/flight/speedbrake"));

    this->xmlMap.insert(pair<int, string>(30,
                                          "/sim/model/c172p/brake-parking"));

    this->xmlMap.insert(pair<int, string>(31,
                                          "/controls/engines/engine/primer"));

    this->xmlMap.insert(pair<int, string>(32,
                                          "/controls/engines/current-engine/mixture"));

    this->xmlMap.insert(pair<int, string>(33,
                                          "/controls/switches/master-bat"));

    this->xmlMap.insert(pair<int, string>(34,
                                          "/controls/switches/master-alt"));

    this->xmlMap.insert(pair<int, string>(35, "/engines/engine/rpm"));
}


// the method initializes the map of variables from the simulator by value
void SymbolTable::initializeDataFromSim(){
    this->dataFromSim.insert(pair<string, double >
                                     ("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    this->dataFromSim.insert(pair<string, double>("/sim/time/warp", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/switches/magnetos", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/heading-indicator/offset-deg", 0));

    this->dataFromSim.insert(pair<string, double>(
            "/instrumentation/altimeter/indicated-altitude-ft", 0));

    this->dataFromSim.insert(pair<string, double>(
            "/instrumentation/altimeter/pressure-alt-ft", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/attitude-indicator/indicated-roll-deg", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/attitude-indicator/internal-pitch-deg", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/attitude-indicator/internal-roll-deg", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/encoder/indicated-altitude-ft", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/encoder/pressure-alt-ft", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/gps/indicated-altitude-ft", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/gps/indicated-ground-speed-kt", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/gps/indicated-vertical-speed", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/heading-indicator/indicated-heading-deg",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/magnetic-compass/indicated-heading-deg", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/turn-indicator/indicated-turn-rate", 0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0));

    this->dataFromSim.insert(pair<string, double>("/controls/flight/aileron",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/flight/elevator",0));

    this->dataFromSim.insert(pair<string, double>("/controls/flight/rudder",0));

    this->dataFromSim.insert(pair<string, double>("/controls/flight/flaps",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/engines/engine/throttle",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/engines/current-engine/throttle",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/switches/master-avionics",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/switches/starter",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/engines/active-engine/auto-start",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/flight/speedbrake",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/sim/model/c172p/brake-parking",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/engines/engine/primer",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/engines/current-engine/mixture",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/switches/master-bat",0));

    this->dataFromSim.insert(pair<string, double>
                                     ("/controls/switches/master-alt",0));

    this->dataFromSim.insert(pair<string, double>("/engines/engine/rpm",0));
}


// the method updates the map of variables from the simulator by value
void SymbolTable::updateValuesFromXml(string serverData){
    char* splitValues = strtok(const_cast<char *>(serverData.c_str()), ",");

    for (int i = 0; i < 36; i++){
        string key = this->xmlMap.find(i)->second;
        if (this->dataFromSim.count(key)) {
            this->dataFromSim.find(key)->second = atof(splitValues);
        }

        if (this->simSymbols.count(key)){
            this->simSymbols.find(key)->second->setValue(atof(splitValues));
        }
        splitValues = strtok(NULL, ",");
    }
}

// the method returns the symbol value from dataFromSim map
double SymbolTable::getDataFromSimSymbolValue(string key){
    if (this->dataFromSim.count(key)){
        return this->dataFromSim.find(key)->second;
    }
}

