#include <iostream>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <istream>
#include <list>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>

enum TYPE {

    EMPTY,
    WALL,
    FLAKE,
    ICE
};

struct Flake {

    int x;
    int y;
};

const char ENTER = 13;
const char ESCAPE = 27;
const char LEFT = 75;
const char RIGHT = 77;
const char UP = 72;
const char DOWN = 80;
const int top_margin = 3;
const int left_margin = 4;

const int N = 60;//TICKRATE
const int GRID_WIDTH = 50;
const int GRID_HEIGHT = 20;

//COLOURS
const int empty_c = 5;
const int wall_c = 8;
const int ice_c = 2;
const int flake_c = 10;
const int cursor_c = 7;

std::list<Flake*> flakes;
TYPE grid[GRID_WIDTH][GRID_HEIGHT];

short cursor_x = (GRID_WIDTH / 2) - 1;
short cursor_y = 1;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void cls() {

    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void ShowIntro() {

    for (int i = 0; i < 10; i++)
        wprintf(L"\n");

    SetConsoleTextAttribute(hConsole, empty_c);

    wprintf(L"\t  ███████████████████████████████████████████████████████████████████\n");
    wprintf(L"\t  █─▄▄▄─█▄─█─▄█▄─▄─▀█▄─▄▄─█▄─▄▄▀█▄─▄▄─█▄─▄████▀▄─██▄─█─▄█▄─▄▄─█─▄▄▄▄█\n");
    wprintf(L"\t  █─███▀██▄─▄███─▄─▀██─▄█▀██─▄─▄██─▄████─██▀██─▀─███─▄▀███─▄█▀█▄▄▄▄─█\n");
    wprintf(L"\t  ▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▀▀▄▄▄▄▄▀▄▄▀▄▄▀▄▄▄▀▀▀▄▄▄▄▄▀▄▄▀▄▄▀▄▄▀▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀\n");
    wprintf(L"\n\n");

    SetConsoleTextAttribute(hConsole, 13);
    wprintf(L"\t\t\t\t PRESS ENTER");

    char ch = 0;

    while (ch != ENTER) { ch = _getch(); }
}

void CreateGrid() {

    for (int x = 0; x < GRID_WIDTH; x++)
        for (int y = 0; y < GRID_HEIGHT; y++)
            grid[x][y] = (y == 0 or y == GRID_HEIGHT - 1 or x == 0 or x == GRID_WIDTH - 1) ? WALL : EMPTY;
}

void MoveCursor(int x = cursor_x, int y = cursor_y) {

    if (x != cursor_x or y != cursor_y) {

        setCursorPosition(cursor_x + left_margin, cursor_y + top_margin);

        if (grid[cursor_x][cursor_y] == EMPTY) {
            SetConsoleTextAttribute(hConsole, empty_c);
            std::wcout << L'·';
        }
        else {
            SetConsoleTextAttribute(hConsole, wall_c);
            std::wcout << L'█';
        }

        cursor_x = x;
        cursor_y = y;
    }

    SetConsoleTextAttribute(hConsole, cursor_c);
    setCursorPosition(cursor_x + left_margin, cursor_y + top_margin);
    std::wcout << L"×";
}

void PrintGrid() {

    cls();

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {

            switch (grid[x][y]) {

            case EMPTY:
                SetConsoleTextAttribute(hConsole, empty_c);
                setCursorPosition(x + left_margin, y + top_margin);
                std::wcout << L"·";
                break;

            case WALL:
                SetConsoleTextAttribute(hConsole, wall_c);
                setCursorPosition(x + left_margin, y + top_margin);
                std::wcout  << L"█";
                break;
            }
        }
    }

    MoveCursor();
}

void CreateFlake() {

    if (grid[cursor_x][2] != WALL and grid[cursor_x][2] != FLAKE and grid[cursor_x][2] != ICE) {
        Flake* new_flake = new Flake();

        new_flake->x = cursor_x;
        new_flake->y = 2;

        flakes.push_back(new_flake);
    }
}

