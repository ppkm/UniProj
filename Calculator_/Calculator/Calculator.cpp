#include <iostream>
#include <cmath>
#include <conio.h>
using namespace std;

#define ARROW_UP   72
#define ARROW_DOWN 80
#define ENTER_KEY  13
#define ESC_KEY    27

//1600

//INPUT-OUTPUT-MENU CONTROL//
//Clears screen and prints menu
void printMenu(int base, char* num1, char* num2, int arrowLevel);
//Prints number from a char array
void printNum(char* num);
//Prints number from an int array
void printNum(int* num, int numL);
//Number input
void inputNum(int base, char* num);
//Base input
int inputBase();

//BASE FUNCTIONS///////////////////////////////////////////////////////

//num1 + num2, prints result
void sumNums(int base, char* num1, char* num2, int num1L, int num2L, bool returnValue, char* returnResult = new char[300]);
//num1 - num2, prints result
void subNums(int base, char* num1, char* num2, int num1L, int num2L, bool returnValue, char* returnResult = new char[300]);
//num1 * num2, prints result
void multyNums(int base, char* num1, char* num2, int num1L, int num2L, bool returnValue, char* returnResult = new char[300]);
//changes 'result' var to (num1^power)
void powTo(char* num1, int power, int num1L, char* endResult);
//num1 / num2, prints result
void divNums(int base, char* num1, char* num2, bool returnValue, char* returnResult = new char[300]);
//Changes digit depending on base and increase value (1-increase, 0;decrease)
void changeDigit(int base, char* num1, int index, bool increase);
//Converts number(char array) to decimal number(char array)
void convertToDex(int base, char* num, char* dexNum);
//Converts number to another base system
void convertToBase(int base, char* num1, char* num2);
//Starts 'change number' menu
void changeNum(int base, char* num1, char* num2, int arrowLevel);
//Converts number from 10 base to new base
void convertDexToBase(int base, char* _dexNum, char* baseNum);
//Returns n%base as char
char divideMod(int base, int n);
//num1%num2 -> leftOver
void modDivNums(int base, char* num1, char* num2, char* leftOver);

///////////////////////////////////////////////////////////////////////

//CHAR ARRAYS//////////////////////////////////////////////////////////
//Converts number(n) to char array (num)
void convertToCharArr(int n, char* num);
//Returns decimal value of char(ex. A -> 10, F -> 15)
int charToInt(char c);
char intToChar(int n);
//Returns length of char array, as if it were a number
int getNumLength(char* num, int size = 300);
//Connects two char arrays together. '123' + '42' -> '12342'
void sumCharArrs(char* num1, char* num2);
//Connects two char arrays and returns value to newCharArray
void sumCharArrs(char* num1, char* num2, char* newCharArray);
int convertCharArrToInt(char* num);

//Returns whether num1 > num2
bool isBigger(char* num1, char* num2, int num1L, int num2L);
//Returns whether num1 >= num2
bool isBiggerOrEqual(char* num1, char* num2, int num1L, int num2L);

//Corrects numbers: removes extra 0s at the start.
void correctNumber(char* num);
void correctNumber300(char* num);
void setToZero(char* num, int len);
void setToZero(int* num, int len);
void copyArrs(char* arr1, char* arr2, int lenOfArr1);
///////////////////////////////////////////////////////////////////////

int main() {
	//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF - 50 Fs
	//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ - 50 Zs

	int base = inputBase();
	char num1[300];
	char num2[300];
	int num1Len, num2Len;

	//Input (num1 & num2)
	inputNum(base, num1);
	inputNum(base, num2);

	correctNumber(num1);
	num1Len = getNumLength(num1);
	correctNumber(num2);
	num2Len = getNumLength(num2);

	//MENU CONTROLLS
	int arrowLevel = 1;
	bool escPressed = false;

	do {
		system("cls");
		printMenu(base, num1, num2, arrowLevel);
		
		char L = _getch();
		if (L == 224)
			L = _getch();

		switch (L)
		{
		case ARROW_UP:
			if (arrowLevel != 1)
				arrowLevel--;
			break;
		case ARROW_DOWN:
			if (arrowLevel != 6)
				arrowLevel++;
			break;

		case ENTER_KEY:
			switch (arrowLevel) {
				case 1://Addition
					sumNums(base, num1, num2, num1Len, num2Len, false);
					system("pause");
					break;
				case 2://Substraction
					subNums(base, num1, num2, num1Len, num2Len, false);
					system("pause");
					break;
				case 3://Multiplication
					multyNums(base, num1, num2, num1Len, num2Len, false);
					system("pause");
					break;
				case 4://Division
					divNums(base, num1, num2, false);
					system("pause");
					break;
				case 5://Base change
					convertToBase(base, num1, num2);
					system("pause");
					break;
				case 6://Number change
					changeNum(base, num1, num2, arrowLevel);
					break;
			}
			break;
		case ESC_KEY:
			escPressed = true;
			break;
		}
	} while (!escPressed);
}

