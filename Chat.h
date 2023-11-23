#pragma once

#include <vector>
#include <map>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "User.h"
#include "Message.h"
#include "Consol_Input.h"
#include "Hash.h"


class Chat
{
public:
	Chat();
	Chat(std::string, std::string, std::string);
	void greeting();
	void farewell();
	int logOrReg();
	int menu_chat();

	bool finding(std::string);
	bool check_password(std::string, std::string);
	void registration(int, bool*);
	void reg_all_user();

	void showListUsers();
	std::string active_user_login();
	std::string active_user_name();
	std::string active_recipient_login();


	void get_user(std::string, std::string);
	void out_user();
	void get_recipient(int);


	int sizeList();

	void send_message();
	void show_message_list();

	void one_user();
	void no_users();

	void clear_show_user();
	void clean_console();
	void system_pause(int second);

	void chat_work();
	void account_work();


private:
	std::map <std::string, User> _users;
	std::vector<Message> _messages;
	std::string _active_user_login;
	std::string _active_recipient_login;
	std::string _active_user_name;

	int _menu{ 0 };

	bool _work{ true };
	bool _check_user{ false };
	bool _discussion{ true };

	const char _fsymbolLogPass = '0';
	const char _lsymbolLogPass = '~';

#ifdef _WIN32
	const char _enter{ 13 };
	const char _esc{ 27 };
#else
	const char _enter{ 10 };
	const char _esc{ 27 };
#endif // _WIN32


};
