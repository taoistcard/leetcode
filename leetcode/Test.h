#pragma once
#include <string>
struct stEmtpy
{
};
class CEmptyClass
{

};

class CBase1
{
public:
	virtual void func1(){}
};

class CBase2
{
public:
	virtual void func2(){}
};

class CDriver1 : public CBase1
{
public:
	virtual void func_driver1(){}
};

class CDriver2 : public CBase1, CBase2
{
public:
	virtual void func_driver2(){}
};

class CDDriver1 : public CDriver1
{
public:
	virtual void func_ddriver1(){}
};

//二进制和十六进制字符串互相转换
char c_2_num(char c);
void hexStringToBin(char buffer[], int buffer_len, std::string& hex_s);
std::string binToHexString(char data[], int data_len);