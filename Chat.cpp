#include "Chat.h"

Chat::Chat(){
	greeting();
}

Chat::Chat(std::string active_user_login, std::string active_recipient_login, std::string active_user_name) :
	_active_user_login(active_user_login), _active_recipient_login(active_recipient_login), _active_user_name(active_user_name) {}

//---------------- Приветствие ------------------------------------------------------------
void Chat::greeting() {
	clean_console();
	std::cout << "\n          Добро пожаловать!\n\n";
}

//----------------- Прощание --------------------------------------------------------------
void Chat::farewell() {
	std::cout << "\n\n          Всего хорошего.\n";
}

//----------------- Меню входа ------------------------------------------------------------
int Chat::logOrReg() {
	Universal_Input<int> inputLOR('1', '3');
	std::cout << "\n Вход - 1\n";
	std::cout << " Регистрация - 2 \n";
	std::cout << " Выход - 3 \n -> ";

	return inputLOR.input();
}

//---------------- Меню в аккаунте -------------------------------------------------------
int Chat::menu_chat() {
	Universal_Input<int> inputMC('1', '3');
	std::cout << "\n Выбрать беседу - 1\n";
	std::cout << " Создать сообщение всем - 2 \n";
	std::cout << " Выход из аккаунта - 3 \n ";
	std::cout << " -> ";
	return inputMC.input();
}

//--------------- Проверка логина -------------------------------------------------------
bool Chat::finding(std::string login) {
	if (_users.find(login) == _users.end()) return true;
	else return false;
}

//--------------- Проверка пароля -------------------------------------------------------
bool Chat::check_password(std::string password, std::string login) {
	if (_users.at(login).user_password() == password) return true;
	else return false;
}

//--------------- Вход и регистрация ----------------------------------------------------
void Chat::registration(int menu, bool* check_user) {
	User user;
	Universal_Input<std::string> inputPL(_fsymbolLogPass, _lsymbolLogPass);
	*check_user = false;
	// Вход в чат
	if (menu == 1) {
		std::cout << "\n Введите логин: ";
		user.get_user_login(inputPL.input());
		std::cout << "\n Введите пароль: ";
		user.get_user_password(inputPL.input());
		int counter = 0;

		if (!finding(user.user_login()) && check_password(user.user_password(), user.user_login())) {
			clean_console();
			get_user(user.user_login(), _users.at(user.user_login()).user_name());
			std::cout << "\n\n Вы вошли как:\n\n";
			_users.at(_active_user_login).showUser();
			*check_user = true;
		}
		else {
			std::cout << "\n Не верный логин или пароль!";
			system_pause(2);
			return;
		}

	}
	// регистрация нового пользователя
	else {
		*check_user = true;
		std::cout << " Введите имя: ";
		std::string username;
		std::cin >> username;
		user.get_user_name(username);
		std::cout << " Введите логин (латинский алфавит, цифры, символы): ";
		bool check_login;
		do {
			check_login = true;
			user.get_user_login(inputPL.input());
			if (!finding(user.user_login())) {
				user.clear_login();
				inputPL.clear();
				std::cout << "\n Данный логин занят, выберите другой: ";
				check_login = false;
			}
		} while (!check_login);

		std::cout << "\n Введите пароль (латинский алфавит, цифры, символы): ";
		user.get_user_password(inputPL.input());

		_users.emplace(user.user_login(), user);
		get_user(user.user_login(), user.user_name());

		clean_console();
		std::cout << "\n\n Вы зарегистрированы как:\n\n";
		_users.at(_active_user_login).showUser();
	}
}

//----------------- Регистрация общего чата ---------------------------------------
void Chat::reg_all_user() {
	User user;
	user.get_user_login("ALL_USERS");
	user.get_user_password("admin");
	user.get_user_name("общий чат");
	_users.emplace(user.user_login(), user);
}

//---------------- Вывод списка участников чата -----------------------------------
void Chat::showListUsers() {
	int counter{ 0 };
	clear_show_user();
	std::cout << "\n Участники чата:\n\n";

	for (std::map<std::string, User>::iterator it = _users.begin(); it != _users.end(); it++) {
		counter++;
		if (it->second.user_login() == _active_user_login) continue;
		std::cout << counter << " - ";
		if (it->second.user_login() == "ALL_USERS") it->second.showUserName();
		else it->second.showUser();
		std::cout << "\n";
	}
}

//--------------- Возвращает логин активного пользователя --------------------------
std::string Chat::active_user_login() {
	return _active_user_login;
}

//--------------- Возвращает имя активного пользователя -----------------------------
std::string Chat::active_user_name() {
	return _active_user_name;
}

//--------------- Возвращает логин получателя ---------------------------------------
std::string Chat::active_recipient_login() {
	return _active_recipient_login;
}

//--------------- Активация пользователя --------------------------------------------
void Chat::get_user(std::string login, std::string name)
{
	_active_user_login = login;
	_active_user_name = name;
}

//--------------- Деактивация пользователя ------------------------------------------
void Chat::out_user() {
	_active_user_login = '\0';
	_active_user_name = '\0';

}

