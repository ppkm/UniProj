#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

//���������� � arr ��������� ��������.
void get_nums_arr(int length, int* arr);

//������� ������ � �������.
void print_nums_arr(int, int*);

//������ ����� ����� ����.
void find_sums(int, int, int*, int*);

//������� �������������� ������������
int binomial_coefficient(int, int);

//���������� 1 � ��� "��������" ������
bool add_1_bin(int, int*);

//������� ������ � "��������" �������
int get_ones_count(int, int*);

//����� ������� ���� ��������� � �������
void swap(int*, int*);

//��������� ����������
void shaker_sort(int*, int);

//�������� �� ��������
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

	//INPUT: ����� ������� � ��� ������.

	//������ ��� ��� �������(��� ����� ��� ����,
	//����� ������ ��� ������� �� ������� �������),
	//����� ������ ��� ����� ���������� �����.
	srand(time(NULL));
	
	//���������� ��������� ����� �� 1 �� 100.
	for (int i = 0; i < length; i++)
		arr[i] = rand() % 100 + 1;
}

void print_nums_arr(int length, int* arr) {

	//INPUT: ����� ������� � ��� ������.

	for (int i = 0; i < length; i++)
		cout << arr[i] << " ";

	cout << endl;
}

void find_sums(int length, int k, int* base_arr, int* sum_arr) {

	//INPUT: ����� ��������� �������,
	//       ������ ������������ ���������������������
	//       �������� ������������������
	//       ������ � �������

	//���-�� ��������� ���� ����� ������������� ����������� �� (length) �� (k)
	//���� � ������, �� ��� ������� �������������
	int sum_len = binomial_coefficient(length, k);

	//������ ����� �� ����� ��� � ������� ������������������.
	//�������� ������. ����� ��� ��������.
	int* bin_arr = new int[length];
	for (int i = 0; i < length; i++)
		bin_arr[i] = 0;

	//����� ������� ����������
	int comb_num = 0;

	cout << "Found combinations: \n\n";

	//����� (������ 1) � ����� �����.
	do {
		
		//�������� �� ������ ����������
		if (get_ones_count(length, bin_arr) != k)
			continue;

		comb_num++;

		//������� �����
		int curr_sum = 0;

		cout << "Combination #" << comb_num << ": (";
		//���������� �� ������� bin_arr � ���� ������� ����� 1, �� ������� ��������������
		//������� �� base_arr � ���� �����.
		for (int i = 0; i < length; i++)
			if (bin_arr[i] == 1) {
				cout << " " << base_arr[i] << ",";
				curr_sum += base_arr[i];
			}

		cout << "); Sum = " << curr_sum << "\n";
		//��������� ������� ����� � ����� ������ ����.
		sum_arr[comb_num - 1] = curr_sum;

	} while (add_1_bin(length, bin_arr));

	cout << "\n\nSum array: \n";
	print_nums_arr(sum_len, sum_arr);

	//��������� ����������(��� ���� ��� ���������)
	//��� ����� ����� ����������� ����������, �� ����������
	//����������� �������� ������ � ��������� � ���
	//������ ����� ��������
	shaker_sort(sum_arr, sum_len);
	cout << "\nSorted sum array: \n";
	print_nums_arr(sum_len, sum_arr);

	bool flag = false;
	//����� ������������� ������������ �����
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

	//INPUT: ������ ����������� ������������������
	//       ������ ������������ ���������������������

	//����� �� ������� ���������, ��� ��� ������ ��������
	//https://en.wikipedia.org/wiki/Binomial_coefficient

	int res = 1;

	// ��������� C(n, k) = C(n, n-k)  
	if (k > n - k)
		k = n - k;

	// ������������ ��������  
	// [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]  
	for (int i = 0; i < k; ++i)
	{
		res *= (n - i);
		res /= (i + 1);
	}

	return res;
}

bool add_1_bin(int length, int* arr) {

	//INPUT: ����� �������� ������������������
	//       �������� ������������������

	//��� ������� �������� �������� ��������� ����� � 1.
	//�������� �������� �������� �� ���� ������� �� ������ � ��� �������.

	bool check = false;
	//�������� �� ��, �������� �� ��� �������� � ������� ��� 1
	//���� {1, 1, 1, 1} - ����� ��� ������ ������ ��������� 1��.
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

	//INPUT: ������ �������� ������������������
	//       �������� ������������������

	int n = 0;
	for (int i = 0; i < length; i++)
		if (bin_arr[i] == 1)
			n++;

	return n;
}

void swap(int* a, int* b) {

	//INPUT: ��� ��������� �� �������� �������, ������� ����� �������� �������.

	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void shaker_sort(int* a, int len) {

	//INPUT: ������
	//       ����� �������

	//����� ����������� ��� ��� ��������. ������ �������� � ��������.
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

	//INPUT: ����� �� ��������

	//�� ���� �� ���������� �� ������� ����� �� 2(����������� ������� �����) �� n/2
	//� ������� ������� ��� ����� ��� ���
	//���� ������� ����� ����� �� �������
	//����� �������

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



/*������ 1:
	������� �������� ��������� �������:
	� ��� ����������� ������������������. 
	arr = {1, 2, 3, 4}

	�� ������� ������ ����� �� �����, ��� � ������� ������������������
	� ��������� �� ������.
	bin_arr = {0, 0, 0, 0}

	����� �� �������� � bin_arr ��� � ������ � 2���� �������.
	� ����� ������� add_1_bin() "��������" ����������� �� 1.
	�.�.
	0, 0, 0, 0
	0, 0, 0, 1
	0, 0, 1, 0
	0, 0, 1, 1
	..........
	1, 1, 1, 1

	����� ��� ������ �������� ����� �� ���������, ����� ���-�� 1
	� ������� bin_arr ���� ����� k
	��� ����� ������, ��� ��� ���������� �� k ���������(��� ��� � �����)
	������:
	bin_arr = {1, 0, 1, 0}
	����� �� ����� ������������� ���������� [1, 3] � ����� ����� ����� �������������� 4
*/