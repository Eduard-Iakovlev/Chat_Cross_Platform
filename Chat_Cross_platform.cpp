// Chat_Cross_platform.cpp: определяет точку входа для приложения.
//

#include "Chat_Cross_platform.h"

using namespace std;

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
#endif // _WIN32

	Chat chat;
	chat.reg_all_user(); // регистрация аккаунта общего чата
	chat.chat_work(); // работа чата
}
