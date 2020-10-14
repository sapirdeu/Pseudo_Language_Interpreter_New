#include <unistd.h>
#include "SleepCommand.h"
#include <iostream>

void SleepCommand::execute(vector<string>::iterator &it){
    int timeToSleep = atoi((*(++it)).c_str());
    sleep(timeToSleep/1000);
}