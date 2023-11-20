#pragma once

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif // _WIN332


#ifdef _WIN32
#else
char _getch() {
	char buf = 0;
	struct termios old = { 0 };
	fflush(stdout);
	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror("tcsetattr ~ICANON");
	std::cout << buf;
	return buf;
}
#endif // _WIN32

//char readingchar() {
//	char ch;
//#ifdef _WIN32
//	ch = _getch();
//#else
//	ch = getin();
//#endif // _WIN32
//	return ch;
//}

template<typename T>
class Universal_Input {
public:
	Universal_Input() = default;
	Universal_Input(char first_symbol, char last_symbol)
		: _first_symbol(first_symbol), _last_symbol(last_symbol) {}

	T input() {

		while (true) {

			_str[_counter] = _getch();

			if (_str[_counter] >= _first_symbol && _str[_counter] <= _last_symbol) {
				std::cout << _str[_counter];
				_counter++;
			}
			else if (_str[_counter] == _back_space) {
				if (_counter == 0) continue;
				else {
					std::cout << "\b" << " " << "\b";
					_counter--;
				}
			}
			else if (_str[_counter] == _enter) {
				if (_str[0] == _enter) continue;
				else {
					_str[_counter] = '\0';
					break;
				}
			}
			else {
				_str[_counter] = '\0';
				std::cout << " " << "\b";
			}
		}
		if constexpr (std::is_same_v<T, int>)  return atoi(_str);
		else return std::string(_str);
	}

	void clear() {
		_str[0] = '\0';
		_counter = 0;
	}

private:
	char _first_symbol{};
	char _last_symbol{};
#ifdef _WIN32
	const char _back_space{ 8 };
	const char _enter{ 13 };
#else
	const char _back_space{ 127 };
	const char _enter{ 10 };
#endif // _WIN32

	char _str[256]{};
	int _counter{ 0 };
};
