#pragma once
#include <iostream>
#include <string.h>


#ifdef __Linux__
#include <unistd.h>
#include <sys/acct.h>
#include <arpa/inet.h>
#elif defined(_WIN32)||defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")
#else 
#error Not implemented!
#endif

using namespace std;

#define MESSAGE_LENGTH_CL 1024 //Максимальный размер буфера для данных
#define PORT_CL 7777 //будем использовать этот номер порта


string client(string message);

