#include <iostream>
using namespace std;

class Fraction; //объявление класса
Fraction operator*(Fraction left, Fraction right); //объявление оператора
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction //Описание класса
{
	int integer;     //Целая часть
	int numerator;   //Числитель
	int denominator; //Знаменатель

public:

	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}

	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

//Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer) //explicit - явный
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:" << this << endl;
	}
	Fraction(double decimal)
	{
		//decimal - десятичная дробь
		decimal += 1e-10;
		integer = decimal;    //получаем целую часть дроби
		decimal -= integer;   //убираем целую часть из десятичной дроби
		denominator = 1e+9;   //получаем максимально возможный знаменатель 1000000000
		numerator = decimal * denominator; //вытаскиваем дробную часть в числитель
		reduce();
		cout << "SingleArgumentConstructor: " << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

//Operators:
	Fraction& operator =(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	Fraction& operator *= (const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator /=(const Fraction& other)
	{
		return *this = *this / other;
	}
//Incremento/Decremento:
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction& operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator--()
	{
		integer--;
		return *this;
	}
	const Fraction operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
	}

//Type-cast operators:
	explicit operator int()const
	{
		//const в начале заголовка метода означает, что метод возвращает константное значение
		//const в конце заголовка метода означает, что метод - константный, то есть не изменяет объект, для которого вызывается
		//Абсолютно все переменные члены класса внутри константного метода evaluate as a constant, то есть расцениваются как константы 
		//to_improper();
		return integer + numerator / denominator;
	}
	operator double()const
	{
		return integer + (double)numerator / denominator;
	}
//Methods:
	Fraction& to_improper()
	{
		//перевод в неправильную дробь:
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		//перевод в правильную дробь:
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator); //swap - меняет местами две переменные
		return inverted;
	}
	Fraction& reduce()
	{
		int more, less, rest;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

Fraction operator+ (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	);
}

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	/*
	Fraction result;
	result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denominator(left.get_denominator() * right.get_denominator());
	return result;
	*/
	/*
	Fraction result
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	);
	result.to_proper();
	return result;
	*/

	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

//Comparison operators

bool operator == (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() ==
		right.get_numerator() * left.get_denominator();
}
bool operator != (const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator > (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}

bool operator < (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator >=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
	//return left > right || left == right;
}
bool operator <=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
	//return left < right || left == right;
}
std::ostream& operator << (std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if(obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if(obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
std::istream& operator >> (std::istream& is, Fraction& obj)
{
	const int SIZE = 256;     //размер буфера ввода.
	char buffer[SIZE] = {};   //буфер ввода.
	//is >> buffer;
	is.getline(buffer, SIZE);
	const char delimiters[] = "(/, )";
	int n = 0;               //количество ввеленных чисел
	int numbers[3] = {};     //числа, введенные с клавиатуры
	for (
		char* pch = strtok(buffer, delimiters); 
		pch && n < 3; 
		pch = strtok(NULL, delimiters)
		)
		numbers[n++] = atoi(pch);   //atoi() - ASCII-string to Integer
	//for (int i = 0; i < n; i++)cout << numbers[i] << "\t"; cout << endl;
	switch (n)
	{
	case 0:obj = Fraction(); break;
	case 1:obj = Fraction(numbers[0]); break;
	case 2:obj = Fraction(numbers[0],numbers [1]); break;
	case 3:obj = Fraction(numbers[0],numbers [1], numbers [2]); break;
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ARITTMETICAL_OPERATORS_CHECK
//#define INCREMENTAl_CHECK
//#define COMPARISON_OPERATORS
#define STREAMS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSIONS_FROM_OTHER_TO_CLASS
//#define CONVERSIONS_FROM_CLASS_TO_OTHER
//#define HAVE_A_NICE_DAY
void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;     //Default constructor
	A.print();

	Fraction B = 5; //Single-Argument constructor
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITTMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();
	Fraction B(3, 4, 5);
	B.print();

	Fraction C = A * B;
	C.print();

	C = A / B;
	C.print();

	A *= B;
	A.print();

	A /= B;
	A.print();
#endif // ARITTMETICAL_OPERATORS_CHECK

#ifdef INCREMENTAL_CHECK
	Fraction A(2, 3, 4);
	Fraction B = ++A;
	A.print();
	B.print();
#endif // INCREMENTAL_CHECK

#ifdef COMPARISON_OPERATORS

	cout << (2 == 3) << endl;
	cout << (Fraction(1, 2) >= Fraction(5, 10)) << endl;

#endif // COMPARISON OPERATORS

#ifdef STREAMS_CHECK
	Fraction A(2, 3, 4);
	cout << "Введите простую дробь: ";
	cin >> A;
	cout << A << endl;
#endif // STREAMS_CHECK

#ifdef TYPE_CONVERSIONS_BASICS

	cout << (int)(3.14) << endl;
	int a = 2;    //No conversion
	double b = 3; //Conversion from less to more
	int c = b;    //Conversion from more to less without data loss
	int d = 5.5;  //Conversion from more to less with data loss

#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS

	Fraction A = 5; //Single-Argument constructor (from less to more)
	cout << A << endl;

	Fraction B; 
	B = 8;

#endif // CONVERSIONS_FROM_OTHER_TO_CLASS

#ifdef CONVERSIONS_FROM_CLASS_TO_OTHER

	Fraction A(2, 3, 4);
	A.to_improper().print();
	int a = (int)A;
	cout << a << endl;

	double b = A;  //
	cout << b << endl;

#endif // CONVERSIONS_FROM_CLASS_TO_OTHER

#ifdef HAVE_A_NICE_DAY
	Fraction A = 3.33; 3.14159265359; //Conversion from 'double' to 'Fraction'
	cout << A << endl;

#endif // HAVE_A_NICE_DAY

}

/*
Преобразование типов:
В языке C++ существует явное и неявное преобразование типов (expcilit - явное преобразование типов, implicit - неявное преобразование типов).

Для того, чтобы явно преобразовать значение в другой тип данных, необходимо желаемый тип данных указать в круглых скобках перед значением
(type)value - C-like notation - C-подобная форма записи
type(value) - Functional notation - функциональная форма записи

Явное преобразование выполняет программист
Неявное преобразование выполняет компилятор, а именно - оператор

Как явное, так и неявное преобразование бывают от меньшего к большему или от большего к меньшему(может привести к потере данных, компилятор выдает предупреждение C4244).
Все операторы в C++ приводят все значения в выражении к наибольшему типу данных для того, чтобы избежать потери данных
Операторы присваивания всегда приводят значение справа к типу слева, если типы преобразуются. И не важно, произойдет ли про этом потеря данных или нет.

Преобразование типов в ООП:

1) Из другого типа в класс (from other to Class)
2) Из класса в другие типы (from Class to other)

Для того, чтобы другие типы преобразовывать в объекты класса, в классе должны быть конструктор с одним параметром и оператор присваивания (второй не работает без первого)
Для того, чтобы объекты класса преобразовать в другие типы данных, в классе должны быть соответствующие операторы преобразования. 
Операторы преобразования это самые обычные методы, имя которых состоит из ключевого слова "operator" и спецификатора существуюго типа.
Операторы преобразования всегда возвращают значение, но перед ними никогда не пишется тип возвращаемого значения, поскольку он является частью имени функции.
К операторам преобразования так же применимо слово exlpicit
*/