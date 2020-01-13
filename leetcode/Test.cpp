#include "Test.h"
#include <stdio.h>
#include <sstream>
#include <iomanip>

char c_2_num(char c)
{
	char num = 0;
	if (c >= '0' && c <= '9')
	{
		num = c - '0';
	}
	else if (c >= 'A' && c <= 'F')
	{
		num = c - 'A' + 10;
	}
	else if (c >= 'a' && c <= 'f')
	{
		num = c - 'a' + 10;
	}
	return num;
}

void hexStringToBin(char buffer[], int buffer_len, std::string& hex_s)
{
	std::istringstream is(hex_s);
	unsigned int i = 0;
	while ( i < buffer_len)
	{
		if (hex_s.size() < i * 2 + 1)
			break;
		char h = hex_s.at(i * 2);
		char l = hex_s.at(i * 2 + 1);

		buffer[i] = c_2_num(h);
		buffer[i] <<= 4;
		buffer[i] |= c_2_num(l);
		i++;
	}
}

std::string binToHexString(char data[], int data_len)
{
	std::stringstream ss;
	ss << std::hex;
	for (unsigned int i = 0; i < data_len; i++)
	{
		ss << std::setw(2);
		ss << std::setfill('0');
		ss << (int)data[i];
	}
	return ss.str();
}