void printMenu(int base, char* num1, char* num2, int arrowLevel) {

	printf("%s %d \n", "Base = ", base);
	printf("Number1 = ");
	printNum(num1);
	printf("Number2 = ");
	printNum(num2);
	cout << endl;

	cout << ">" << ((arrowLevel == 1) ? ("Addition        <===") : ("Addition")) << endl;
	cout << ">" << ((arrowLevel == 2) ? ("Subtraction     <===") : ("Subtraction")) << endl;
	cout << ">" << ((arrowLevel == 3) ? ("Multiplication  <===") : ("Multiplication")) << endl;
	cout << ">" << ((arrowLevel == 4) ? ("Division        <===") : ("Division")) << endl;
	cout << ">" << ((arrowLevel == 5) ? ("Base change     <===") : ("Base change")) << endl;
	cout << ">" << ((arrowLevel == 6) ? ("Number 1 change <===") : ("Number 1 change")) << endl;

	cout << endl << endl;
}

void printNum(char* num) {

	for (int i = 0; i < getNumLength(num); i++) {
		char currC = num[i];
		cout << currC;
	}
	cout << endl;
}

void printNum(int* num, int numL) {

	bool numStarted = false;

	for (int i = numL; i >= 0; i--) {

		if (numStarted) {
			cout << num[i];
		}
		else if (num[i] != 0) {
			numStarted = true;
			cout << num[i];
		}
	}

	if (!numStarted)
		cout << "0";

	cout << endl;
}

void inputNum(int base, char* num) {

	bool numR = false;
	char input[50];
	char buffer[200];

	setToZero(num, 50);

	do {
		numR = true;
		printf("Enter a number(1-50 digits) > ");
		cin >> buffer;

		if (strlen(buffer) <= 50) {
			copyArrs(input, buffer, 50);

			for (int i = 0; i < 50; i++) {
				char currC = input[i];

				if (currC == 0)
					break;

				if (base >= 2 and base <= 10) {

					if (currC >= '0' and currC < '0' + base) {
						num[i] = currC;
					}
					else {
						numR = false;
						break;
					}
				}
				else if (base >= 11 and base <= 36) {

					if ((currC >= '0' and currC <= '9') || (currC >= 'A' and currC < 'A' + base - 10)) {
						num[i] = currC;
					}
					else {
						numR = false;
						break;
					}
				}
			}

			if (!numR) {
				printf("Number contains unexpected symbols. Try again. \n");
			}
		}
		else {
			numR = false;
			printf("Number is too large. Try again. \n");
		}
	} while (!numR);
}

int inputBase() {

	int result;
	int len;
	bool numR = false;
	char buffer[200];
	char base[2];

	do {

		numR = false;
		printf("Enter base(2-36) > ");
		cin >> buffer;

		setToZero(base, 2);
		len = 0;
		result = 0;

		if (strlen(buffer) <= 2) {
			for (int i = 0; i < 2; i++) {

				char currC = buffer[i];

				if (currC == 0)
					break;

				if (currC >= '0' and currC <= '9') {
						base[i] = currC;
						len++;
						numR = true;
				} else {
					numR = false;
					break;
				}
			}
		}

		result = (len == 1) ? charToInt(base[0]) : charToInt(base[0]) * 10 + charToInt(base[1]);

		if (result < 2 or result > 36)
			numR = false;
		else
			return result;
	} while (!numR);
}