//--------------- Выбор получателя -------------------------------------------------
void Chat::get_recipient(int menu) {
	Universal_Input<int> inputID('0', '9');
	int counter = 0;

	if (menu == 2) _active_recipient_login = "ALL_USERS";
	else {
		int id{ 0 };
		do {
			id = inputID.input();
			if (id < 1 || id > _users.size()) {
				std::cout << "\n Не верный ID, повторите выбор: ";
			}
			else break;

		} while (true);

		std::map<std::string, User>::iterator it = _users.begin();
		for (; it != _users.end(); it++) {
			counter++;
			if (counter == id) break;
		}

		_active_recipient_login = it->second.user_login();
	}
}

//------------- Определение количества пользователей --------------------------------
int Chat::sizeList() {
	return _users.size();
}

//------------- Создание и отправка сообщения ---------------------------------------
void Chat::send_message() {
	Message message;
	std::string mess{};
	char menu{ ' ' };
	while (true) {
		std::cout << " Написать - \"Enter\", Выход - \"Esc\" -> ";
		menu = _getch();

		if (menu == _esc) {
			clear_show_user();
			break;
		}
		else if (menu == _enter) {
			std::cout << "\n сообщение:\n";
			while (mess.empty()) {
				getline(std::cin, mess);
			}
			message.create_message(mess, _active_user_name, _active_user_login, _active_recipient_login);
			_messages.push_back(message);
			clear_show_user();
			std::cout << "\n Сообщение ";
			if (_active_recipient_login == "ALL_USERS") std::cout << " в общий чат\n";
			else {
				std::cout << " для ";
				_users.at(_active_recipient_login).showUserName();
			}
			std::cout << " отправлено \n";
			break;
		}
		else std::cout << " хм, можно повторить? \n";
	}
	system_pause(2);
}

//----------------- Вывод беседы ----------------------------------------------------------
void Chat::show_message_list() {
	clear_show_user();
	std::cout << "\n Беседа с \n";
	_users.at(_active_recipient_login).showUser();
	for (Message i : _messages) {
		if (_active_user_login == i.login_sender() && _active_recipient_login == i.login_recipient() && _active_recipient_login != "ALL_USERS"
			|| _active_user_login == i.login_recipient() && _active_recipient_login == i.login_sender()) {

			i.show_message();
		}
		else if (_active_recipient_login == "ALL_USERS" && _active_recipient_login == i.login_recipient()) i.show_message();
		
	}
}

//----------------- Действие если пользователь один --------------------------------------
void Chat::one_user() {
	std::cout << " вы пока единственный пользователь. \n Зайдите попозже, когда ещё кто ни будь зарегистрируется.\n";
	out_user();
	system_pause(2);
	clean_console();
}

//----------------- Действие если пользователей нет --------------------------------------
void Chat::no_users() {
	std::cout << "\n Зарегистрированных пользователей пока нет. \n Пожалуйста сначала зарегистрируйтесь.\n ";
	system_pause(2);
	clean_console();
}

//----------------- Вывод активного пользователя с очисткой консоли ----------------------- 
void Chat::clear_show_user()
{
	clean_console();
	_users.at(_active_user_login).showUser();
}

//----------------- Очистка консоли -------------------------------------------------------
void Chat::clean_console(){
#ifdef _WIN32
	std::system("cls");  // Очистка экрана в системе Windows
#else
	std::system("clear");  // Очистка экрана в системах UNIX и Linux
#endif
}

//----------------- Пауза -----------------------------------------------------------------
void Chat::system_pause(int second){
	std::this_thread::sleep_for(std::chrono::seconds(second));

}

//----------------- Основна функция работы чата -------------------------------------------
void Chat::chat_work(){

	while(_work) {

		_menu = logOrReg();
		clean_console();
		// выход из аккаунта
		if (_menu == 3) {
			farewell();
			_work = false;
			break;
		}
		// вход в аккаунт
		else if (_menu == 1) {
			if (sizeList() == 1) {
				no_users();
				continue;
			}
			std::cout << " Вход \n";
			registration(_menu, &_check_user);
			if (sizeList() == 2) {
				one_user();
				continue;
			}

			if (_check_user == false) {
				system_pause(2);
				clean_console();
				continue;
			}

		}
		//регистрация нового пользователя
		else {
			std::cout << " Регистрация:\n";
			registration(_menu, &_check_user);
		}
		// проверка кол-ва зарегистрированных
		if (sizeList() == 2) {
			one_user();
			continue;
		}
		//работа аккаунта
		account_work();
	}
}

//--------------------- Функция работы аккаунта ------------------------------------
void Chat::account_work(){

	do {
		_menu = menu_chat();
		_discussion = true;
		switch (_menu) {
		case 1: // личная беседа
			showListUsers();
			std::cout << " ID собеседника: ";
			get_recipient(_menu);
			show_message_list();
			send_message();
			break;
		case 2: // сообщение всем
			get_recipient(_menu);
			send_message();
			break;
		case 3: // выход
			out_user();
			clean_console();
			_discussion = false;
			break;

		default:
			break;
		}

	} while (_discussion);
}

