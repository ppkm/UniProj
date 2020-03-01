#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

//Записывает в arr случайные значения.
void get_nums_arr(int length, int* arr);

//Выводит массив в консоль.
void print_nums_arr(int, int*);

//Собсна поиск наших сумм.
void find_sums(int, int, int*, int*);

//Подсчет биноминального коэффициента
int binomial_coefficient(int, int);

//Добавление 1 в наш "бинарный" массив
bool add_1_bin(int, int*);

//Подсчет единиц в "бинарном" массиве
int get_ones_count(int, int*);

//Смена местами двух элементов в массиве
void swap(int*, int*);

//Шейкерная сортировка
void shaker_sort(int*, int);

//Проверка на простоту
bool is_prime(int);

int main() {
    
	int* base_arr;
	int* sum_arr;
	int length = 0;
	int k = 0;

	while (length < 1 or length > 30) {
		cout << "Enter length of base sequence(1-30): ";
		cin >> length;
		cout << endl;
	}

	while (k < 1 or k > length) {
		cout << "Enter K (1-" << length << "): ";
		cin >> k;
		cout << endl;
	}

	base_arr = new int[length];
	sum_arr  = new int[binomial_coefficient(length, k)];

	get_nums_arr(length, base_arr);
	print_nums_arr(length, base_arr);
	find_sums(length, k, base_arr, sum_arr);

	system("pause");
}

void get_nums_arr(int length, int* arr) {

	//INPUT: длина массива и сам массив.

	//Задаем сид для рандома(это нужно для того,
	//чтобы рандом был завязан на времени системы),
	//иначе каждый раз будут одинаковые числа.
	srand(time(NULL));
	
	//Записываем случайные числа от 1 до 100.
	for (int i = 0; i < length; i++)
		arr[i] = rand() % 100 + 1;
}

void print_nums_arr(int length, int* arr) {

	//INPUT: длина массива и сам массив.

	for (int i = 0; i < length; i++)
		cout << arr[i] << " ";

	cout << endl;
}

void find_sums(int length, int k, int* base_arr, int* sum_arr) {

	//INPUT: длина исходного массива,
	//       размер интересующей подпоследовательности
	//       исходная последовательность
	//       массив с суммами

	//Кол-во возможный сумм равно биномиальному коэфициенты из (length) по (k)
	//Гугл в помощь, но это простая комбинаторика
	int sum_len = binomial_coefficient(length, k);

	//Массив такой же длины как и входная последовательность.
	//Заполнен нулями. Нужно для перебора.
	int* bin_arr = new int[length];
	for (int i = 0; i < length; i++)
		bin_arr[i] = 0;

	//Номер текущей комбинации
	int comb_num = 0;

	cout << "Found combinations: \n\n";

	//Читай (Сноска 1) в конце файла.
	do {
		
		//Проверка на размер комбинации
		if (get_ones_count(length, bin_arr) != k)
			continue;

		comb_num++;

		//Текущая сумма
		int curr_sum = 0;

		cout << "Combination #" << comb_num << ": (";
		//Проходимся по массиву bin_arr и если элемент равен 1, то заносим соответсвующий
		//элемент из base_arr в нашу сумму.
		for (int i = 0; i < length; i++)
			if (bin_arr[i] == 1) {
				cout << " " << base_arr[i] << ",";
				curr_sum += base_arr[i];
			}

		cout << "); Sum = " << curr_sum << "\n";
		//Добавляем текущую сумму в общий массив сумм.
		sum_arr[comb_num - 1] = curr_sum;

	} while (add_1_bin(length, bin_arr));

	cout << "\n\nSum array: \n";
	print_nums_arr(sum_len, sum_arr);

	//Шейкерная сортировка(мне лень это объяснять)
	//Это хуйня вроде пузырьковой сортировки, но улучшенная
	//Обязательно посмотри видосы и разберись с ней
	//Препод может спросить
	shaker_sort(sum_arr, sum_len);
	cout << "\nSorted sum array: \n";
	print_nums_arr(sum_len, sum_arr);

	bool flag = false;
	//Поиск максимального натурального числа
	for (int i = sum_len - 1; i >= 0; i--) {
		if (is_prime(sum_arr[i])) {
			cout << "Largest prime sum is: " << sum_arr[i] << endl;
			flag = true;
			break;
		}
	}

	if (!flag)
		cout << "None of the sum elements is a prime number.\n";

	cout << endl;
}