void sumNums(int base, char* num1, char* num2, int num1L, int num2L, bool returnValue, char* returnResult) {

	int result[300];
	char dexNum1[300];
	char dexNum2[300];

	convertToDex(base, num1, dexNum1);
	convertToDex(base, num2, dexNum2);

	int dexNum1L = getNumLength(dexNum1);
	int dexNum2L = getNumLength(dexNum2);
	int endIndex = (dexNum1L >= dexNum2L) ? dexNum1L : dexNum2L;

	setToZero(result, 300);

	int resL = 0;
	int maxres = 0;
	for (int i = 1; i <= endIndex; i++) {

		int num1AtIndex = (dexNum1L - i >= 0) ? charToInt(dexNum1[dexNum1L - i]) : 0;
		int num2AtIndex = (dexNum2L - i >= 0) ? charToInt(dexNum2[dexNum2L - i]) : 0;
		int currIndexSum = num1AtIndex + num2AtIndex + result[resL];

		if (currIndexSum > 9) {
			result[resL + 1] += currIndexSum / 10;
			maxres = resL + 2;
		}

		result[resL] = currIndexSum % 10;
		resL++;
		if (resL > maxres)
			maxres = resL;
	}

	for (int i = 0; i < maxres; i++)
		returnResult[i] = intToChar(result[maxres - i - 1]);
	returnResult[maxres] = 0;
	correctNumber300(returnResult);

	if (returnValue)
		return;

	char baseResult[300];
	convertDexToBase(base, returnResult, baseResult);

	printf("Result in base(10) = ");
	printNum(returnResult);
	printf("Result in base(%d) = ", base);
	printNum(baseResult);
}

void subNums(int base, char* num1, char* num2, int num1L, int num2L, bool returnValue, char* returnResult) {

	int result[300];
	setToZero(result, 300);
	char dexNum1[300];
	char dexNum2[300];

	convertToDex(base, num1, dexNum1);
	convertToDex(base, num2, dexNum2);

	int dexNum1L = getNumLength(dexNum1);
	int dexNum2L = getNumLength(dexNum2);
	int endIndex = dexNum1L;

	if (isBigger(dexNum2, dexNum1, dexNum2L, dexNum1L)) {
		printf("Result is negative. \n");
		return;
	}

	int resL = 0;
	int index = 0;
	for (int i = 1; i <= endIndex; i++) {

		int num1AtIndex = (dexNum1L - i >= 0) ? charToInt(dexNum1[dexNum1L - i]) : 0;
		int num2AtIndex = (dexNum2L - i >= 0) ? charToInt(dexNum2[dexNum2L - i]) : 0;
		int currIndexSum = num1AtIndex + result[index] - num2AtIndex;

		if (currIndexSum < 0) {
			result[index + 1] -= 1;
			currIndexSum += 10;
			resL = index + 1;
		}

		result[index] = currIndexSum;

		index++;
		resL = (index > resL) ? index : resL;
	}

	for (int i = 0; i < resL; i++)
		returnResult[i] = intToChar(result[resL - i - 1]);
	returnResult[resL] = 0;
	correctNumber300(returnResult);

	if (returnValue)
		return;

	char baseResult[300];
	convertDexToBase(base, returnResult, baseResult);

	printf("Result in base(10) = ");
	printNum(returnResult);
	printf("Result in base(%d) = ", base);
	printNum(baseResult);
}

