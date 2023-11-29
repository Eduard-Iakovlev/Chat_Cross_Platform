#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include<iostream>
#include<string.h>
#include "Message.h"
#include "User.h"

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <io.h>
#pragma comment(lib, "Ws2_32.lib")

#else
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#endif

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

//char message[MESSAGE_LENGTH];

class Net {
public:
	Net() = default;
	void socket_file();
	int socket_file_description();
	void server_address();
	void connect();

	void receiving_user();


private:
int _socket_file_descriptor, _connection, _bind_status, _connection_status;
struct sockaddr_in _server_address, _client;
socklen_t _length;
Message _message;
User _user;
};

