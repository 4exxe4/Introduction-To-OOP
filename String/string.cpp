#include <iostream>
using namespace std;

#define delimiter  "---------------------------------------"

class String
{
	int size;     //размер строки в байтах
	char* str;    //адрес строки в динамической памятм
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
	explicit String(int size = 80)
	{
		//Конструктор по умолчанию создает пустую строку размером 80 байт
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaulConstructor:\t " << this << endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1; //strlen() возвращает размер строки в символах, +1 нужен для выделения памяти под nullterminator
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		//this->str = other.str;     //ShallowCopy
		//Deep copy:
		this->size = other.size;
		this->str = new char [size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];

		cout << "CopyConstructor: \t" << this << endl;
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
		// this->str = other.str; Shallow copy - Поверхностное копирование
		///-----------------------------------------///
		//0) Проверяем, не является ли тот объект этим объектом
		if (this == &other)return *this;
		//1) Удаляем старую динамическую память
		delete[] this->str;
		//Deep copy - побитовое копирование:
		this->size = other.size;
		//2) Выделяем новую динамическую память
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
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

#define CONSTRUCTORS_CHECK
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

	String str5 = str3 + str4;
	cout << str5 << endl;
	cout << delimiter << endl;

#endif // CONSTRUCTORS_CHECK

#ifdef COPY_SEMANTIC_CHECK

	String str1 = "Hello";
	str1 = str1;
	cout << str1 << endl;

	String str2;
	str2= str1;
	cout << str2 << endl;

#endif // COPY_SEMANTIC_CHECK
}
/*
Использование динамической памяти в классе:
Если в классе есть хотя бы один указатель, то скорее всего, класс использует динамическую память
И если это так, то конструктор будет выделять эту память оператором "new"
А если конструктор выделяет память оператором "new", то в классе обязательно должен быть деструктор с оператором "delete".

То есть деструктор обязательно должен удалять динамическую память в конструкторе.

При перегрузке конструкторов в таком классе, если в хотя бы одном конструкторе написан оператор "new", то и все остальные конструкторы будут выделять память оператором "new".

В классе, который использует динамическую память, для указателей не пишут set методы.

Ошибка на этапе выполнения "debug assertion failed" возникает, когда оператор "delete" выполняется два раза по одному адресу

В классе, который использует динамическую память, обязательно должны быть реализованы CopyConstructor и CopyAssignment и они обязательно должны выполнять побитовое копирование (DeepCopy), а именно выделять память оператором "new"
и копировать содержимое этой памяти из другого объекта в наш.

Неявные конструктор копирования и оператор присваивания выполняют поверхностное копирование (shallow copy). То есть не выделяют новую память под объект, а копируют адрес памяти из другого объекта в наш, в результате чего возникает ситуация, когда есть два и более объекта, которые владеют одной и той же областью динамической памяти, что приводит к непредсказуемым последствиям. Как правило, это часто вызывает "debug assertion failed".
Чтобы избежать таких ситуаций, в классах с динамической памятью обязательно нужно реализовывать CopyConstructor и CopyAssignment.

CopyAssignment прежде чем выделить новую дмнамическую память обязательно должен удалить старую динамическую память.
Прежде, чем удалять динамическую память, нужно убедиться в том, что CopyAssignment не принял тот объект для которого он вызывается.

Конструктор копирования и оператор присваивания еще называют CopyMethods или CopySemantic.

 Перегрузка оператора []:

 Оператор "[]" принимает индекс элемента массива и возвращает значение по индексу.

*/