void multyNums(int base, char* num1, char* num2, int num1L, int num2L, bool returnValue, char* returnResult) {


	if ((num2L == 1 and num2[0] == '0') or (num1L == 1 and num1[0] == '0')) {
		if (!returnValue)
			(base == 10) ? printf("Result in base(10) = 0 \n") : printf("Result in base(10) and in base(%d) = 0", base);

		returnResult[0] = '0';
		returnResult[1] = 0;
		return;
	}

	char dexNum1[300];
	char dexNum2[300];
	convertToDex(base, num1, dexNum1);
	convertToDex(base, num2, dexNum2);
	int dexNum1L = getNumLength(dexNum1);
	int dexNum2L = getNumLength(dexNum2);
	int indexNum1 = 0;
	int indexNum2 = 0;
	int resL = 0;

	char result[300];
	setToZero(result, 300);

	for (int i = dexNum1L - 1; i >= 0; i--) {

		int carry = 0;
		int n1 = charToInt(dexNum1[i]);
		indexNum2 = 0;

		for (int j = dexNum2L - 1; j >= 0; j--) {

			int n2 = charToInt(dexNum2[j]);
			int sum = n1 * n2 + result[indexNum1 + indexNum2] + carry;
			carry = sum / 10;
			result[indexNum1 + indexNum2] = sum % 10;
			resL = indexNum1 + indexNum2;
			indexNum2++;
		}

		if (carry > 0) {
			result[indexNum1 + indexNum2] += carry;
			resL = indexNum1 + indexNum2;
		}

		indexNum1++;
	}

	resL++;

	for (int i = 0; i < resL; i++)
		returnResult[i] = result[resL - i - 1] + 48;
	returnResult[resL] = 0;
	correctNumber300(returnResult);

	if (returnValue)
		return;

	char baseResult[300];
	convertDexToBase(base, returnResult, baseResult);

	printf("Result in base(10) = ");
	printNum(returnResult);
	printf("Result in base(%d) = ", base);
	printNum(baseResult);
}

void powTo(char* base, int power, int baseL, char* endResult) {

	int result[300];
	int deltaResult[300];
	char num1[300];
	copyArrs(num1, base, 300);
	int num1L = baseL;

	setToZero(result,      300);
	setToZero(deltaResult, 300);
	for (int i = 0; i < 300; i++) {
		result[i] = 0;
		deltaResult[i] = 0;
	}

	int indexNum1 = 0;
	int indexNum2 = 0;

	if (power == 0) {
		endResult[0] = '1';
		endResult[1] = 0;
		return;
	} else if (power == 1) {
		endResult[0] = num1[0];
		endResult[1] = num1[1];
		endResult[2] = 0;
		return;
	}

	int resL = 0;
	for (int p = 0; p < power - 1; p++) {

		indexNum1 = 0;
		indexNum2 = 0;
		resL = 0;
		setToZero(deltaResult, 300);

		for (int i = num1L - 1; i >= 0; i--) {

			int carry = 0;
			int n1 = charToInt(num1[i]);
			indexNum2 = 0;

			for (int j = baseL - 1; j >= 0; j--) {
				int n2 = charToInt(base[j]);
				int sum = n1 * n2 + deltaResult[indexNum1 + indexNum2] + carry;
				carry = sum / 10;
				deltaResult[indexNum1 + indexNum2] = sum % 10;
				resL = indexNum1 + indexNum2;
				indexNum2++;
			}

			if (carry > 0) {
				deltaResult[indexNum1 + indexNum2] += carry;
				resL = indexNum1 + indexNum2;
			}
			indexNum1++;
		}

		for (int i = 0; i < resL + 1; i++)
			num1[i] = intToChar(deltaResult[resL - i]);

		num1L = getNumLength(num1);
	}

	for (int i = 0; i < resL + 1; i++)
		endResult[i] = intToChar(deltaResult[resL - i]);
	endResult[resL + 1] = 0;
	correctNumber300(endResult);
}