void CreateWall() {

    if (cursor_y == 1)
        return;

    grid[cursor_x][cursor_y] = (grid[cursor_x][cursor_y] == WALL) ? EMPTY : WALL;

    setCursorPosition(cursor_x + left_margin, cursor_y + top_margin);

    if (grid[cursor_x][cursor_y] == WALL) {
        SetConsoleTextAttribute(hConsole, wall_c);
        std::wcout << L"█";
    }
    else {
        SetConsoleTextAttribute(hConsole, empty_c);
        std::wcout << L"·";
    }
}

void CalculateFallingFlakes() {

    for (Flake* f : flakes) {

        int x = f->x;
        int y = f->y;

        if (grid[x][y] == ICE)
            continue;


        if (grid[x][y + 1] == EMPTY) {

            SetConsoleTextAttribute(hConsole, empty_c);
            setCursorPosition(x + left_margin, y + top_margin);
            std::wcout << L"·";
            SetConsoleTextAttribute(hConsole, flake_c);
            setCursorPosition(x + left_margin, y + 1 + top_margin);
            std::wcout << L"×";

            grid[x][y + 1] = FLAKE;
            grid[x][y] = EMPTY;

            f->y++;
            continue;
        }
        
        if (grid[x - 1][y + 1] == EMPTY) {

            SetConsoleTextAttribute(hConsole, empty_c);
            setCursorPosition(x + left_margin, y + top_margin);
            std::wcout << L"·";
            SetConsoleTextAttribute(hConsole, flake_c);
            setCursorPosition(x - 1 + left_margin, y + 1 + top_margin);
            std::wcout << L"×";


            grid[x - 1][y + 1] = FLAKE;
            grid[x][y] = EMPTY;
            f->x--;
            f->y++;
            continue;
        }
        
        if (grid[x + 1][y + 1] == EMPTY) {

            SetConsoleTextAttribute(hConsole, empty_c);
            setCursorPosition(x + left_margin, y + top_margin);
            std::wcout << L"·";
            SetConsoleTextAttribute(hConsole, flake_c);
            setCursorPosition(x + 1 + left_margin, y + 1 + top_margin);
            std::wcout << L"×";

            grid[x + 1][y + 1] = FLAKE;
            grid[x][y] = EMPTY;
            f->x++;
            f->y++;
            continue;
        }

        SetConsoleTextAttribute(hConsole, ice_c);
        setCursorPosition(x + left_margin, y + top_margin);
        std::wcout << L"X";

        grid[x][y] = ICE;
    }
}

static bool deleteFlakes(Flake* flake) { delete flake; return true; }

void Melt() {

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[x][y] == FLAKE or grid[x][y] == ICE)
                grid[x][y] = EMPTY;
        }
    }

    flakes.remove_if(deleteFlakes);
}

void ControlGame() {
    
    cursor_x = (GRID_WIDTH / 2) - 1;
    cursor_y = 1;

    PrintGrid();

    char ch = 0;

    SetConsoleTextAttribute(hConsole, cursor_c);
    setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin - 2);
    std::wcout << L"You are in build mode.";
    setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin);
    std::wcout << L"Press [R] - to melt CYBERFLAKES.";
    setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin + 1);
    std::wcout << L"Press [ESC] - to exit CYBERFLAKES.";

    
    while (ch != ESCAPE) {

        Sleep(N);

        if (_kbhit()) {

            ch = _getch();

            if (ch == 224) ch = _getch();

            switch (ch) {

            case RIGHT:
                if (cursor_x + 1 < GRID_WIDTH - 1)
                    MoveCursor(cursor_x + 1, cursor_y);
                break;

            case LEFT:
                if (cursor_x - 1 > 0)
                    MoveCursor(cursor_x - 1, cursor_y);
                break;

            case ENTER:
                CreateFlake();
                break;

            case ESCAPE:
                exit(0);
                break;

            case 'R':
                Melt();
                PrintGrid();
                break;
            }

            SetConsoleTextAttribute(hConsole, cursor_c);
            setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin - 2);
            std::wcout << L"You are in build mode.";
            setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin);
            std::wcout << L"Press [R] - to melt CYBERFLAKES.";
            setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin + 1);
            std::wcout << L"Press [ESC] - to exit CYBERFLAKES.";
        }

        CalculateFallingFlakes();
    }
}

