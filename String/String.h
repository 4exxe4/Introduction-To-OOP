#pragma once
#include <iostream>
using namespace std;

#define delimiter  "---------------------------------------"

class String
{
	int size;     //размер строки в байтах
	char* str;    //адрес строки в динамической памятм
public:
	int get_size()const;
	const char* get_str()const;
	char* get_str();

	//Constructors:

	explicit String(int size = 80);
	String(const char* str);
	String(const String& other);
	String(String&& other);
	~String();

	//Operators:

	String& operator = (const String& other);
	String& operator = (String&& other);
	char operator[](int i) const;
	char& operator[](int i);

	//Methods:

	void print()const;
};

String operator+ (const String& left, const String& right);
std::ostream& operator << (std::ostream& os, const String& obj);