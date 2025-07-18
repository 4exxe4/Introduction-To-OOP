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
	explicit String(int size = 80):size(size), str (new char[size] {})
	{
		//Конструктор по умолчанию создает пустую строку размером 80 байт
		//this->size = size;
		//this->str = new char[size] {};
		cout << "DefaulConstructor:\t " << this << endl;
	}
	String(const char* str):
		size(strlen(str) +1),
		str(new char[size] {})
	{
		//this->size = strlen(str) + 1; //strlen() возвращает размер строки в символах, +1 нужен для выделения памяти под nullterminator
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
		//Обнуляем принимаемый объект, для того, чтобы предотвратить удаление его ресурсов деструктором.
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
	String& operator = (String&& other)
	{
		//0) Проверка, не являются ли "this" и "other" одним и тем же объектом
		if (this == &other)return *this;
		//1) Удаление старой памяоти
		delete[] str;
		//2) Shallow copy;
		this->size = other.size;
		this->str = other.str;
		//3) Обнуляем принимаемый объект
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
	В этой строке не вызывается DefaultConstructor, и не создается объект. 
	Здесь объявляется функция 'str4', которая ничего не принимает, и возвращает значение типа 'String'.
	То есть, круглые скобки не делают явный вызов конструктора по умолчанию.
	Если есть необходимость явно вызвать конструктор по умолчанию, это можно сделать с помощью фигурных скобок
	*/

	String str5{};
	/*
	Эта строка уже явно вызывает DefaultConstructor()
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

	//Фигурные скобки для вызова конструкторов следует использовать с большой осторожностью

	String str11 = str3 + str8;
	str11.print();
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

------------------------------------------------------------------------------------------------------

 Перегрузка оператора []:

 Оператор "[]" принимает индекс элемента массива и возвращает значение по индексу.

 MoveMethods (MoveSemantic):

 На самом деле конструктор копирования и оператор присваивания копируют на место вызова локальный объект, который сразу же после копирования, будет удален из памяти.
 На копирование объекта, как правило, тратятся ресурсы памяти и процессорного времени. Чем больше памяти занимает объект, тем больше времени на него тратится.
 Копирование всегда является ресурсозатратной операцией, а затраты ресурсов снимают производительность.
 Именно поэтому стандарт C++ 11 добавили "MoveSemantic", которая позволяет избежать лишних копирований там, где без них можно обойтись. А именно при возврате локального объекта на место вызова по значению.
 Вместо того, чтобы копировать значение удаляемого локального объекта на место вызова происходит перенос его значения на место вызова и этот перенос имеет смысл только при использовании динамической памяти.
 

 MoveMethods (MoveConstructor/MoveAssignment) всякий раз неявно вызываются, когда создаваемый или существующий объект нужно проинициализировать значением временного безымянного объекта.
 Эти методы вместо побитового копирования (DeepCopy) выполняют поверхностное копирование (ShellCopy).
 Таким образом память удаляемого локального объекта переносят на место вызова и инициализируют этой памятью создаваемый или существующий объект, в зависимости от контекста.

 После выполнения ShallowCopy MoveMethods обязательно должны обнулить принимаемый объект, для того, чтобы избежать удаления ресурсов этого объекта деструктором.

 Методы переноса принимают не константу и не ссылку, а r-value reference 

 ------------------------------------------------------------------------------------------------------

 The rule of 3:

 Если в классе используется динамическая память, то этот класс обязательно должен отвечать правилу 3:
 1) Destructor - освобождает память оператором delete [];
 2) CopyConstructor - выполняет побитовое копирование (DeepCopy)
 3) CopyAssignment - делает то же самое, что CopyConstructor, но для существующего объекта.
 4) MoveConstructor - выполняет поверхностное копирование (ShallowCopy)
 5) MoveAssignment - выполняет поверхностное копирование 

 После выхода стандарта C++, который ввел MoveConstructor, которые выполняют поверхностное копирование, "the rule of 3" стало "the rule of 5".

 Если в классе не используется динамическая память, то класс соответствует "the rule of 0":
 В классе не нужен ни один из вышеперечисленных методов.

 ------------------------------------------------------------------------------------------------------

 Инициализация в заголовке:

 Инициализаторы в заголовке конструктора отрабатывают в том порядке, в котором объявлены переменные члены класса.
 Инициализация в заголовке доступна только в конструкторах.
 Если член класса является константой, то его можно проинициализировать только в заголовке

*/