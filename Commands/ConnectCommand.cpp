#include "ConnectCommand.h"
#include "../Tools/Structs.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <thread>

#include <chrono>
#include <typeinfo>

using namespace std;

void ConnectCommand::func(char serverBuffer[256], ssize_t numCharR, int clientSocket){
    while(!this->flightControl->controlCommand.empty()){
        bzero(serverBuffer,256);
        string command = this->flightControl->controlCommand.at(0);
        if (command[0] == 's'){
            this->flightControl->controlCommand.erase(this->flightControl->controlCommand.begin());
            strcpy(serverBuffer, command.c_str());
            ssize_t numCharW = write(clientSocket, serverBuffer, strlen(serverBuffer));
            if (numCharW < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
        else{
            this->flightControl->controlCommand.erase(this->flightControl->controlCommand.begin());
        }
        bzero(serverBuffer,256);
    }
}


void* ConnectCommand::clientFunc(int clientSocket) {
    char serverBuffer[256];
    ssize_t numCharR;
    while(!this->clientFinished->exit) {
        this->func(serverBuffer, numCharR, clientSocket);
    }
    this->func(serverBuffer, numCharR, clientSocket);
}


void ConnectCommand::execute(vector<string>::iterator &it) {
    struct socketClientArguments* args = new socketClientArguments();
    string ip = *(++it);
    ip = ip.substr(1,ip.length()-2);
    string port = *(++(it));
    args->ip = ip;
    args->port = stoi(port);

    //create a sockaddr obj - hold the address of server
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(args->ip.c_str());
    serverAddress.sin_port = htons((uint16_t)((size_t)args->port));

    //create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //if we didn't succeed to create a socket, we print an error
    if (clientSocket == -1) {
        std::cerr << "Could not create a socket"<<std::endl;
        exit(1);
    }

    while (!this->checkConnection->isConnect) {
    }

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        exit(1);
    }

    this->clientFinished->threads.push_back(std::thread(&ConnectCommand::clientFunc,this, clientSocket));
}