void divNums(int base, char* num1, char* num2, bool returnValue, char* returnResult) {

	char dexNum1[300];
	char dexNum2[300];
	char result[300];
	char deltaResult[300];
	char currDiv[300];
	int indexDiv = 0;
	int currDivIndex = 0;

	setToZero(result, 300);
	convertToDex(base, num1, dexNum1);
	convertToDex(base, num2, dexNum2);
	int dexNum1L = getNumLength(dexNum1);
	int dexNum2L = getNumLength(dexNum2);

	if (dexNum2[0] == '0' and dexNum2L == 1) {
		printf("Cannot divide by zero. \n");
		return;
	} else if (dexNum1[0] == '0' and dexNum1L == 1) {
		(base == 10) ? printf("Result in base(10) = 0 \n") : printf("Result in base(10) and base(%d) = 0 \n", base);
		return;
	} else if (dexNum2[0] == '1' and dexNum2L == 1) {
		printf("Result in base(10) = ");
		printNum(dexNum1);
		printf("Result in base(%d) = ", base);
		printNum(num1);
		return;
	} else if (isBigger(dexNum2, dexNum1, getNumLength(dexNum2), getNumLength(dexNum1))) {
		if (returnValue) {
			returnResult[0] = '0';
			returnResult[1] = 0;
		}
		else {
			printf("Result in base(10) = 0\n Result in base(%d) = 0 \n", base);
		}
		return;
	}

	char oneArr[300];
	char zeroArr[300];
	convertToCharArr(1, oneArr);
	convertToCharArr(0, zeroArr);

	bool tookDigit = false;

	while (indexDiv != getNumLength(dexNum1)) {

		tookDigit = false;

		while (isBigger(dexNum2, currDiv, getNumLength(dexNum2), getNumLength(currDiv)) and indexDiv <= getNumLength(dexNum1)) {

			currDiv[currDivIndex] = dexNum1[indexDiv];
			indexDiv++;

			if (tookDigit and result[0] != 0) {
				sumCharArrs(result, zeroArr);
			}

			tookDigit = true;
			correctNumber300(currDiv);
			currDivIndex = getNumLength(currDiv);
		}

		if (indexDiv > getNumLength(dexNum1))
			break;

		setToZero(deltaResult, 300);

		while (isBiggerOrEqual(currDiv, dexNum2, getNumLength(currDiv), getNumLength(dexNum2))) {

			subNums(10, currDiv, dexNum2, getNumLength(currDiv), getNumLength(dexNum2), true, currDiv);
			sumNums(10, deltaResult, oneArr, getNumLength(deltaResult), 1, true, deltaResult);
		}

		currDivIndex = getNumLength(currDiv);
		sumCharArrs(result, deltaResult);
	}

	int resL = getNumLength(result);
	for (int i = 0; i < resL; i++)
		returnResult[i] = result[i];
	returnResult[resL] = 0;
	correctNumber300(returnResult);

	if (returnValue)
		return;

	char baseResult[300];
	convertDexToBase(base, returnResult, baseResult);

	printf("Result in base(10) = ");
	printNum(result);
	printf("Result in base(%d) = ", base);
	printNum(baseResult);
}

void modDivNums(int base, char* num1, char* num2, char* leftOver) {
	char dexNum1[300];
	char dexNum2[300];
	char deltaResult[300];
	char result[300];
	char currDiv[300];
	int indexDiv = 0;
	int currDivIndex = 0;

	convertToDex(base, num1, dexNum1);
	convertToDex(base, num2, dexNum2);
	int dexNum1L = getNumLength(dexNum1);
	int dexNum2L = getNumLength(dexNum2);
	setToZero(result, 300);

	if (dexNum2[0] == '0' and dexNum2L == 1) {
		printf("Cannot divide by zero. \n");
		return;
	} else if (dexNum1[0] == '0' and dexNum1L == 1) {
		convertToCharArr(0, leftOver);
		return;
	} else if (dexNum2[0] == '1' and dexNum2L == 1) {
		copyArrs(leftOver, num1, 300);
		return;
	} else if (isBigger(dexNum2, dexNum1, getNumLength(dexNum2), getNumLength(dexNum1))) {
		copyArrs(leftOver, num1, 300);
		return;
	}

	char oneArr[300];
	char zeroArr[300];
	convertToCharArr(1, oneArr);
	convertToCharArr(0, zeroArr);
	setToZero(currDiv, 300);


	bool tookDigit = false;

	while (indexDiv != getNumLength(dexNum1)) {

		tookDigit = false;

		while (isBigger(dexNum2, currDiv, getNumLength(dexNum2), getNumLength(currDiv)) && indexDiv <= getNumLength(dexNum1)) {

			currDiv[currDivIndex] = dexNum1[indexDiv];
			indexDiv++;

			if (tookDigit && result[0] != 0)
				sumCharArrs(result, zeroArr);

			tookDigit = true;
			correctNumber300(currDiv);
			currDivIndex = getNumLength(currDiv);
		}

		if (indexDiv > getNumLength(dexNum1))
			break;

		for (int i = 0; i < 300; i++)
			deltaResult[i] = 0;

		while (isBiggerOrEqual(currDiv, dexNum2, getNumLength(currDiv), getNumLength(dexNum2))) {
			subNums(10, currDiv, dexNum2, getNumLength(currDiv), getNumLength(dexNum2), true, currDiv);
			sumNums(10, deltaResult, oneArr, getNumLength(deltaResult), 1, true, deltaResult);
		}

		currDivIndex = getNumLength(currDiv);

		sumCharArrs(result, deltaResult);
	}

	for (int i = 0; i < 300; i++)
		leftOver[i] = currDiv[i];
}

