#include <iostream>
using namespace std;

#define delimiter  "---------------------------------------"

class String
{
	int size;     //������ ������ � ������
	char* str;    //����� ������ � ������������ ������
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}

	char* get_str()
	{
		return str;
	}

	//Constructors:
	explicit String(int size = 80):size(size), str (new char[size] {})
	{
		//����������� �� ��������� ������� ������ ������ �������� 80 ����
		//this->size = size;
		//this->str = new char[size] {};
		cout << "DefaulConstructor:\t " << this << endl;
	}
	String(const char* str):
		size(strlen(str) +1),
		str(new char[size] {})
	{
		//this->size = strlen(str) + 1; //strlen() ���������� ������ ������ � ��������, +1 ����� ��� ��������� ������ ��� nullterminator
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other):size(other.size),str(new char[size] {})
	{
		//this->str = other.str;     //ShallowCopy
		//Deep copy:
		//this->size = other.size;
		//this->str = new char [size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];

		cout << "CopyConstructor: \t" << this << endl;
	}
	String(String&& other):size(other.size), str(other.str)
	{
		//MoveConstructor - ShallowCopy:
		//this->size = other.size;
		//this->str = other.str;
		//�������� ����������� ������, ��� ����, ����� ������������� �������� ��� �������� ������������.
		other.size = 0;
		other.str = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] str;
		str = nullptr;
		size = 0;
		cout << "Destructor:\t" << this << endl;
	}
	//Operators:
	String& operator = (const String& other)
	{
		// this->str = other.str; Shallow copy - ������������� �����������
		///-----------------------------------------///
		//0) ���������, �� �������� �� ��� ������ ���� ��������
		if (this == &other)return *this;
		//1) ������� ������ ������������ ������
		delete[] this->str;
		//Deep copy - ��������� �����������:
		this->size = other.size;
		//2) �������� ����� ������������ ������
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	String& operator = (String&& other)
	{
		//0) ��������, �� �������� �� "this" � "other" ����� � ��� �� ��������
		if (this == &other)return *this;
		//1) �������� ������ �������
		delete[] str;
		//2) Shallow copy;
		this->size = other.size;
		this->str = other.str;
		//3) �������� ����������� ������
		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment:\t\t" << this << endl;
	}
	char operator[](int i) const
	{
		return str[i];  //Index operator, subscript operator
	}
	char& operator[](int i) 
	{
		return str[i];
	}

	//Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+ (const String& left, const String& right)
{
	String result (left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		result[i] = left[i];
		//result.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}

std::ostream& operator << (std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//#define CONSTRUCTORS_CHECK
//#define COPY_SEMANTIC_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK 

	String str1;
	str1.print();
	cout << delimiter << endl;

	String str2 (5); //Conversion from 'int' to 'String'
	str2.print();
	cout << delimiter << endl;

	String str3 = "Hello";
	str3.print();
	cout << str3 << endl;
	cout << delimiter << endl;

	String str4 = "World";
	cout << str4 << endl;
	cout << delimiter << endl;

	String str5;
	str5 = str3 + str4;
	cout << delimiter << endl;
	cout << str5 << endl;

#endif // CONSTRUCTORS_CHECK

#ifdef COPY_SEMANTIC_CHECK

	String str1 = "Hello";
	str1 = str1;
	cout << str1 << endl;

	String str2;
	str2= str1;
	cout << str2 << endl;

#endif // COPY_SEMANTIC_CHECK

//MoveMethods (MoveSemantic)

	String str1;           //DefaultConstructor
	str1.print();

	String str2(5);
	str2.print();

	String str3 = "Hello"; //Single-argument Constructor (const char str[])
	str3.print();

	String str4(); 
	/*
	� ���� ������ �� ���������� DefaultConstructor, � �� ��������� ������. 
	����� ����������� ������� 'str4', ������� ������ �� ���������, � ���������� �������� ���� 'String'.
	�� ����, ������� ������ �� ������ ����� ����� ������������ �� ���������.
	���� ���� ������������� ���� ������� ����������� �� ���������, ��� ����� ������� � ������� �������� ������
	*/

	String str5{};
	/*
	��� ������ ��� ���� �������� DefaultConstructor()
	*/
	str5.print();

	String str6{ 6 };     //Single-Argument Constructor (int)
	str6.print();

	String str7{ "World" };
	str7.print();

	String str8 = str7;
	str8.print();

	String str9(str8);
	str9.print();

	String str10{ str9 };
	str10.print();

	//�������� ������ ��� ������ ������������� ������� ������������ � ������� �������������

	String str11 = str3 + str8;
	str11.print();
}
/*
������������� ������������ ������ � ������:
���� � ������ ���� ���� �� ���� ���������, �� ������ �����, ����� ���������� ������������ ������
� ���� ��� ���, �� ����������� ����� �������� ��� ������ ���������� "new"
� ���� ����������� �������� ������ ���������� "new", �� � ������ ����������� ������ ���� ���������� � ���������� "delete".

�� ���� ���������� ����������� ������ ������� ������������ ������ � ������������.

��� ���������� ������������� � ����� ������, ���� � ���� �� ����� ������������ ������� �������� "new", �� � ��� ��������� ������������ ����� �������� ������ ���������� "new".

� ������, ������� ���������� ������������ ������, ��� ���������� �� ����� set ������.

������ �� ����� ���������� "debug assertion failed" ���������, ����� �������� "delete" ����������� ��� ���� �� ������ ������

� ������, ������� ���������� ������������ ������, ����������� ������ ���� ����������� CopyConstructor � CopyAssignment � ��� ����������� ������ ��������� ��������� ����������� (DeepCopy), � ������ �������� ������ ���������� "new"
� ���������� ���������� ���� ������ �� ������� ������� � ���.

������� ����������� ����������� � �������� ������������ ��������� ������������� ����������� (shallow copy). �� ���� �� �������� ����� ������ ��� ������, � �������� ����� ������ �� ������� ������� � ���, � ���������� ���� ��������� ��������, ����� ���� ��� � ����� �������, ������� ������� ����� � ��� �� �������� ������������ ������, ��� �������� � ��������������� ������������. ��� �������, ��� ����� �������� "debug assertion failed".
����� �������� ����� ��������, � ������� � ������������ ������� ����������� ����� ������������� CopyConstructor � CopyAssignment.

CopyAssignment ������ ��� �������� ����� ������������ ������ ����������� ������ ������� ������ ������������ ������.
������, ��� ������� ������������ ������, ����� ��������� � ���, ��� CopyAssignment �� ������ ��� ������ ��� �������� �� ����������.

����������� ����������� � �������� ������������ ��� �������� CopyMethods ��� CopySemantic.

------------------------------------------------------------------------------------------------------

 ���������� ��������� []:

 �������� "[]" ��������� ������ �������� ������� � ���������� �������� �� �������.

 MoveMethods (MoveSemantic):

 �� ����� ���� ����������� ����������� � �������� ������������ �������� �� ����� ������ ��������� ������, ������� ����� �� ����� �����������, ����� ������ �� ������.
 �� ����������� �������, ��� �������, �������� ������� ������ � ������������� �������. ��� ������ ������ �������� ������, ��� ������ ������� �� ���� ��������.
 ����������� ������ �������� ���������������� ���������, � ������� �������� ������� ������������������.
 ������ ������� �������� C++ 11 �������� "MoveSemantic", ������� ��������� �������� ������ ����������� ���, ��� ��� ��� ����� ��������. � ������ ��� �������� ���������� ������� �� ����� ������ �� ��������.
 ������ ����, ����� ���������� �������� ���������� ���������� ������� �� ����� ������ ���������� ������� ��� �������� �� ����� ������ � ���� ������� ����� ����� ������ ��� ������������� ������������ ������.
 

 MoveMethods (MoveConstructor/MoveAssignment) ������ ��� ������ ����������, ����� ����������� ��� ������������ ������ ����� ������������������� ��������� ���������� ����������� �������.
 ��� ������ ������ ���������� ����������� (DeepCopy) ��������� ������������� ����������� (ShellCopy).
 ����� ������� ������ ���������� ���������� ������� ��������� �� ����� ������ � �������������� ���� ������� ����������� ��� ������������ ������, � ����������� �� ���������.

 ����� ���������� ShallowCopy MoveMethods ����������� ������ �������� ����������� ������, ��� ����, ����� �������� �������� �������� ����� ������� ������������.

 ������ �������� ��������� �� ��������� � �� ������, � r-value reference 

 ------------------------------------------------------------------------------------------------------

 The rule of 3:

 ���� � ������ ������������ ������������ ������, �� ���� ����� ����������� ������ �������� ������� 3:
 1) Destructor - ����������� ������ ���������� delete [];
 2) CopyConstructor - ��������� ��������� ����������� (DeepCopy)
 3) CopyAssignment - ������ �� �� �����, ��� CopyConstructor, �� ��� ������������� �������.
 4) MoveConstructor - ��������� ������������� ����������� (ShallowCopy)
 5) MoveAssignment - ��������� ������������� ����������� 

 ����� ������ ��������� C++, ������� ���� MoveConstructor, ������� ��������� ������������� �����������, "the rule of 3" ����� "the rule of 5".

 ���� � ������ �� ������������ ������������ ������, �� ����� ������������� "the rule of 0":
 � ������ �� ����� �� ���� �� ����������������� �������.

 ------------------------------------------------------------------------------------------------------

 ������������� � ���������:

 �������������� � ��������� ������������ ������������ � ��� �������, � ������� ��������� ���������� ����� ������.
 ������������� � ��������� �������� ������ � �������������.
 ���� ���� ������ �������� ����������, �� ��� ����� ������������������� ������ � ���������

*/