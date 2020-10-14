#include "Parser.h"
#include "Commands/OpenServerCommand.h"
#include "Tools/Structs.h"
#include "Commands/ConnectCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/SleepCommand.h"
#include "Commands/SetCommand.h"
#include "Commands/IfCommand.h"
#include "Expression/AllExpressions.h"
#include "Commands/WhileCommand.h"


bool Parser::checkIsDouble(string inputString, double &result) {
    char* end;
    result = strtod(inputString.c_str(), &end);
    if (end == inputString.c_str() || *end != '\0') return false;
    return true;
}

void Parser::cal(string leftString, string rightString){
    double result;
    double value;
    string inputSetVars;
    bool isDouble = checkIsDouble(rightString, result);

    if (this->symbolTable->isInVarSymbols(rightString))
        value = this->symbolTable->getSymbolValue(rightString);
    else if (isDouble){
        value = result;
    }
    else{
        Interpreter* interpreter = new Interpreter();
        Expression* exp = nullptr;
        try {
            int size = this->symbolTable->getVarSymbols().size();
            auto iter = this->symbolTable->getVarSymbols().begin();
            for (int i = 0; i< size; i++){
                string currVar = iter->first;
                if (rightString.find(currVar)!=std::string::npos){
                    inputSetVars+=currVar+"="+to_string
                            (iter->second->getValue())+";";
                }
                iter++;
            }
            interpreter->setVariables(inputSetVars);
            exp = interpreter->interpret(rightString);
            value = exp->calculate();
            delete exp;
        } catch (const char* e) {
            if (exp!= nullptr) {
                delete exp;
            }
            std::cout << e << std::endl;
        }
    }

    //add new object to the varSymbols map
    if (this->symbolTable->isInVarSymbols(leftString))
        this->symbolTable->updateSymbol(leftString, value);
}


void Parser::fillCommandMap(){
    this->commandsMap.insert(pair<string,Command*>("openDataServer",new
            OpenServerCommand(this->checkConnection, this->symbolTable,
                              this->serverFinished)));

    this->commandsMap.insert(pair<string,Command*>("connectControlClient",new
            ConnectCommand(this->checkConnection,this->flightControl,
                           this->serverFinished)));

    this->commandsMap.insert(pair<string,Command*>("var",new
            DefineVarCommand(this->symbolTable)));

    this->commandsMap.insert(pair<string,Command*>("Print",new
            PrintCommand(this->symbolTable)));

    this->commandsMap.insert(pair<string,Command*>("Sleep",new SleepCommand()));

    this->commandsMap.insert(pair<string,Command*>("set",new SetCommand
            (this->flightControl, this->symbolTable)));
}

void Parser::parsing(){
    // for each line in lexerFile
    for (unsigned int i = 0; i < this->lexerFile.size(); i++){
        string firstToken = this->lexerFile.at(i)[0];
        // if the first token is a command
        if (firstToken == "while" || firstToken == "While" || firstToken == "if" || firstToken == "If") {
            auto it = this->lexerFile.at(i).begin();
            i++;
            while (i<this->lexerFile.size() && this->lexerFile.at(i)[0].compare("}")!=0){
                this->scope.push_back(lexerFile.at(i));
                i++;
            }

            if (firstToken == "if" || firstToken == "If") {
                this->commandsMap.insert(pair<string, Command *>("if", new IfCommand
                        (this->scope, this->commandsMap, this->symbolTable)));
            } else if (firstToken == "while" || firstToken == "While"){
                this->commandsMap.insert(pair<string, Command *>("while", new WhileCommand
                        (this->scope, this->commandsMap, this->symbolTable)));
            }

            Command *command = this->commandsMap.find(firstToken)->second;
            command->execute(it);
            if (firstToken == "while" || firstToken == "While")
                this->commandsMap.erase("while");
            if (firstToken == "if" || firstToken == "If")
                this->commandsMap.erase("if");
            this->scope.clear();
        }
        else if (this->commandsMap.count(firstToken)){
            auto it = this->lexerFile.at(i).begin();
            Command *command = this->commandsMap.find(firstToken)->second;
            command->execute(it);
        }
            // if the first token is an exisiting var
        else if (this->symbolTable->isInVarSymbols(firstToken)){
            string lastToken = this->lexerFile.at(i)[2];
            // if the last token is also an existing var
            if (this->symbolTable->isInVarSymbols(lastToken)){
                this->symbolTable->updateSymbol(firstToken, this->symbolTable->getSymbolValue(lastToken));
            } else {
                // the last token is a number or an expression
                this->cal(firstToken, lastToken);
            }
            // if the operator is '->' we need to update the simulator
            if (this->symbolTable->getSymbolOper(firstToken).compare("->")== 0){
                auto it = this->lexerFile.at(i).begin();
                Command* setCommand = this->commandsMap.find("set")->second;
                setCommand->execute(it);
            }
        }
    }
    this->serverFinished->exit=true;
    if (this->serverFinished->threads.size())
        this->serverFinished->threads.at(0).join();
}