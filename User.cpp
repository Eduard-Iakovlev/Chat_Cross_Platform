#include "User.h"

User::User(std::string name, std::string login, std::string password) :
	_name{ name }, _login{ login }, _password{ password } {}

void User::showUser() {
	std::cout << _login << " / ";
	std::cout << _name << "\n";
}
void User::showUserName() {
	std::cout << _name << "\n";
}

std::string User::user_name() {
	return _name;
}

std::string User::user_login() {
	return _login;
}

std::string User::user_password() {
	return _password;
}

void User::get_user_name(std::string name) {
	_name = name;
}

void User::get_user_login(std::string login) {
	_login = login;
}

void User::get_user_password(std::string password) {
	std::size_t hashed = hash_fn(password);
	_password = hashed;
}

void User::clear_login() {
	_login.clear();
}

