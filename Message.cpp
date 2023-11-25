#include "Message.h"

Message::Message(std::string mass, std::string name, std::string sender, std::string recipient) :
	_mass(mass), _name_sender(name), _login_sender(sender), _login_recipient(recipient) {}

//------- Создание сообщение ---------------------------------------------------
void Message::create_message(std::string mass, std::string name, std::string login_sender, std::string login_recipient) {
	_mass = mass;
	_name_sender = name;
	_login_sender = login_sender;
	_login_recipient = login_recipient;
}

//------- Вывод сообщения в списке ----------------------------------------------
void Message::show_message() {
	std::cout << "\n |" << _login_sender << " / " << _name_sender << "|\n";
	std::cout << "--------------------:\n";
	std::cout << _mass << "\n";
	std::cout << "--------------------------------------------------------\n";
}

//------- Возвращает логин отправителя ------------------------------------------
std::string Message::login_sender() {
	return _login_sender;
}

//------- Возвращает логин получателя --------------------------------------------
std::string Message::login_recipient() {
	return _login_recipient;
}
