#include "OpenServerCommand.h"
#include "../Tools/Structs.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>


using namespace std;


void* OpenServerCommand::serverFunc(int serverSocketForClient) {
    string data = "";
    /* start communication between the simulator (as client) to the
     * interpreter (as server) */
    char dataFromClient[1024];
    ssize_t numChar;
    while(!this->serverFinished->exit) {
        bzero(dataFromClient,1024);
        numChar = read(serverSocketForClient, dataFromClient, 1023);
        if (numChar < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        data.append(dataFromClient);
        char* splitValues = strtok(const_cast<char *>(data.c_str()), "\n");

        this->symbolTable->updateValuesFromXml(splitValues);
        data.erase(0, data.find("\n") + 1);
    }
}

void OpenServerCommand::execute(vector<string>::iterator &it){
    struct socketServerArguments* args = new socketServerArguments();
    args->port = stoi(*(++it));

    //create the sockaddr object
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons((uint16_t)((size_t)args->port));

    //create socket
    int serverMainSocket = socket(AF_INET, SOCK_STREAM, 0);


    //if we didn't succeed to create a socket, we print an error
    if (serverMainSocket == -1) {
        std::cerr << "Could not create a socket"<<std::endl;
        exit(1);
    }

    //bind socket to IP address
    if (bind(serverMainSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        exit(1);
    }

    //making socket listen to the port
    if (listen(serverMainSocket, 1) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        exit(1);
    }

    socklen_t clilen = sizeof(sockaddr_in);

    int serverSocketForClient = accept(serverMainSocket, (struct sockaddr *)
            &serverAddress,&clilen);


    //if we didn't succeed to create a socket, we print an error
    if (serverSocketForClient == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        exit(1);
    }

    this->checkConnection->isConnect = true;

    //serverFunc(serverSocketForClient);
    thread serverThread(&OpenServerCommand::serverFunc,this,serverSocketForClient);
    serverThread.detach();
    sleep(3);
}