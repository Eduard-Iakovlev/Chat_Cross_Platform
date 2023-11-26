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
        std::cout << "Server is listening for new connection: " << "\n";
    }
    _length = sizeof(_client);
    _connection = accept(_socket_file_descriptor, (struct sockaddr*)&_client, &_length);
    if (_connection == -1) {
        std::cout << "Server is unable to accept the data from client.!" << "\n";
        exit(1);
    }
}
