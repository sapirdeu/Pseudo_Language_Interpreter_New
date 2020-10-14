#ifndef PSEUDO_LANGUAGE_INTERPRETER_COMMANDS_H
#define PSEUDO_LANGUAGE_INTERPRETER_COMMANDS_H

#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual void execute(vector<string>::iterator &it) = 0;
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_COMMANDS_H
