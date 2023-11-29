#include "Net.h"

//----------- Создание сокета ---------------------------
void Net::socket_file(){
	_socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_file_descriptor == -1) {
        std::cout << "Не удалось создать сокет!" << std::endl;
        exit(1);
    }
}

//------------ Возврат значения сокета -----------------------
int Net::socket_file_description(){
    return _socket_file_descriptor;
}

//------------ Настройка порта и привязка сокета -------------
void Net::server_address(){
    // 
    _server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    _server_address.sin_port = htons(PORT);
    // Используем IPv4
    _server_address.sin_family = AF_INET;
    // Привяжем сокет
    _bind_status = bind(_socket_file_descriptor, (struct sockaddr*)&_server_address,
        sizeof(_server_address));
    if (_bind_status == -1) {
        std::cout << " Не удалось выполнить привязку сокета!" << std::endl;
        exit(1);
    }
}

//------------ Постановка сервера на прием ----------------------
void Net::connect(){
    _connection_status = listen(_socket_file_descriptor, 5);
    if (_connection_status == -1) {
        std::cout << " Сокет не может прослушивать новые подключения!" << "\n";
        exit(1);
    }
    else {
        std::cout << "Сервер прослушивает новое соединение: " << "\n";
    }
    _length = sizeof(_client);
    _connection = accept(_socket_file_descriptor, (struct sockaddr*)&_client, &_length);
    if (_connection == -1) {
        std::cout << "Сервер не может принять данные от клиента!" << "\n";
        exit(1);
    }
}

//-------------- Прием данных о пользователе --------------------
void Net::receiving_user(){
    while (1) {
        memset(&_user, 0, MESSAGE_LENGTH);
        read(_connection, _user, sizeof(_user));
        if (strncmp("end", _user, 3) == 0) {
            std::cout << "Client Exited." << "\n";
            std::cout << "Server is Exiting..!" << "\n";
            break;
        }
    }
}

