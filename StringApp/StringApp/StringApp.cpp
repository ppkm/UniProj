#include <iostream>
#include <conio.h>
using namespace std;

//Вывод
//Копирование
//Склеивание
//Сравнение
//Длина

void inputString(char* str);
void copyString(char* dest_str, char* source_str);
void printString(char* str);
void stringCat(char* dest_str, char* source_str);
int compareStrings(char* str1, char* str2);
int strLen(char* str);

void main() {

	char str1[81];
	char str2[81];

	while (true) {

		system("cls");
		inputString(str1);
		inputString(str2);
		system("cls");

		printf("\n String 1 = ");
		printString(str1);
		printf("\n Length of string 1 = %d", strLen(str1));

		printf("\n\n String 2 = ");
		printString(str2);
		printf("\n Length of string 2 = %d", strLen(str2));

		printf("\n\n Comparison of strings = %d", compareStrings(str1, str2));

		stringCat(str1, str2);
		printf("\n\n String 1 += String 2 = ");
		printString(str1);
	
		copyString(str2, str1);
		printf("\n\n Copy of string 1 = ");
		printString(str2);
		cout << endl;

		system("pause");
	}
}


void inputString(char* str) {

	char buffer[200];

	do {
		printf("Print string(1-40 symbols): ");
		cin >> buffer;

		if (strLen(buffer) <= 40) {
			copyString(str, buffer);
			return;
		} else {
			printf("String is too large. Try again. \n");
		}
	} while (true);
}

int strLen(char* str) {
	
	int n = 0;
	while (str[n] != '\0')
		n++;
	
	return n;
}

void copyString(char* dest_str, char* source_str) {

	for (int i = 0; i < strLen(source_str); i++) {
		dest_str[i] = source_str[i];
	}
	dest_str[strLen(source_str)] = 0;
}

void printString(char* str) {
	for (int i = 0; i < strLen(str); i++)
		cout << str[i];
}

void stringCat(char* dest_str, char* source_str) {

	int destL = strLen(dest_str);
	for (int i = 0; i < strLen(source_str); i++)
		dest_str[destL + i] = source_str[i];
	dest_str[destL + strLen(source_str)] = 0;
}

//1  - str1 < str2
//-1 - str1 > str2
//0  - equal
int compareStrings(char* str1, char* str2) {

	int result = 0;

	int L1 = strLen(str1);
	int L2 = strLen(str2);

	if (L1 > L2) {
		return -1;
	} else if (L1 < L2) {
		return 1;
	}
	
	int sum1 = 0;
	int sum2 = 0;

	for (int i = 0; i < L1; i++) {
		sum1 += str1[i];
		sum2 += str2[i];
	}

	if (sum1 > sum2) {
		return -1;
	}
	else if (sum1 < sum2) {
		return 1;
	} else {

		for (int i = 0; i < L1; i++) {
			if (str1[i] > str2[i])
				return -1;
			else if (str1[i] < str2[i])
				return 1;
		}

		return 0;
	}
}