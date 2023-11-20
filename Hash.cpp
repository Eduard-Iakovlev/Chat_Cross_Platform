#include "Hash.h"

std::size_t hash_fn(const std::string& password)
{
	std::hash<std::string> hash_f;
	return hash_f(password);
}
