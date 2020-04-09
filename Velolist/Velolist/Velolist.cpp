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
			cout << "List is linked.\n[" << Back()->value << "]-->[" << next_elem->value << "]\n";
		}
	}
};

class BiVelolist {

public:
	int value;
	BiVelolist* next_elem = nullptr;
	BiVelolist* prev_elem = nullptr;

	BiVelolist() {
	}

	BiVelolist(int start_value) {
		value = start_value;
	}

	int Size() {

		BiVelolist* buffer = next_elem;
		int size = 0;
		while (buffer != nullptr && buffer != this) {
			size++;
			buffer = buffer->next_elem;
		}

		return size;
	}

	BiVelolist* Element_At(int index) {

		if (index < -1 || index >= Size()) {
			cout << "BiVelolist: Out of bounds exception\n";
			system("pause");
			exit(0);
		}

		BiVelolist* buffer = this;
		for (int i = 0; i <= index; i++)
			buffer = buffer->next_elem;

		return buffer;
	}

	BiVelolist* Front() {
		return Element_At(0);
	}

	BiVelolist* Back() {
		return Element_At(Size() - 1);
	}

	void Insert_At(int index, int new_value) {

		BiVelolist* newElement = new BiVelolist(new_value);

		BiVelolist* prevElement = Element_At(index - 1);
		BiVelolist* currElement = prevElement->next_elem;

		prevElement->next_elem = newElement;

		newElement->prev_elem = prevElement;
		newElement->next_elem = currElement;

		if (currElement == nullptr) { return; }

		currElement->prev_elem = newElement;
	}

	void Append(int new_value) {

		Insert_At(Size(), new_value);
	}

	void Remove_At(int index) {

		if (index < 0) {
			cout << "BiVelolist: Out of bounds exception\n";
			system("pause");
			exit(0);
		}

		BiVelolist* b = Element_At(index);

		BiVelolist* prevElement = b->prev_elem;
		BiVelolist* nextElement = b->next_elem;

		if(prevElement != nullptr)
			prevElement->next_elem = nextElement;

		if (nextElement != nullptr)
			nextElement->prev_elem = prevElement;

		delete b;
	}

	void Remove_Last() {
		Remove_At(Size() - 1);
	}
	
	void Link(int index) {

		if (index < 0)
		{
			cout << "BiVelolist: Index out of bounds.\n";
			system("pause");
			exit(0);
		}

		BiVelolist* last_elem = Back();
		BiVelolist* link_elem = Element_At(index);

		for (int i = 0; i < index; i++)
			Remove_At(0);

		last_elem->next_elem = this;
		prev_elem = last_elem;
	}

	/* 0-1-2-[3]-4-5-\   ->>>  [3]-4-5-0-1-2
	   \-----------/
	*/

	void Unlink(int index) {

		if (prev_elem == nullptr)
		{
			cout << "BiVelolist: List isn't linked.\n";
			system("pause");
			exit(0);
		}

		if (Size() == 1)
			return;

		BiVelolist* newFirst = Element_At(index);
		BiVelolist* newLast = newFirst->prev_elem;

		BiVelolist* currLast = prev_elem;

		currLast->next_elem = next_elem;
		next_elem->prev_elem = currLast;

		prev_elem = nullptr;
		next_elem = newFirst;

		newFirst->prev_elem = this;
		newLast->next_elem = nullptr;
	}
	
	void PrintList() {

		cout << "\n\nSize: " << Size() << endl;

		BiVelolist* buffer = this;

		for (int i = 0; i < Size(); i++) {
			cout << "List[" << i << "]: " << (buffer->next_elem)->value << endl;
			buffer = buffer->next_elem;
		}

		if (prev_elem != nullptr) {
			cout << "List is linked.\n[" << prev_elem->value << "]-n->[" << prev_elem->next_elem->next_elem->value << "]\n";
			cout << "[" << next_elem->value << "] -p->[" << next_elem->prev_elem->prev_elem->value << "]\n";
		}
	}
};



const int INIT_VELOLIST_SIZE = 10;

void init(Velolist* vl) {

	srand(time(NULL));

	for (int i = 0; i < INIT_VELOLIST_SIZE; i++)
		vl->Append((rand() % 100 + 1));
}

void init(BiVelolist* bvl) {

	srand(time(NULL));

	for (int i = 0; i < INIT_VELOLIST_SIZE; i++)
		bvl->Append((rand() % 10 + 1));
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

void TestInsertAt(BiVelolist& bvl) {

	int new_value;
	int index;

	cout << "Index: ";
	cin >> index;

	cout << "Value: ";
	cin >> new_value;

	bvl.Insert_At(index, new_value);
}

void TestAppend(Velolist& vl) {

	int value;
	cout << "Value: ";
	cin >> value;

	vl.Append(value);
}

void TestAppend(BiVelolist& bvl)
{
	int value;
	cout << "Value: ";
	cin >> value;

	bvl.Append(value);
}

void TestRemoveAt(Velolist& vl) {

	int index;
	cout << "Index: ";
	cin >> index;

	vl.Remove_At(index);
}

void TestRemoveAt(BiVelolist& bvl)
{
	int index;
	cout << "Index: ";
	cin >> index;

	bvl.Remove_At(index);
}

void TestLink(Velolist& vl) {

	int index;
	cout << "Index: ";
	cin >> index;

	vl.Link(index);
}

void TestLink(BiVelolist& bvl)
{
	int index;
	cout << "Index: ";
	cin >> index;

	bvl.Link(index);
}

void TestUnlink(BiVelolist& bvl)
{
	int index;
	cout << "Index: ";
	cin >> index;

	bvl.Unlink(index);
}

void PrintVelolistMenu(Velolist * vl)
{
	int test_mode = 0;
	vl->PrintList();
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
		TestInsertAt(*vl);
		break;

	case 2:
		TestAppend(*vl);
		break;

	case 3:
		TestRemoveAt(*vl);
		break;

	case 4:
		vl->Remove_Last();
		break;

	case 5:
		TestLink(*vl);
		break;

	case 6:
		vl->Unlink();
		break;
	}
}

void PrintBiVelolistMenu(BiVelolist * bvl)
{
	bvl->PrintList();
	
	cout << "\nAvailable tests: \n";
	cout << "[1] - Insert_At(int index, int value)\n";
	cout << "[2] - Append(int value)\n";
	cout << "[3] - RemoveAt(int index)\n";
	cout << "[4] - RemoveLast()\n";
	cout << "[5] - Link(int index)\n";
	cout << "[6] - Unlink()\n";

	int test_mode = 0;
	cout << "\nEnter test number:";
	cin >> test_mode;

	switch (test_mode) {
	case 1:
		TestInsertAt(*bvl);
		break;

	case 2:
		TestAppend(*bvl);
		break;

	case 3:
		TestRemoveAt(*bvl);
		break;

	case 4:
		bvl->Remove_Last();
		break;

	case 5:
		TestLink(*bvl);
		break;

	case 6:
		TestUnlink(*bvl);
		break;
	}
}

void main() {

	Velolist vl;
	BiVelolist bvl;

	init(&vl);
	init(&bvl);

	while (true) {
		system("cls");
		cout << "\t\tTest Start\n\n";

		PrintBiVelolistMenu(&bvl);
	}
}