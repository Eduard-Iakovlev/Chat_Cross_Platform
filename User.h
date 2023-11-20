#include <iostream>
#include <string>
#include "Hash.h"


class User {
public:
	User() = default;
	User(std::string, std::string, std::string);

	void showUser();
	void showUserName();

	std::string user_name();
	std::string user_login();
	std::string user_password();

	void get_user_name(std::string);
	void get_user_login(std::string);
	void get_user_password(std::string);

	void clear_login();

private:
	std::string _name;
	std::string _login;
	std::string _password;
};