void SaveGrid() {

    char ch[153] = "testName";

    cls();

    while (true) {

    wprintf(L"Enter save name: ");

    loop_start:
        char buffer[153] = "\0";
        std::cin.clear();
        std::cin.getline(buffer, 152);

        if (strlen(buffer) >= 153) {
            wprintf(L"File name is too large.\n");
            wprintf(L"Enter save name: ");
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

                wprintf(L"File name contains unexpected symbols.\n");
                wprintf(L"Enter save name: ");
                goto loop_exit;
            }
        }

        if (false) {
        loop_exit:
            continue;
        }

        strcpy_s(ch, buffer);
        char fName[167] = "Save Files/";
        strcat_s(fName, ch);
        strcat_s(fName, ".txt");

        std::ifstream FileT(fName);
        if (!FileT) {

            wprintf(L"Save file has been created.\n");
        }
        else {
            wprintf(L"Save file with such name already exists.\n");
            continue;
        }

        std::ofstream file;

        file.open(fName);

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {

                if (grid[x][y] == WALL)
                    file << "W";
                else
                    file << "E";
            }
            file << "\n";
        }

        file.close();

        system("pause");

        return;
    }

    return;
}

void LoadGrid() {

    cls();
    char ch[153] = "testName";

    wprintf(L"\nTo exit type /exit");
    wprintf(L"\nEnter save name: ");

    while (true) {

        char buffer[153] = "\0";
        std::cin.clear();
        std::cin.getline(buffer, 152);
        strcpy_s(ch, buffer);
        char fName[167] = "Save Files/";
        strcat_s(fName, ch);
        strcat_s(fName, ".txt");

        if (buffer[0] == '\0')
            continue;

        if (!strcmp(ch, "/exit"))
            return;

        std::ifstream save;
        save.open(fName);

        if (save.is_open()) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                for (int x = 0; x < GRID_WIDTH; x++) {

                    char ch = 0;

                    save >> ch;

                    if (ch == 'W')
                        grid[x][y] = WALL;
                    else
                        grid[x][y] = EMPTY;
                }
            }
            save.close();
            return;
        }
        else {
            wprintf(L"\nSave file with such name does not exist.");
            wprintf(L"\nEnter save name: ");
            continue;
        }
    }
}

void ControlBuild() {

    char ch = 0;

    SetConsoleTextAttribute(hConsole, cursor_c);
    setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin - 2);
    std::wcout << L"You are in build mode.";
    setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin);
    std::wcout << L"Press [S] - to save this grid.";
    setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin + 1);
    std::wcout << L"Press [L] - to load an existing grid.";
    setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin + 2);
    std::wcout << L"Press [ESC] - to exit build mode.";

    while (ch != ESCAPE) {

        if (_kbhit()) {

            ch = _getch();

            if (ch == 224) ch = _getch();

            switch (ch) {

            case RIGHT:
                if (cursor_x + 1 < GRID_WIDTH - 1)
                    MoveCursor(cursor_x + 1, cursor_y);
                break;

            case LEFT:
                if (cursor_x - 1 > 0)
                    MoveCursor(cursor_x - 1, cursor_y);
                break;

            case UP:
                if (cursor_y - 1 >= 1)
                    MoveCursor(cursor_x, cursor_y - 1);
                break;

            case DOWN:
                if (cursor_y + 1 < GRID_HEIGHT - 1)
                    MoveCursor(cursor_x, cursor_y + 1);
                break;

            case ENTER:
                CreateWall();
                break;

            case 'S':
                SaveGrid();
                PrintGrid();
                break;

            case 'L':
                LoadGrid();
                PrintGrid();
                break;
            }

            SetConsoleTextAttribute(hConsole, cursor_c);
            setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin - 2);
            std::wcout << L"You are in build mode.";
            setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin);
            std::wcout << L"Press [S] - to save this grid.";
            setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin + 1);
            std::wcout << L"Press [L] - to load an existing grid.";
            setCursorPosition(left_margin + GRID_WIDTH + 2, top_margin + 2);
            std::wcout << L"Press [ESC] - to exit build mode.";
        }
    }

    ControlGame();
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    system("mode con cols=95 lines=25");
    ShowConsoleCursor(false);

    ShowIntro();
    cls();

    CreateGrid();
    PrintGrid();

    ControlBuild();
}
