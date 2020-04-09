#include <iostream>
#include <fstream>
#include <istream>
#include <conio.h>

using namespace std;

struct BiList {

    int value;
    BiList* next_element = nullptr;
    BiList* prev_element = nullptr;
};

class Velolist {

public:
    BiList* head = nullptr;
    int size = 0;

    Velolist() { head = new BiList(); }

    BiList* ElementAt(int index) {

        if (index < 0 || index >= size) {
            cout << "ERROR: Index out of bounds.";
            system("pause");
            exit(0);
        }

        BiList* buffer = head->next_element;
        
        for (int i = 1; i <= index; i++)
            buffer = buffer->next_element;

        return buffer;
    }

    void InsertAt(int index, int value) {

        //Проверка на валидность
        if (index < 0 || index > size) {
            cout << "ERROR: Index out of bounds.\n";
            system("pause");
            return;
        }

        //Создаем новый элемент и присваеваем значение
        BiList* newElement = new BiList();
        newElement->value = value;

        //Если лист еще пустой
        if (size == 0) {

            head->next_element = newElement;
            newElement->prev_element = head;

            size++;
            return;
        }

        //Если добавляем на первое место
        if (index == 0) {

            head->next_element->prev_element = newElement;
            
            newElement->next_element = head->next_element;
            newElement->prev_element = head;

            head->next_element = newElement;
            
            size++;
            return;
        }

        //Если добавляем на последнее место
        if (index == size) {

            BiList* lastElement = ElementAt(size - 1);

            newElement->next_element = lastElement->next_element;

            lastElement->next_element = newElement;
            newElement->prev_element = lastElement;

            //На случай замкнутого списка.
            if (newElement->next_element)
                newElement->next_element->prev_element = newElement;// все равно, что head->prev_element = newElement

            size++;
            return;
        }

        if (index > 0 && index < size) {

            BiList* prevElement = ElementAt(index - 1);

            newElement->prev_element = prevElement;
            newElement->next_element = prevElement->next_element;

            prevElement->next_element->prev_element = newElement;
            prevElement->next_element = newElement;

            size++;
            return;
        }
    }

    void RemoveAt(int index) {

        if (index < 0 || index >= size) {
            cout << "ERROR: Index out of bounds.\n";
            system("pause");
            return;
        }

        BiList* elementToRemove = ElementAt(index);
        BiList* prevElement = elementToRemove->prev_element;
        BiList* nextElement = elementToRemove->next_element;

        prevElement->next_element = nextElement;
        
        if (nextElement)
            nextElement->prev_element = prevElement;

        delete(elementToRemove);
        size--;

        if (size == 0) {
            head->prev_element = nullptr;
            head->next_element = nullptr;
        }
    }

    void Link(int index) {

        if (index < 0 || index >= size) {
            cout << "ERROR: Index out of bounds.";
            system("pause");
            return;
        }

        BiList* newStartElement = ElementAt(index);
        BiList* lastElement = ElementAt(size - 1);

        for (int i = 0; i < index; i++)
            RemoveAt(0);

        lastElement->next_element = head;
        head->prev_element = lastElement;
    }

    void UnLink(int index) {

        if (!head->prev_element) {
            cout << "List isn't linked.\n";
            system("pause");
            return;
        }

        if (size == 1) {
            head->prev_element = nullptr;
            head->next_element->next_element = nullptr;
            return;
        }

        BiList* newStartElement = ElementAt(index);
        BiList* currentLastElement = head->prev_element;
        newStartElement->prev_element->next_element = nullptr;

        currentLastElement->next_element = head->next_element;
        head->next_element->prev_element = currentLastElement;

        head->next_element = newStartElement;
        newStartElement->prev_element = head;

        head->prev_element = nullptr;
    }

    void PrintList() {

        if (size == 0) {
            cout << "List is empty \n";
            return;
        }

        BiList* buffer = head->next_element;

        int index = 0;
        while (buffer && buffer != head) {
            
            cout << "[" << index << "] " << buffer->value << endl;
            buffer = buffer->next_element;
            index++;
        }

        if (head->prev_element) {

            cout << "\n List is linked.\n";
            cout << "[" << head->prev_element->value << "] --next--> [" << head->next_element->value << "].\n";
            cout << "[" << head->next_element->value << "] --prev--> [" << head->prev_element->value << "].\n";
        }
        else {
            cout << "List isn't linked.\n";
        }
    }
};

