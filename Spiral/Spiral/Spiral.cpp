#include <iostream>;
#include <conio.h>;
#include <fstream>;
#include <istream>;

using namespace std;

struct SaveFile {

public:
	int width = -1;
	int height = -1;

	int spiral[10][10];
};

void drawSpiral(int width, int height, int InOutMode, int torsionMode, SaveFile* s_file);
void StartSaveProcedure(SaveFile* s_file);
void LoadSaveFile();

int main() {

	int width = -1;
	int height = -1;

	while (width <= 0 || width > 11) {

		cout << "Enter width: " << endl;
		cin >> width;
	}

	while (height <= 0 || height > 11) {

		cout << "Enter height: " << endl;
		cin >> height;
	}

	SaveFile s_file;
	s_file.width = width;
	s_file.height = height;

	int InOutMode = 1;//1 2
	int torsionMode = 1;//1 -1
	int arrowLevel = 1;

	char ch = 't';

	do {
		system("cls");

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

		drawSpiral(width, height, InOutMode, torsionMode, &s_file);

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
	} while (ch != 'e');

	return 0;
}

void drawSpiral(int width, int height, int InOutMode, int torsionMode, SaveFile* s_file) {

	int** spiral = new int* [width];

	for (int i = 0; i < width; i++)
		spiral[i] = new int[height];

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
			} else {
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
			} else {

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

	// print
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%5d", spiral[j][i]);
			s_file->spiral[j][i] = spiral[j][i];
		}
		cout << endl;
	}
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

		/*ofstream FileO;
		FileO.open(fName);
		FileO << s_file->width << " " << s_file->height << " ";

		for (int i = 0; i < s_file->height; i++) {
			for (int j = 0; j < s_file->width; j++) {
				FileO << s_file->spiral[j][i] << " ";
			}
		}*/

		FILE** f;
		fopen_s(f, fName, "wb");

		for (int i = 0; i < s_file->height; i++) {
			for (int j = 0; j < s_file->width; j++) {
				fwrite_s(s_file->spiral[j], 4, 1, f);
				//FileO << s_file->spiral[j][i] << " ";
			}
		}

		fclose(f);

		//FileO.close();

		system("pause");
		
		return;
	}

	return;
}

void LoadSaveFile() {

	char ch[153] = "testName";

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

		ifstream FileI;
		FileI.open(fName);

		if (buffer[0] == '\0')
			continue;

		if (FileI.is_open()) {


			int width, height;
			int spiral[10][10];

			FileI >> width;
			FileI >> height;

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					int n = -1;
					FileI >> n;
					printf("%5d", n);
				}
				cout << endl;
			}


			FileI.close();
			return;
		}
		else {

			cout << "Save file with such name does not exist.";
			cout << ESN;
			continue;
		}
	}
}