void changeDigit(int base, char* num, int index, bool increase) {

	if (increase) {
		if (base >= 2 and base <= 10) {

			if (num[index] == '0' + base - 1)
				num[index] = '0';
			else
				num[index] += 1;
		}
		else if (base >= 11 and base <= 36) {

			if (num[index] == '9') {
				num[index] = 'A';
			}
			else if (num[index] == 'A' + base - 11) {
				num[index] = '0';
			}
			else {
				num[index] += 1;
			}
		}
	} else {
		if (base >= 2 && base <= 10) {

			if (num[index] == '0')
				num[index] = '0' + base - 1;
			else
				num[index] -= 1;
		}
		else if (base >= 11 && base <= 36) {

			if (num[index] == 48) {
				num[index] = 'A' + base - 11;
			}
			else if (num[index] == 65) {
				num[index] = '9';
			}
			else {
				num[index] -= 1;
			}
		}
	}
}

void convertToDex(int base, char* num, char* dexNum) {

	if (base == 10) {

		int deltaDexNumL = getNumLength(num) - 1;

		for (int i = 0; i <= deltaDexNumL; i++) {

			if (num[i] == -52)
				break;

			dexNum[i] = num[i];
		}

		return;
	}

	char deltaDexNum[300];

	for (int i = 0; i < 300; i++) {

		deltaDexNum[i] = 0;
		dexNum[i] = 0;
	}

	int power = 0;
	for (int i = 49; i >= 0; i--) {

		char currC = num[i];

		if (currC != 0 && currC != -52) {

			int currI = charToInt(currC);
			char multPow[300];
			char baseC[300];
			convertToCharArr(base, baseC);

			char powerC[300];
			char currI_asCharArr[300];
			convertToCharArr(currI, currI_asCharArr);

			powTo(baseC, power, getNumLength(baseC), powerC);
			multyNums(10, currI_asCharArr, powerC, getNumLength(currI_asCharArr), getNumLength(powerC), true, multPow);
			sumNums(10, deltaDexNum, multPow, getNumLength(deltaDexNum), getNumLength(multPow), true, deltaDexNum);
			power++;
		}
	}

	int deltaDexNumL = getNumLength(deltaDexNum) - 1;

	for (int i = 0; i <= deltaDexNumL; i++) {

		dexNum[i] = deltaDexNum[i];
	}
}

void convertToBase(int base, char* num1, char* num2) {

	char dexNum1[300];
	char dexNum2[300];

	convertToDex(base, num1, dexNum1);
	convertToDex(base, num2, dexNum2);

	int newBase = inputBase();

	char baseNum1[300];
	char baseNum2[300];

	convertDexToBase(newBase, dexNum1, baseNum1);
	convertDexToBase(newBase, dexNum2, baseNum2);

	cout << "Base " << newBase << endl;
	cout << "Number 1: ";
	printNum(baseNum1);
	cout << "Number 2: ";
	printNum(baseNum2);
}

