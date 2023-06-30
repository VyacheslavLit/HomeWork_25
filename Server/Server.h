#pragma once
#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include "Times.h"

#ifdef __Linux__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#elif defined(_WIN32)||defined(_WIN64)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <mysql.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
#else 
#error Not implemented!
#endif

using namespace std;

#define MESSAGE_LENGTH 1024 //максимальныйразмер буфера для данных
#define PORT 7777 //будем использовать этот номер порта

class Server
{
private:
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int sockert_file_descriptor, connection, bind_status, connection_status;
    char message[MESSAGE_LENGTH];


public:
    void miServer();
private:
    string zaprosMySQL(string);
    string reg(string);
    string changPassw(string pass);
    void pauses();
};
