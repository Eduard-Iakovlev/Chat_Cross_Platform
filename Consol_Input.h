#pragma once
#include <iostream>
#include <string>
#include "Get.h"

#ifdef _WIN32
#include <conio.h>
#else
#endif // _WIN332


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