void changeNum(int base, char* num1, char* num2, int arrowLevel) {

	int starIndex = 0;
	char e = 'o';
	char deltaNum[50];

	for (int i = 0; i < 50; i++)
		deltaNum[i] = num1[i];

	do {
		system("cls");

		printMenu(base, num1, num2, arrowLevel);

		cout << "DELETE         - Backspace" << endl;
		cout << "Increase digit - UP" << endl; 
		cout << "Decrease digit - DOWN" << endl;
		cout << "Move star      - LEFT/RIGHT" << endl;

		for (int i = 0; i < starIndex; i++)
			cout << " ";
		cout << "v" << endl;
		printNum(deltaNum);

		for (int i = 0; i < starIndex; i++)
			cout << " ";
		cout << "^" << endl;

		char L = _getch();
		if (L == 224)
			L = _getch();

		switch (L) {

		case 72:
			changeDigit(base, deltaNum, starIndex, true);
			break;

		case 80:
			changeDigit(base, deltaNum, starIndex, false);
			break;

		case 75:
			if (starIndex != 0) {
				starIndex--;
			} else if(getNumLength(deltaNum) < 50){
				char zeroArr[50];
				convertToCharArr(0, zeroArr);
				sumCharArrs(zeroArr, deltaNum, deltaNum);
			}
			break;

		case 77:
			if (starIndex != getNumLength(deltaNum) - 1) {
				starIndex++;

				if (deltaNum[0] == '0') {
					for (int i = 0; i < getNumLength(deltaNum) - 1; i++) {
						char buff = deltaNum[i + 1];
						deltaNum[i] = buff;
					}

					deltaNum[getNumLength(deltaNum) - 1] = 0;
					starIndex--;
				}
			}
			else if(getNumLength(deltaNum) < 50) {
				char zeroArr[50];
				convertToCharArr(0, zeroArr);
				sumCharArrs(deltaNum, zeroArr, deltaNum);
				starIndex++;
			}
			break;

		case 8:
			if (deltaNum[starIndex] != 0 && getNumLength(deltaNum) > 1) {
				for (int i = starIndex; i < getNumLength(deltaNum) - 1; i++) {
					char buff = deltaNum[i + 1];
					deltaNum[i] = buff;
				}

				deltaNum[getNumLength(deltaNum) - 1] = 0;
			}
			break;

		case 27:
			e = 'e';
			break;
		}

	} while (e != 'e');

	for (int i = 0; i < 50; i++)
		num1[i] = deltaNum[i];

	correctNumber(num1);
}

void convertDexToBase(int base, char* _dexNum, char* baseNum) {
	
	char dexNum[300];
	copyArrs(dexNum, _dexNum, 300);

	if (getNumLength(dexNum) == 1 && dexNum[0] == '0') {

		baseNum[0] = '0';

		for (int i = 1; i < 300; i++)
			baseNum[i] = 0;
		return;
	}

	char deltaResult[300];

	char zeroArr[300];
	convertToCharArr(0, zeroArr);

	char baseArr[300];
	convertToCharArr(base, baseArr);

	for (int i = 0; i < 300; i++)
		deltaResult[i] = 0;

	int len = 0;

	for (int i = 0; isBigger(dexNum, zeroArr, getNumLength(dexNum), 1); i++) {

		char leftOver[300];
		modDivNums(10, dexNum, baseArr, leftOver);

		char c = divideMod(base, convertCharArrToInt(leftOver));
		baseNum[i] = c;

		divNums(10, dexNum, baseArr, true, dexNum);
		len++;
	}

	char deltaDexNum[300];
	for (int i = 0; i < 300; i++)
		deltaDexNum[i] = 0;

	for (int i = 0; i < len; i++)
		deltaDexNum[i] = baseNum[len - i - 1];

	for (int i = 0; i < 300; i++)
		baseNum[i] = deltaDexNum[i];
}

char divideMod(int base, int n) {

	if (base >= 2 && base < 11) {
		return 48 + n;
	}
	else {

		if (n > 9)
			return 55 + n;
		else
			return 48 + n;
	}
}



void convertToCharArr(int n, char* num) {

	char deltaNum[300];

	if (n == 0) {
		num[0] = '0';
		return;
	}

	int len = 0;
	
	for (int i = 0; i < 300; i++)
		num[i] = 0;

	while (n != 0) {
		deltaNum[len] = (n % 10) + 48;
		n /= 10;
		len++;
	}

	for (int i = len-1; i >= 0; i--)
		num[i] = deltaNum[len - i-1];
}

int charToInt(char c) {
	if (c >= '0' and c <= '9')
		return c - '0';

	return c - 'A' + 10;
}

char intToChar(int n) {
	if (n >= 0 and n <= 9)
		return '0' + n;
	return 'A' + n - 10;
}

void sumCharArrs(char* num1, char* num2) {

	int startIndex = getNumLength(num1);

	for (int i = 0; i < getNumLength(num2); i++)
		num1[startIndex + i] = num2[i];
}

