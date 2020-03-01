#include <iostream>
#include <conio.h>
#include <fcntl.h>
#include <io.h>


#define maxPow	99

class Polynom {

private:
	int value[maxPow + 1] = { 0,0,0,0,0,0,0,0,0,0 };

public:
	int get_factor(int degree) {
		if (degree < 0) degree *= -1;
		return value[degree % (maxPow + 1)];
	}
	void set_factor(int degree, int val) {
		if (degree < 0) degree *= -1;
		value[degree % (maxPow + 1)] = val;
	}

	Polynom operator+(Polynom b) {
		Polynom result;

		for (int i = 0; i <= maxPow; i++)
			result.value[i] = value[i] + b.value[i];

		return result;
	}

	Polynom operator-(Polynom b) {
		Polynom result;
		for (int i = 0; i <= maxPow; i++)
			result.value[i] = value[i] - b.value[i];
		return result;
	}

	Polynom operator*(Polynom b) {
		Polynom result;
		for (int i = 0; i <= maxPow; i++)
			for (int j = 0; j <= maxPow; j++) {
				if (i + j <= maxPow)
					result.value[i + j] += value[i] * b.value[j];
				else if (value[i] != 0 and b.value[j] != 0)
					throw L"Power is not expected to be more than 99!";
			}
		return result;
	}

	void operator += (Polynom b) {
		*this = *this + b;
	}
	void operator -= (Polynom b) {
		*this = *this - b;
	}
	void operator *= (Polynom b) {
		*this = *this * b;
	}
};

#define SIZE						120

#define KEY_BACKSPACE				8
#define FUNC_KEYS					0
#define CONTROL_KEYS				224
#define KEY_LEFT					75
#define KEY_RIGHT					77
#define KEY_DELETE					83

wchar_t expr_str[SIZE];
wchar_t result[10];
int index = 0;
int position = 0;
int symbols = 0;
int error_pos = 0;
bool update_screen = true;

Polynom parse_addition();
Polynom parse_negative();

bool is_number(wchar_t ch) {
	return ch >= '0' and ch <= '9';
}

int parse_number() {
	int value = expr_str[index] - '0';
	if (is_number(expr_str[index]))
		++index;
	else {
		throw L"Ожидалось число";
	}
	while (index < SIZE and is_number(expr_str[index])) {
		value = value * 10 + expr_str[index] - '0';
		++index;
	}
	return value;
}

Polynom parse_value() {
	Polynom result;
	if (expr_str[index] == 'x') {
		++index;
		result.set_factor(1, 1);
	}
	else
		result.set_factor(0, parse_number());
	return result;
}


Polynom parse_parenthesis() {
	if (expr_str[index] == '(') {
		++index;
		Polynom value = parse_addition();
		if (expr_str[index] != ')') {
			throw L"Ожидалась закрывающая скобка";
		}
		++index;
		return value;
	}
	return parse_value();
}

Polynom parse_exponentiation() {
	Polynom value = parse_parenthesis();
	while (expr_str[index] == L'^') {
		int pow_index = index;
		++index;
		Polynom power = parse_negative();
		for (int i = 1; i < maxPow; i++)
			if (power.get_factor(i) != 0) {
				index = pow_index;
				throw L"Ожидалась степень с выражением, не содержащим «x»";
			}
		if (power.get_factor(0) > 0) {
			Polynom factor = value;
			for (int i = 1; i < power.get_factor(0); i++) {
				value *= factor;
			}
		}
		else if (power.get_factor(0) == 0) {
			for (int i = 1; i < maxPow; i++) {
				value.set_factor(i, 0);
			}
			value.set_factor(0, 1);
		}
		else {
			index = pow_index;
			throw L"Ожидалась степень с неотрицательным значением";
		}
	}
	return value;
}

Polynom parse_negative() {
	if (expr_str[index] == L'–') {
		index++;
		Polynom negative;
		negative.set_factor(0, -1);
		return negative * parse_exponentiation();
	}
	if (expr_str[index] == L'+' and index == 0)
		++index;
	return parse_exponentiation();
}

Polynom parse_multiplication() {
	Polynom value = parse_negative();
	while (expr_str[index] == L'·') {
		++index;
		value *= parse_negative();
	}
	return value;
}

