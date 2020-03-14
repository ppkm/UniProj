#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

class Velolist {

public:
	int value;
	Velolist* next_elem = nullptr;
	
	Velolist() {
	}

	Velolist(int start_value) {
	    value = start_value;
	}

	int Size() {

		Velolist* buffer = next_elem;
		int size = 0;
		while (buffer != nullptr && buffer != this) {
			size++;
			buffer = buffer->next_elem;
		}

		return size;
	}

	Velolist* Element_At(int index) {

		if (index < -1 || index >= Size()) {
			cout << "Velolist: Out of bounds exception\n";
			system("pause");
			exit(0);
		}

		Velolist* buffer = this;
		for (int i = 0; i <= index; i++)
			buffer = buffer->next_elem;

		return buffer;
	}
	
	Velolist* Front() {
		return Element_At(0);
	}

	Velolist* Back() {
		return Element_At(Size() - 1);
	}

	void Insert_At(int index, int new_value) {

		Velolist* new_element = new Velolist(new_value);

		Velolist* prev_element = Element_At(index-1);
		Velolist* curr_element = prev_element->next_elem;

		prev_element->next_elem = new_element;
		new_element->next_elem = curr_element;
	}

	void Append(int new_value) {

		Insert_At(Size(), new_value);
	}

	void Remove_At(int index) {
		
		Velolist* b = Element_At(index);
		Element_At(index - 1)->next_elem = b->next_elem;
		delete b;
	}

	void Remove_Last() {
		Remove_At(Size() - 1);
	}

	void Link(int index) {

		Velolist* last_elem = Back();
		Velolist* link_elem = Element_At(index);

		for (int i = 0; i < index; i++)
			Remove_At(0);

		last_elem->next_elem = this;
	}

	void Unlink() {

		Velolist* last_elem = Back();
		last_elem->next_elem = nullptr;
	}

	void PrintList() {

		cout << "\n\nSize: " << Size() << endl;
		Velolist* buffer = this;
		for (int i = 0; i < Size(); i++) {
			cout << "List[" << i << "]: " << (buffer->next_elem)->value << endl;
			buffer = buffer->next_elem;
		}

		if (Back()->next_elem != nullptr) {
			cout << "Link is linked.\n[" << Back()->value << "]-->[" << next_elem->value << "]\n";
		}
	}
};

const int INIT_VELOLIST_SIZE = 10;

void init(Velolist* vl) {

	srand(time(NULL));

	for (int i = 0; i < INIT_VELOLIST_SIZE; i++)
		vl->Append((rand() % 100 + 1));
}

void TestInsertAt(Velolist& vl) {

	int new_value;
	int index;

	cout << "Index: ";
	cin >> index;

	cout << "Value: ";
	cin >> new_value;

	vl.Insert_At(index, new_value);
}

void TestAppend(Velolist& vl) {

	int value;
	cout << "Value: ";
	cin >> value;

	vl.Append(value);
}

void TestRemoveAt(Velolist& vl) {

	int index;
	cout << "Index: ";
	cin >> index;

	vl.Remove_At(index);
}

void TestLink(Velolist& vl) {

	int index;
	cout << "Index: ";
	cin >> index;

	vl.Link(index);
}

void main() {

	Velolist vl;
	init(&vl);

	while (true) {
		system("cls");
		cout << "\t\tTest Start\n\n";

		vl.PrintList();

		int test_mode = 0;

		cout << "\nAvailable tests: \n";
		cout << "[1] - Insert_At(int index, int value)\n";
		cout << "[2] - Append(int value)\n";
		cout << "[3] - RemoveAt(int index)\n";
		cout << "[4] - RemoveLast()\n";
		cout << "[5] - Link(int index)\n";
		cout << "[6] - Unlink()\n";

		cout << "\nEnter test number:";
		cin >> test_mode;

		switch (test_mode) {
		case 1:
			TestInsertAt(vl);
			break;

		case 2:
			TestAppend(vl);
			break;

		case 3:
			TestRemoveAt(vl);
			break;

		case 4:
			vl.Remove_Last();
			break;

		case 5:
			TestLink(vl);
			break;

		case 6:
			vl.Unlink();
			break;
		}
	}
}