void sumCharArrs(char* num1, char* num2, char* newCharArray) {

	int startIndex = getNumLength(num1);

	char deltaResult[50];

	for (int i = 0; i < 50; i++) {
		deltaResult[i] = 0;
	}

	for (int i = 0; i < getNumLength(num1); i++)
		deltaResult[i] = num1[i];

	for (int i = 0; i < getNumLength(num2); i++)
		deltaResult[getNumLength(num1) + i] = num2[i];

	for (int i = 0; i < getNumLength(deltaResult); i++)
		newCharArray[i] = deltaResult[i];
}

int getNumLength(char* num, int size) {

	int n = 0;
	for (int i = 0; i < size; i++) {

		if (num[i] != -52 and num[i] != 0)
			n++;
		else
			break;
	}

	return n;
}

bool isBigger(char* num1, char* num2, int num1L, int num2L) {

	if (num1L > num2L)
		return true;
	if (num1L < num2L)
		return false;

	for (int i = 0; i < num1L; i++)
		if (num1[i] > num2[i])
			return true;
		else if (num1[i] < num2[i])
			return false;

	return false;
}

bool isBiggerOrEqual(char* num1, char* num2, int num1L, int num2L) {

	if (num1L > num2L)
		return true;
	if (num1L < num2L)
		return false;

	bool equal = true;

	for (int i = 0; i < num1L; i++) {
		if (num1[i] > num2[i])
			return true;
		else if (num1[i] < num2[i])
			return false;

		if (num1[i] != num2[i])
			equal = false;
	}

	return equal;
}

void correctNumber(char* num) {

	if (getNumLength(num) == 1)
		return;

	bool leftZeros = true;
	char deltaResult[50];

	for (int i = 0; i < 50; i++)
		deltaResult[i] = 0;

	int deltaIndex = 0;
	for (int i = 0; i < getNumLength(num); i++) {
		if (num[i] != '0' && leftZeros) {
			leftZeros = false;
			deltaResult[deltaIndex] = num[i];
			deltaIndex++;
		}
		else if (!leftZeros) {
			deltaResult[deltaIndex] = num[i];
			deltaIndex++;
		}
	}

	if (deltaResult[0] == 0)
		deltaResult[0] = '0';

	for (int i = 0; i < 50; i++)
		num[i] = 0;

	int resultIndex = 0;
	for (int i = 0; i < 50; i++) {
		
		if (deltaResult[i] != 0) {
			num[resultIndex] = deltaResult[i];
			resultIndex++;
		}
	}
}

void correctNumber300(char* num) {

	if (getNumLength(num) == 1)
		return;

	bool leftZeros = true;
	char deltaResult[300];

	for (int i = 0; i < 300; i++)
		deltaResult[i] = 0;

	int deltaIndex = 0;
	for (int i = 0; i < getNumLength(num); i++) {
		if (num[i] != '0' && leftZeros) {
			leftZeros = false;
			deltaResult[deltaIndex] = num[i];
			deltaIndex++;
		}
		else if (!leftZeros) {
			deltaResult[deltaIndex] = num[i];
			deltaIndex++;
		}
	}

	if (deltaResult[0] == 0)
		deltaResult[0] = '0';

	for (int i = 0; i < 300; i++)
		num[i] = 0;

	int resultIndex = 0;
	for (int i = 0; i < 300; i++) {

		if (deltaResult[i] != 0) {
			num[resultIndex] = deltaResult[i];
			resultIndex++;
		}
	}
}

int convertCharArrToInt(char* num) {

	if (getNumLength(num) == 2) {

		int n1 = charToInt(num[0]);
		int n2 = charToInt(num[1]);
		return n1 * 10 + n2;
	}
	else {
		return charToInt(num[0]);
	}
}

void setToZero(char* arr, int len) {
	for (int i = 0; i < len; i++)
		arr[i] = 0;
}

void setToZero(int* arr, int len) {
	for (int i = 0; i < len; i++)
		arr[i] = 0;
}

void copyArrs(char* arr1, char* arr2, int lenOfArr1) {
	for (int i = 0; i < lenOfArr1; i++) {
		arr1[i] = arr2[i];
			if (arr1[i] == 0)
				break;
	}
}