void TestInsertAt(Velolist* vl) {

    int index, value;

    cout << "Index: ";
    cin >> index;

    cout << "Value: ";
    cin >> value;

    vl->InsertAt(index, value);
}

void TestRemoveAt(Velolist* vl) {

    int index;
    cout << "Index: ";
    cin >> index;

    vl->RemoveAt(index);
}

void TestChainInsert(Velolist* vl) {

    int size = 0;

    while (size <= 0) {
        cout << "\nSize of chain: ";
        cin >> size;
    }

    int startIndex = -1;

    while (startIndex < 0 || startIndex > vl->size) {

        cout << "\nStartIndex: ";
        cin >> startIndex;
    }

    for (int i = 0; i < size; i++) {
        int value;
        cin >> value;
        vl->InsertAt(startIndex + i, value);
    }
}

void TestChainDelete(Velolist* vl) {

    int startIndex = -1;
    int endIndex = -1;

    while (startIndex < 0 || startIndex >= vl->size) {
        cout << "\nStart index: ";
        cin >> startIndex;
    }

    while (endIndex < startIndex || endIndex >= vl->size) {
        cout << "\nEnd index: ";
        cin >> endIndex;
    }

    for (int i = 0; i <= endIndex-startIndex; i++) {
        vl->RemoveAt(startIndex);
    }
}

void TestLink(Velolist* vl) {

    int index = -1;

    if (vl->size == 0) {
        cout << "List is empty.\n";
        system("pause");
        return;
    }


    while (index < 0 || index >= vl->size) {
        cout << "\nIndex: ";
        cin >> index;
    }

    vl->Link(index);
}

void TestUnlink(Velolist* vl) {

    if (!vl->head->prev_element) {
        cout << "List isn't linked.\n";
        system("pause");
        return;
    }

    int index = -1;

    while (index < 0 || index >= vl->size) {

        cout << "\nindex: ";
        cin >> index;
    }

    vl->UnLink(index);
}

void StartSaveProcedure(Velolist* vl) {

    //Обработка ввода имени файла
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

        if (false) {
        loop_exit:
            continue;
        }

        //Конец обработки имени файла

        //Открытие файла
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
        

        ofstream FileO;
        FileO.open(fName);

        if (vl->head->prev_element)
            FileO << "L\n";
        else
            FileO << "U\n";

        for (int i = 0; i < vl->size; i++)
            FileO << vl->ElementAt(i)->value << " ";

        FileO.close();

        system("pause");
        return;
    }

    return;
}

void StartLoadProcedure(Velolist* vl) {

    char ch[153] = "testName";

    cout << "\nTo exit type: exit()";

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

        if (strcmp(ch,"exit()") == 0)
            return;

        ifstream FileI;
        FileI.open(fName);

        if (buffer[0] == '\0')
            continue;

        if (FileI.is_open()) {
            
            bool isLinked = false;
            char L;

            //Deleting old list
            while (vl->size != 0)
                vl->RemoveAt(0);

            FileI >> L;

            isLinked = (L == 'L') ? true : false;

            int value;

            int index = 0;
            while (FileI >> value) {

                vl->InsertAt(index, value);
                index++;
            }

            if (isLinked)
                vl->Link(0);

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

void PrintMenu(Velolist* vl) {

    vl->PrintList();

    cout << "\nAvailable tests: \n";
    cout << "[1] - InsertAt\n";
    cout << "[2] - RemoveAt\n";
    cout << "[3] - ChainInsert\n";
    cout << "[4] - DeleteChain\n";
    cout << "[5] - Link\n";
    cout << "[6] - Unlink\n";
    cout << "[7] - SaveList\n";
    cout << "[8] - LoadList\n";

    int test_mode = 0;
    cout << "\nEnter test number:";
    cin >> test_mode;

    switch (test_mode) {
    case 1:
        TestInsertAt(vl);
        break;

    case 2:
        TestRemoveAt(vl);
        break;

    case 3:
        TestChainInsert(vl);
        break;

    case 4:
        TestChainDelete(vl);
        break;

    case 5:
        TestLink(vl);
        break;

    case 6:
        TestUnlink(vl);
        break;

    case 7:
        StartSaveProcedure(vl);
        break;

    case 8:
        StartLoadProcedure(vl);
        break;
    }
}

void init(Velolist* vl) {

    for (int i = 0; i < 5; i++)
        vl->InsertAt(i, i);
}

int main()
{
    Velolist vl;
    init(&vl);

    while (true) {
        system("cls");
        cout << "\t\tTest Start\n\n";

        PrintMenu(&vl);
    }

    system("pause");
}

