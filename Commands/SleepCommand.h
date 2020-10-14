#ifndef PSEUDO_LANGUAGE_INTERPRETER_SLEEPCOMMAND_H
#define PSEUDO_LANGUAGE_INTERPRETER_SLEEPCOMMAND_H

#include "Command.h"

class SleepCommand: public Command {
public:
    virtual void execute(vector<string>::iterator &it);
};

#endif //PSEUDO_LANGUAGE_INTERPRETER_SLEEPCOMMAND_H