Polynom parse_addition() {
	Polynom value = parse_multiplication();
	while (true) {
		if (expr_str[index] == '+') {
			++index;
			value += parse_multiplication();
		}
		else if (expr_str[index] == L'–') {
			++index;
			value -= parse_multiplication();
		}
		else
			break;
	}
	return value;
}

Polynom parse() {
	index = 0;
	Polynom value = parse_addition();
	if (index < symbols) {
		throw L"Unexpected symbol";
	}
	return value;
}

void print_in_superscript(int number) {
	if (number == 0)
		wprintf(L"⁰");
	else if (number == 1)
		wprintf(L"¹");
	else if (number == 2)
		wprintf(L"²");
	else if (number == 3)
		wprintf(L"³");
	else if (number >= 4 and number <= 9)
		wprintf(L"%c", number - 4 + L'⁴');
	else if (number >= 10) {
		print_in_superscript(number / 10);
		print_in_superscript(number % 10);
	}
}

int main()
{
	//(void)_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < SIZE; i++)
		expr_str[i] = L'\0';

	while (true) {
		if (update_screen) {
			system("cls");

			wprintf(L"Polynomal Simplification\n");
			wprintf(L"Enter expr_stression:\n");

			for (int i = 0; i < SIZE; i++)
				wprintf(L"%c", expr_str[i]);

			try {

				int ccc = 1;

				Polynom result = parse();
				bool printed = false;
				if (position < SIZE)
					wprintf(L"\n%*c", (position + 1), L'‾');
				else
					wprintf(L"\n");
				wprintf(L"\nРезультат: ");
				for (int i = maxPow; i >= 0; i--) {
					int a = result.get_factor(i);
					if (a == -1 and i > 0)
						wprintf(L"–");
					if (printed and a > 0)
						wprintf(L"+");
					if (a != 0) {
						if ((a != 1 and a != -1) or i == 0) {
							if (a > 0)
								wprintf(L"%d", a);
							if (a < 0)
								wprintf(L"–%d", -a);
						}
						if (i > 0)
							wprintf(L"x");
						if (i >= 2)
							print_in_superscript(i);
						printed = true;
					}
				}
				if (!printed)
					wprintf(L"0");
			}
			catch (const wchar_t* msg) {
				if (position < index)
					wprintf(L"%*c%*c\n", (position + 1), L'‾', (index - position), L'↑');
				else if (position > index)
					wprintf(L"%*c%*c\n", (index + 1), L'↑', (position - index), L'‾');
				else
					wprintf(L"%*c\n", (index + 1), L'˄');
				wprintf(L"%*s", (index + 1), msg);
			}
			wprintf(L"\n");
			update_screen = false;
		}
		/*
		* Управление
		*/
		int input = _getwch();
		if (input == L'ч')
			input = 'x';
		else if (input == ':')
			input = '^';
		else if (input == '*')
			input = L'·';
		else if (input == '-')
			input = L'–';

		if (input == FUNC_KEYS)
			(void)_getwch();
		else if (input == CONTROL_KEYS) {
			input = _getwch();
			if (input == KEY_LEFT and position > 0) {
				--position;
				update_screen = true;
			}
			else if (input == KEY_RIGHT and position < symbols) {
				++position;
				update_screen = true;
			}
			else if (input == KEY_DELETE and position < symbols) {
				for (int i = position; i < SIZE - 1; i++)
					expr_str[i] = expr_str[i + 1];
				expr_str[SIZE - 1] = '\0';
				--symbols;
				update_screen = true;
			}
		}
		else if (input == KEY_BACKSPACE and position > 0) {
			for (int i = position - 1; i < SIZE - 1; i++)
				expr_str[i] = expr_str[i + 1];
			expr_str[SIZE - 1] = '\0';
			--position;
			--symbols;
			update_screen = true;
		}
		else {
			if (symbols < SIZE and position < SIZE and (
				is_number(input)
				or input == 'x'
				or input == '+'
				or input == L'–'
				or input == L'·'
				or input == '^'
				or input == '('
				or input == ')')) {
				for (int i = SIZE - 1; i >= position; i--)
					expr_str[i] = expr_str[i - 1];
				expr_str[position] = input;
				++position;
				++symbols;
				update_screen = true;
			}
		}
	}
}
