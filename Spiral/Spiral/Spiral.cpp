#include <iostream>
#include <conio.h>
#include <fstream>
#include <istream>

using namespace std;

struct SaveFile {

public:
	int char_count = 1;
	char * save_seq;
};

void drawSpiral(int width, int height, int InOutMode, int torsionMode, SaveFile* s_file);
void StartSaveProcedure(SaveFile* s_file);
void LoadSaveFile();

void InputW_H(int& width, int& height) {

	while (width <= 0 || width > 11) {

		cout << "Enter width: " << endl;
		cin >> width;
	}

	while (height <= 0 || height > 11) {

		cout << "Enter height: " << endl;
		cin >> height;
	}
}
void PrintChooseMenu(int width, int height, int& arrowLevel, int& InOutMode, int& torsionMode) {

	cout << "Width = " << width << " Height = " << height << endl;
	if (arrowLevel == 1) {
		cout << "Inside out  | Clockwise <-" << endl;
		InOutMode = 1;
		torsionMode = 1;
	}
	else {
		cout << "Inside out  | Clockwise" << endl;
	}
	if (arrowLevel == 2) {
		cout << "Inside out  | Counterclockwise <-" << endl;
		InOutMode = 1;
		torsionMode = -1;
	}
	else {
		cout << "Inside out  | Counterclockwise" << endl;
	}
	if (arrowLevel == 3) {
		cout << "Outside in  | Clockwise <-" << endl;
		InOutMode = 2;
		torsionMode = 1;
	}
	else {
		cout << "Outside in  | Clockwise" << endl;
	}
	if (arrowLevel == 4) {
		cout << "Outsinde in | Counterclockwise <-" << endl;
		InOutMode = 2;
		torsionMode = -1;
	}
	else {
		cout << "Outsinde in | Counterclockwise" << endl;
	}
	if (arrowLevel == 5) {
		cout << "Load save <-\n";
	}
	else {
		cout << "Load save\n";
	}

	cout << "\nTo save this pattern press [S]\n";
}
void ControlInput(int& arrowLevel, SaveFile& s_file, char& ch) {

	char L = _getch();
	if (L == 224)
		L = _getch();

	switch (L)
	{
	case 72:
		if (arrowLevel != 1)
			arrowLevel--;
		break;
	case 80:
		if (arrowLevel != 5)
			arrowLevel++;
		break;

	case 'S':
		StartSaveProcedure(&s_file);
		break;

	case 13:
		if (arrowLevel == 5) {
			LoadSaveFile();
			system("pause");
		}
		else {
			ch = 'e';
		}
		break;
	}
}

int main() {

	int width = -1;
	int height = -1;
	SaveFile s_file = SaveFile();
	s_file.save_seq = new char[1000];
	s_file.save_seq[0] = '\0';
	int InOutMode = 1;
	int torsionMode = 1;
	int arrowLevel = 1;

	InputW_H(width, height);

	char ch = 't';

	do {
		system("cls");

		PrintChooseMenu(width, height, arrowLevel, InOutMode, torsionMode);
		drawSpiral(width, height, InOutMode, torsionMode, &s_file);
		ControlInput(arrowLevel, s_file, ch);
	} while (ch != 'e');

	return 0;
}

void int_to_char(int n, char* c) {


	char nc = ' ';
	char n_str[3]{ '\0', '\0', '\0' };

	int i = 0;
	while (n != 0) {

		nc = (n % 10) + 48;
		n /= 10;

		n_str[i] = nc;
		i++;
	}

	char f_str[4] = { '\0', '\0', '\0', '\0', };
	int j = 0;
	for (int i = 2; i >= 0; i--) {
		if (n_str[i] == '\0')
			continue;
		f_str[j] = n_str[i];
		j++;
	}

	strcat(c, f_str);
}

