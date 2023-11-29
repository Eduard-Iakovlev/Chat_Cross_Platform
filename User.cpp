#include "User.h"

User::User(std::string name, std::string login, std::string password) :
	_name{ name }, _login{ login }, _password{ password} {}

//------------------- Вывод логина и имени пользователя --------------------------------
void User::showUser() {
	std::cout << _login << " / ";
	std::cout << _name;
}

//------------------- Вывод имени пользователя -----------------------------------------
void User::showUserName() {
	std::cout << _name << "\n";
}

//------------------- Возвращает имя пользователя --------------------------------------
std::string User::user_name() {
	return _name;
}

//------------------- Возвращает логин пользователя ------------------------------------
std::string User::user_login() {
	return _login;
}

//------------------- Возвращает пароль пользователя -----------------------------------
std::string User::user_password() {
	return _password;
}

//------------------- Присвоение имени пользователя -----------------------------------
void User::get_user_name(std::string name) {
	_name = name;
}

//------------------- Присвоение логина пользователя -----------------------------------
void User::get_user_login(std::string login) {
	_login = login;
}

//------------------ Хеширование и присвоение пароля пользователя ----------------------
void User::get_user_password(std::string password) {
	std::size_t hashed = hash_fn(password);
	_password = hashed;
}

//------------------ Очистка логина пользователя. --------------------------------------
void User::clear_login() {
	_login.clear();
}

