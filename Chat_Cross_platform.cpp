#include "Chat_Cross_platform.h"

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