void CalculateSpiral(int width, int height, int InOutMode, int torsionMode, int** spiral) {

	double side = height;
	int x = ceil(side / 2 - 1);
	int y = ceil(side / 2 - 1);

	int maxNumber = (width * height) + 1;
	int currentNumber = 1;

	int directionX = 1;
	int directionY = 1;

	int sideX = width - height + 1;
	int sideY = 1;

	switch (InOutMode) {

	case 1:

		if (width >= height) {

			side = height;
			sideX = width - height + 1;
			sideY = 1;

			if (torsionMode == 1) {
				x = ceil(side / 2 - 1);
			}
			else {
				x = width - ceil(side / 2 - 1) - 1;
				directionX = -1;
			}
			y = ceil(side / 2 - 1);
		}
		else {

			side = width;
			sideX = 1;
			sideY = height - width + 1;
			directionY = -1;

			if (torsionMode == 1) {

				x = ceil(side / 2 - 1);
				y = height - 1 - x;
			}
			else {

				directionX = -1;
				x = width - ceil(side / 2 - 1) - 1;
				y = height - 1 - ceil(side / 2 - 1);
			}
		}


		spiral[x][y] = currentNumber++;

		if (height > width) {
			for (int i = 0; i < sideY; i++) {
				y += directionY;
				spiral[x][y] = currentNumber++;
			}

			directionY = 1;
			sideY++;
		}

		while (currentNumber != maxNumber) {

			for (int i = 0; i < sideX; i++) {

				if (currentNumber == maxNumber)
					break;

				x += directionX;
				spiral[x][y] = currentNumber++;
			}

			sideX++;
			directionX = -directionX;

			for (int i = 0; i < sideY; i++) {

				if (currentNumber == maxNumber)
					break;

				y += directionY;
				spiral[x][y] = currentNumber++;
			}

			sideY++;
			directionY = -directionY;
		}
		break;

	case 2:
		int i = 0;
		int p = 0;
		sideX = width;
		sideY = height;

		if (torsionMode == 1) {

			while (currentNumber != maxNumber) {
				for (i = p; i < sideX; i++) {
					spiral[i][p] = currentNumber++;
				}

				if (currentNumber == maxNumber)
					break;
				for (i = p + 1; i < sideY; i++) {
					spiral[sideX - 1][i] = currentNumber++;
				}

				if (currentNumber == maxNumber)
					break;
				for (i = sideX - 2; i >= p; i--) {
					spiral[i][sideY - 1] = currentNumber++;
				}

				if (currentNumber == maxNumber)
					break;
				for (i = sideY - 2; i > p; i--) {
					spiral[p][i] = currentNumber++;
				}

				p++;
				sideX--;
				sideY--;
			}
		}
		else {
			while (currentNumber != maxNumber)
			{
				for (i = p; i < sideY; i++) {
					spiral[p][i] = currentNumber++;
				}

				for (i = p + 1; i < sideX; i++) {
					spiral[i][sideY - 1] = currentNumber++;
				}

				if (currentNumber == maxNumber)
					break;

				for (i = sideY - 2; i >= p; i--) {
					spiral[sideX - 1][i] = currentNumber++;
				}
				for (i = sideX - 2; i > p; i--) {
					spiral[i][p] = currentNumber++;
				}

				p++;
				sideX--;
				sideY--;
			}
		}

		if (!width % 2)
			spiral[(width + 1) / 2][(width + 1) / 2] = currentNumber;

		break;
	}
}

void PrintSpiral(int width, int height, int** spiral, SaveFile* s_file) {

	s_file->save_seq = new char[1000];
	s_file->save_seq[0] = '\0';
	s_file->char_count = 1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%5d", spiral[j][i]);

			if (spiral[j][i] > 9)
				strcat(s_file->save_seq, "   ");
			else
				strcat(s_file->save_seq, "    ");

			int_to_char(spiral[j][i], s_file->save_seq);
			s_file->char_count += 5;

		}
		cout << endl;
		strcat(s_file->save_seq, "\n");
		s_file->char_count++;
	}

	strcat(s_file->save_seq, "\0");
	s_file->char_count++;
}

void drawSpiral(int width, int height, int InOutMode, int torsionMode, SaveFile* s_file) {

	int** spiral = new int* [width];

	for (int i = 0; i < width; i++)
		spiral[i] = new int[height];

	CalculateSpiral(width, height, InOutMode, torsionMode, spiral);
	PrintSpiral(width, height, spiral, s_file);
}

void StartSaveProcedure(SaveFile* s_file) {

	char ch[153] = "testName";

	const char ESN[] = "Enter save name: ";
	cout << ESN;

	while (true) {

		loop_start:
		char buffer[153] = "\0";
		cin.clear();
		cin.getline(buffer, 152);

		if (strlen(buffer) >= 153) {
			cout << strlen(buffer) << "File name is too large.\n";
			cout << ESN;
			continue;
		}

		if (buffer[0] == '\0')
			continue;

		for (int i = 0; i < 152; i++) {
				char t = buffer[i];
				if (t == '\\'
					or t == '/'
					or t == '*'
					or t == '?'
					or t == '\"'
					or t == '<'
					or t == '>'
					or t == '|') {
					
					cout << "File name contains unexpected symbols.\n";
					cout << ESN;
					goto loop_exit;
				}
		}

		if(false) {
			loop_exit:
			continue;
		}

		strcpy_s(ch, buffer);
		char fName[167] = "Save Files/";
		strcat_s(fName, ch);
		strcat_s(fName, ".txt");

		ifstream FileT(fName);
		if (!FileT) {

			cout << "Save file [" << fName << "] has been created.\n";
		}
		else {
			cout << "Save file with such name already exists.\n";
			continue;
		}

		FILE* save_file = fopen(fName, "w+");

		if (save_file != NULL) {
			fwrite(s_file->save_seq, sizeof(char), s_file->char_count, save_file);
			fclose(save_file);
		}
		else {
			cout << "\nSave error. Cannot open file.";
		}

		system("pause");
		
		return;
	}

	return;
}

void LoadSaveFile() {

	char ch[153] = "testName";

	cout << "\nTo exit type [/exit]\n";

	const char ESN[] = "\nEnter save name: ";
	cout << ESN;

	while (true) {

		char buffer[153] = "\0";
		cin.clear();
		cin.getline(buffer, 152);
		strcpy_s(ch, buffer);
		char fName[167] = "Save Files/";
		strcat_s(fName, ch);
		strcat_s(fName, ".txt");

		if (buffer[0] == '\0')
			continue;

		if (!strcmp(ch, "/exit"))
			return;

		FILE* save_file_in = fopen(fName, "rb");

		if (save_file_in != NULL) {

			while (1)
			{
				char c = fgetc(save_file_in);
				if (c == EOF)
					break;
				else
					printf("%c", c);
			}
			return;
		} else {

			cout << "Save file with such name does not exist.";
			cout << ESN;
			continue;
		}
	}
}
