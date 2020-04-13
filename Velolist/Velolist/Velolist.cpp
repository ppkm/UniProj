#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

struct List {

	int value;
	List* next_element = nullptr;
};

class Velolist {

public:
	List* head = nullptr;
	int size = 0;
	
	Velolist() {
		head = new List();
	}

	List* ElementAt(int index) {

		if (index < 0 || index >= size) {

			if (index == -1)
				return head;

			cout << "ERROR: Index out of bounds.";
			system("pause");
			exit(0);
		}

		List* buffer = head->next_element;

		for (int i = 1; i <= index; i++)
			buffer = buffer->next_element;

		return buffer;
	}

	void InsertAt(int index, int new_value) {

		if (index < 0 || index > size) {
			cout << "ERROR: Index out of bounds.\n";
			system("pause");
			return;
		}

		List* new_element = new List();
		new_element->value = new_value;

		List* prev_element = (index == 0) ? head : ElementAt(index-1);
		List* curr_element = prev_element->next_element;

		prev_element->next_element = new_element;
		new_element->next_element = curr_element;

		size++;
	}

	void RemoveAt(int index) {
		
		if (index < 0 || index >= size) {
			cout << "ERROR: Index out of bounds\n";
			system("pause");
			return;
		}

		List* b = ElementAt(index);
		ElementAt(index - 1)->next_element = b->next_element;
		delete b;
		size--;
	}

	void Link(int index) {

		if (index < 0 || index >= size) {
			cout << "ERROR: Index out of bounds.";
			system("pause");
			return;
		}

		List* last_elem = ElementAt(size-1);
		List* link_elem = ElementAt(index);

		for (int i = 0; i < index; i++)
			RemoveAt(0);

		last_elem->next_element = head;
	}

	void Unlink(int index) {

		if (!ElementAt(size-1)->next_element) {
			cout << "List isn't linked.\n";
			system("pause");
			return;
		}

		if (size == 1) {
			head->next_element->next_element = nullptr;
			return;
		}

		List* newStartElement = ElementAt(index);
		List* currentLastElement = ElementAt(size - 1);

		ElementAt(index - 1)->next_element = nullptr;

		currentLastElement->next_element = head->next_element;

		head->next_element = newStartElement;
	}

	void PrintList() {

		if (size == 0) {
			cout << "List is empty.\n";
			return;
		}

		List* buffer = head->next_element;

		int index = 0;

		while (buffer && buffer != head) {

			cout << "[" << index << "] " << buffer->value << endl;
			buffer = buffer->next_element;
			index++;
		}

		if (ElementAt(size - 1)->next_element) {

			cout << "\nList is linked.\n";
			cout << "[" << ElementAt(size - 1)->value << "] --next--> [" << head->next_element->value << "].\n";
		}
		else {
			cout << "\nList isn't linked.\n";
		}
	}
};

const int INIT_VELOLIST_SIZE = 10;

void init(Velolist* vl) {

	srand(time(NULL));

	for (int i = 0; i < INIT_VELOLIST_SIZE; i++)
		vl->InsertAt(0,(rand() % 100 + 1));
}

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
		cout << "\nStartIndex: ";
		cin >> startIndex;
	}

	while (endIndex < startIndex || endIndex >= vl->size) {
		cout << "\n\EndIndex: ";
		cin >> endIndex;
	}

	for (int i = 0; i <= endIndex - startIndex; i++) {
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

	if (!vl->ElementAt(vl->size - 1)) {
		cout << "List isn't linked.\n";
		system("pause");
		return;
	}

	int index = -1;

	while (index < 0 || index >= vl->size) {

		cout << "Index: ";
		cin >> index;
	}

	vl->Unlink(index);
}

void PrintVelolistMenu(Velolist * vl)
{
	int test_mode = 0;
	vl->PrintList();
	cout << "\nAvailable test: \n";
	cout << "[1] - InsertAt\n";
	cout << "[2] - RemoveAt\n";
	cout << "[3] - ChainInsert\n";
	cout << "[4] - ChainDelete\n";
	cout << "[5] - TestLink\n";
	cout << "[6] - TestUnlink\n";


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
	}
}

void main() {

	Velolist vl;

	init(&vl);

	while (true) {
		system("cls");
		cout << "\t\tTest Start\n\n";

		PrintVelolistMenu(&vl);
	}
}