int binomial_coefficient(int n, int k) {

	//INPUT: размер изначальной последовательности
	//       размер интересующей подпоследовательности

	//Опять же почитай википедию, тут нет ничего сложного
	//https://en.wikipedia.org/wiki/Binomial_coefficient

	int res = 1;

	// Поскольку C(n, k) = C(n, n-k)  
	if (k > n - k)
		k = n - k;

	// Подсчитываем значения  
	// [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]  
	for (int i = 0; i < k; ++i)
	{
		res *= (n - i);
		res /= (i + 1);
	}

	return res;
}

bool add_1_bin(int length, int* arr) {

	//INPUT: длина исходной последовательности
	//       исходная последовательность

	//Это простой алгоритм сложения двоичного числа с 1.
	//Попробуй поэтапно пройтись по нему ручками на листке и все поймешь.

	bool check = false;
	//Проверка на то, являются ли все элементы в массиве уже 1
	//Типо {1, 1, 1, 1} - тогда нет смысла больше добавлять 1цы.
	for (int i = 0; i < length; i++) {
		if (arr[i] == 0) {
			check = true;
			break;
		}
	}
	
	if (!check)
		return false;

	for (int i = length - 1; i >= 0; i--) {
		if (arr[i] == 0) {
			arr[i] = 1;
			break;
		} else {
			arr[i] = 0;
		}
	}

	return true;
}

int get_ones_count(int length, int* bin_arr) {

	//INPUT: размер бинарной последовательности
	//       бинарная последовательность

	int n = 0;
	for (int i = 0; i < length; i++)
		if (bin_arr[i] == 1)
			n++;

	return n;
}

void swap(int* a, int* b) {

	//INPUT: два указателя на элементы массива, которые нужно поменять местами.

	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void shaker_sort(int* a, int len) {

	//INPUT: массив
	//       длина массива

	//Долго расписывать как она работает. Ничего сложного в принципе.
	//https://en.wikipedia.org/wiki/Cocktail_shaker_sort

	int i, j, k;
	for (i = 0; i < len; i++) {

		for (j = i + 1; j < len; j++) {

			if (a[j] < a[j - 1])
				swap(&a[j], &a[j - 1]);

		}

		len--;

		for (k = len - 1; k > i; k--) {

			if (a[k] < a[k - 1])
				swap(&a[k], &a[k - 1]);

		}
	}
}

bool is_prime(int n) {

	//INPUT: число на проверку

	//По сути мы проходимся по каждому числу от 2(минимальное простое число) до n/2
	//И смотрим делится эта шняга или нет
	//Если делится тогда число не простое
	//Иначе простое

	bool flag = false;
	int m = n / 2;
	for (int i = 2; i <= m; i++)
	{
		if (n % i == 0)
		{
			flag = 1;
			return false;
		}
	}
	if (flag == 0)
		return true;
}



/*Сноска 1:
	Перебор работает следующим образом:
	У нас изначальная последовательность. 
	arr = {1, 2, 3, 4}

	Мы создаем массив такой же длины, что и входная последовательность
	и заполняем ее нулями.
	bin_arr = {0, 0, 0, 0}

	Далее мы работаем с bin_arr как с числом в 2чной системе.
	И через функцию add_1_bin() "побитово" увеличиваем на 1.
	т.е.
	0, 0, 0, 0
	0, 0, 0, 1
	0, 0, 1, 0
	0, 0, 1, 1
	..........
	1, 1, 1, 1

	Далее при каждей итерации цикла мы проверяем, чтобы кол-во 1
	в массиве bin_arr было равно k
	Это будет значит, что это комбинация из k элементов(что нам и нужно)
	пример:
	bin_arr = {1, 0, 1, 0}
	тогда мы будем рассматривать комбинацию [1, 3] и сумма будет равна соответственно 4
*/