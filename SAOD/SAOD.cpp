#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int c = 0;
int ct = 0;

struct Name
{
	char name_[32] = " ";
};

struct Street
{
	char street_[32];
};

struct NumberHouse
{
	short int numberHouse_ = 0;
};

struct NumberApartment
{
	short int numberApartment_ = 0;
};

struct Date
{
	char date_[10];
};

struct Tree
{
public:
	struct Tree* pLeft;
	struct Tree* pRight;
	Name name;
	Street street;
	NumberHouse house;
	NumberApartment apartment;
	Date date;
	bool use;
	int weight;

	Tree(Name name, Street street, NumberHouse house, NumberApartment apartment, Date date, Tree* pNext = nullptr, int weight = 0)
	{
		this->pLeft = pNext;
		this->pRight = pNext;
		this->name = name;
		this->street = street;
		this->house = house;
		this->apartment = apartment;
		this->date = date;
		this->weight = weight;
		use = 0;
	}
};

class List
{
public:
	List();
	~List();

	void DataReading(string path);
	void Push_back(Name name = Name(), Street street = Street(), NumberHouse house = NumberHouse(), NumberApartment apartment = NumberApartment(), Date date = Date());
	int GetSize() { return size; }
	int Print(int index);

	class Node
	{
	public:
		Node* pNext;
		Name name;
		Street street;
		NumberHouse house;
		NumberApartment apartment;
		Date date;
		bool use;
		bool bool_weight;
		int weight;

		Node(Name name, Street street, NumberHouse house, NumberApartment apartment, Date date, Node* pNext = nullptr, int weight = 0)
		{
			this->pNext = pNext;
			this->name = name;
			this->street = street;
			this->house = house;
			this->apartment = apartment;
			this->date = date;
			this->weight = weight;
			use = 0;
			bool_weight = 0;
		}
		Node* GetIndex(Node* node, int index);
	};

	int size = 0;
	Node* Record(int index);
	void Clear(List::Node* head);
	Node** GetHead() { return &head; };
	Node* GetHead1() { return head; };
	Node* head;
	void HEAD(Node* h) { head = h; }
	void SearchPrint(Node* head);
};

List::Node* GetIndex(List::Node* node, int index) {
	int current_node = 1;
	while (current_node != index)
	{
		node = node->pNext;
		current_node++;
	}
	return node;
}

void AddTree(Tree** root, List::Node* node)
{
	Tree** p = root;

	while ((*p) != NULL)
	{
		if (node->apartment.numberApartment_ < (**p).apartment.numberApartment_)
			p = &((**p).pLeft);
		else
			p = &((**p).pRight);
	}
	if ((*p) == NULL)
	{
		(*p) = (Tree*)malloc(sizeof(Tree));
		(**p).apartment.numberApartment_ = node->apartment.numberApartment_;
		(**p).house.numberHouse_ = node->house.numberHouse_;
		for (int i = 0; i < 32; i++)
		{
			(**p).name.name_[i] = node->name.name_[i];
			(**p).street.street_[i] = node->street.street_[i];
		}
		for (int i = 0; i < 10; i++)
		{
			(**p).date.date_[i] = node->date.date_[i];
		}
		(**p).pLeft = (**p).pRight = NULL;
	}
}

int SetWeightInList(int num, List::Node* root, int count = 0) {
	if (root != NULL)
	{
		if (num == root->apartment.numberApartment_ && root->bool_weight == 0)
		{
			count++;
			if (root->pNext != NULL)
			{
				count = SetWeightInList(num, root->pNext, count);
			}
			root->bool_weight = 1;
			root->weight = count;
		}
		else 
		{
			if (root->pNext != NULL) 
			{
				count = SetWeightInList(num, root->pNext, count);
			}
		}
	}
	return count;
}

void DOP_A1(List list, List::Node* root,  Tree** new_root, int size) {
	int i = 1, j = 1;
	while (i != size + 1)
	{
		root = GetIndex(list.GetHead1(), i);
		root->use = 0;
		SetWeightInList(root->apartment.numberApartment_, root);
		i++;
	}
	i = 0;
	while (i != size)
	{
		int max = 0, index = 1;
		while (j != size + 1)
		{
			root = GetIndex(list.GetHead1(), j);
			if (root->weight > max && root->use == 0)
			{
				max = root->weight;
				index = j;
			}
			j++;
		}
		root = GetIndex(list.GetHead1(), index);
		root->use = 1;
		i++;
		j = 1;
		AddTree(new_root, root);
	}
}

int PrintTree(Tree* tree)
{
	std::cout << "  " << "Name:" << " ";
	for (int cnt = 0; cnt < 32; cnt++)
	{
		std::cout << tree->name.name_[cnt];
	}
	std::cout << "  " << "Street:" << " ";

	for (int cnt = 0; cnt < 18; cnt++)
	{
		std::cout << tree->street.street_[cnt];
	}
	std::cout << "  " << "House:" << " ";

	std::cout << tree->house.numberHouse_;

	std::cout << "  " << "Apartment:" << " ";

	std::cout << tree->apartment.numberApartment_;

	std::cout << " " << "date:" << " ";

	for (int cnt = 0; cnt < 10; cnt++)
	{
		std::cout << tree->date.date_[cnt];
	}
	std::cout << endl;	

	return 0;
}

void treeprint(Tree* tree) {
	if (tree != NULL) { 
		treeprint(tree->pLeft); 
		PrintTree(tree);
		treeprint(tree->pRight); 
	}
}

List::Node* SortedMerge(List::Node* a,
	List::Node* b);
void FrontBackSplit(List::Node* source,
	List::Node** frontRef,
	List::Node** backRef);

void MergeSort(List::Node** headRef)
{
	List::Node* head = *headRef;
	List::Node* a;
	List::Node* b;

	if ((head == NULL) || (head->pNext == NULL))
	{
		return;
	}

	FrontBackSplit(head, &a, &b);

	MergeSort(&a);
	MergeSort(&b);

	*headRef = SortedMerge(a, b);
}

List::Node* SortedMerge(List::Node* a, List::Node* b)
{
	List::Node* result = NULL;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	for (int i = 0; i < 33; i++)
	{
		if ((a->street.street_[i] == NULL) && (b->street.street_[i] == NULL))
		{
			if ((a->house.numberHouse_) == (b->house.numberHouse_))
			{
				for (int c = 0; c < 32; c++)
				{
					if ((a->name.name_[c]) <= (b->name.name_[c]))
					{
						if ((a->name.name_[c]) < (b->name.name_[c]))
						{
							result = a;
							result->pNext = SortedMerge(a->pNext, b);
							break;
						}
						else
							continue;
					}
					else
					{
						result = b;
						result->pNext = SortedMerge(a, b->pNext);
						break;
					}
				}
			}
			else if ((a->house.numberHouse_) < (b->house.numberHouse_))
			{
				result = a;
				result->pNext = SortedMerge(a->pNext, b);
				break;
			}
			else
			{
				result = b;
				result->pNext = SortedMerge(a, b->pNext);
				break;
			}
		}
		if ((a->street.street_[i]) <= (b->street.street_[i]))
		{
			if ((a->street.street_[i]) < (b->street.street_[i]))
			{
				result = a;
				result->pNext = SortedMerge(a->pNext, b);
				break;
			}
			else
				continue;
		}
		else
		{
			result = b;
			result->pNext = SortedMerge(a, b->pNext);
			break;
		}
		break;
	}

	return (result);
}

void FrontBackSplit(List::Node* source,
	List::Node** frontRef,
	List::Node** backRef)
{
	List::Node* fast;
	List::Node* slow;
	slow = source;
	fast = source->pNext;

	while (fast != NULL)
	{
		fast = fast->pNext;
		if (fast != NULL)
		{
			slow = slow->pNext;
			fast = fast->pNext;
		}
	}

	*frontRef = source;
	*backRef = slow->pNext;
	slow->pNext = NULL;
}

List::List()
{
	size = 0;
	head = nullptr;
}

List::~List()
{
}

void List::DataReading(string path)
{
	ifstream reading(path);

	if (reading)
	{
		Name name{};
		Street street{};
		NumberHouse house{};
		NumberApartment apartment{};
		Date date{};

		int n = 800;
		char ch;


		for (int i = 0; i < n; i++)
		{

			for (int cnt = 0; cnt < 32; cnt++)
			{
				if (reading.get(ch))
					name.name_[cnt] = ch;
					
			}


			for (int cnt = 0; cnt < 18; cnt++)
			{
				if (reading.get(ch))
					street.street_[cnt] = ch;
			}

			for (int cnt = 0; cnt < 3; cnt++)
			{
				if (reading.get(ch))
				{
					if (ch == '\0')
						break;
					else 
						house.numberHouse_ = ch;
				}
			}

			for (int cnt = 0; cnt < 3; cnt++)
			{
				if (reading.get(ch))
				{
					if (ch == '\0')
						break;
					else
						apartment.numberApartment_ = ch;
				}
			}

			for (int cnt = 0; cnt < 10; cnt++)
			{
				if (reading.get(ch))
					date.date_[cnt] = ch;
			}
			Push_back(name, street, house, apartment, date);
		}
	}
}

void List::Push_back(Name name, Street street, NumberHouse house, NumberApartment apartment, Date date)
{
	if (head == nullptr)
	{
		head = new Node(name, street, house, apartment, date);
	}
	else
	{
		Node* current = this->head;


		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}

		current->pNext = new Node(name, street, house, apartment, date);
		size++;
	}

}

List::Node* List::Record(int index)
{
	int counter = 0;
	Node* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current;
		}
		current = current->pNext;
		counter++;
	}
}

int List::Print(int index)
{
	int cnt = 20;
	int counter = 0;
	Node* current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{

			for (int i = 0; i < cnt; i++)
			{
				if (current == nullptr)
					return 0;
				if (current->name.name_[0] == NULL)
					return 0;
				std::cout << "  " << "Name:" << " ";
				for (int cnt = 0; cnt < 32; cnt++)
				{
					std::cout << current->name.name_[cnt];
				}
				std::cout << "  " << "Street:" << " ";

				for (int cnt = 0; cnt < 18; cnt++)
				{
					std::cout << current->street.street_[cnt];
				}
				std::cout << "  " << "House:" << " ";

				std::cout << current->house.numberHouse_;

				std::cout << "  " << "Apartment:" << " ";

				std::cout << current->apartment.numberApartment_;

				std::cout << " " << "date:" << " ";

				for (int cnt = 0; cnt < 10; cnt++)
				{
					std::cout << current->date.date_[cnt];
				}
				std::cout << endl;
				//cout << counter;
				current = current->pNext;
			}

		}
		current = current->pNext;
		counter++;
	}

	return 0;
}

int BinSearch(int size, List::Node* arr[], char key[], List* listSearch)
{
	int count = 0;
	int L = 1;
	int R = size;
	int m = 0;
	while (L < R)
	{
		m = ((L + R) / 2);
		if (arr[m]->street.street_[0] < key[0])
			L = m + 1;
		else
			R = m;
	}
	for (int i = 0; i < size; i++)
	{
		if (arr[m] == NULL)
			return 0;
		if (arr[m]->street.street_[0] == NULL)
			return 0;
		if (arr[m]->street.street_[0] == key[0] && arr[m]->street.street_[1] == key[1] && arr[m]->street.street_[2] == key[2])
		{
			listSearch->Push_back(arr[m]->name, arr[m]->street, arr[m]->house, arr[m]->apartment, arr[m]->date);
			count++;

		}
		else if (count != 0)
			break;
		else if (arr[m]->pNext == NULL)
			break;
		m++;
	}
	return 0;
}

void Search(List::Node* node, List* listSearch, char key[])
{
	if (node->street.street_[0] == key[0] && node->street.street_[1] == key[1] && node->street.street_[2] == key[2])
	{
		listSearch->Push_back(node->name, node->street, node->house, node->apartment, node->date);
	}

	if (node->pNext != nullptr)
	{
		Search(node->pNext, listSearch, key);
	}
}

void FreeTree(Tree* tree) {
	if (tree->pLeft)   FreeTree(tree->pLeft);
	if (tree->pRight)  FreeTree(tree->pRight);
	delete tree;
}

void List::Clear(List::Node* head)
{
	while (head != NULL)
	{
		List::Node* next = head->pNext;
		delete head;
		head = next;
	}

	List::Node* h = NULL;
	HEAD(h);
	//Head->pNext = NULL;
	//Head = NULL;
}

void List::SearchPrint(Node* head)
{
	int counter = 0;
	Node* current = head;
	while (current != nullptr)
	{
		std::cout << "Name:" << " ";
		for (int cnt = 0; cnt < 32; cnt++)
		{
			std::cout << current->name.name_[cnt];
		}
		std::cout << "  " << "Street:" << " ";

		for (int cnt = 0; cnt < 18; cnt++)
		{
			std::cout << current->street.street_[cnt];
		}
		std::cout << "  " << "House:" << " ";

		std::cout << current->house.numberHouse_;

		std::cout << "  " << "Apartment:" << " ";

		std::cout << current->apartment.numberApartment_;

		std::cout << "  " << "date:" << " ";

		for (int cnt = 0; cnt < 10; cnt++)
		{
			std::cout << current->date.date_[cnt];
		}
		std::cout << endl;
		counter++;

		current = current->pNext;
	}

}

void BinSearchPrint(List::Node* arr[])
{
	int m = 0;
	for (int i = 0; i < 110; i++)
	{
		std::cout << m;
		std::cout << arr[m]->name.name_;

		std::cout << endl << "Street:" << "\t";


		std::cout << arr[m]->street.street_;

		std::cout << endl << "House:" << "\t";

		std::cout << arr[m]->house.numberHouse_;

		std::cout << endl << "Apartment:" << "\t";

		std::cout << arr[m]->apartment.numberApartment_;

		std::cout << endl << "date:" << "\t";


		std::cout << arr[m]->date.date_;
		std::cout << endl << "----------------------------------" << endl;
	}

	m++;
}

void SearchTree(Tree* tree, int numberApart) {
	while (tree != NULL)
	{
		if (tree->apartment.numberApartment_ == numberApart) {
			PrintTree(tree);
			SearchTree(tree->pRight, numberApart);
			break;
		}
		else if (tree->apartment.numberApartment_ > numberApart) {
				SearchTree(tree->pLeft, numberApart);
				break;
		}
		else if (tree->apartment.numberApartment_ < numberApart) {
				SearchTree(tree->pRight, numberApart);	
				break;
		}
	}
}

int Med(int L, int R, int P[]) {
	int Sl = 0;
	for (int i = L; i < R; i++) {
		Sl = Sl + P[i];
	}
	int Sr = P[R];
	int m = R;
	while (Sl >= Sr) {
		m = m - 1;
		Sl = Sl - P[m];
		Sr = Sr + P[m];
	}
	return m;
}

int Fano(int L, int R, int k, int(*C)[15], int* Lenght, int P[]) {
	if (L < R) {
		k = k + 1;
		int m = Med(L, R, P);
		for (int i = L; i <= R; i++) {
			if (i <= m) {
				C[i][k] = 0;
				Lenght[i] = Lenght[i] + 1;
			}
			else {
				C[i][k] = 1;
				Lenght[i] = Lenght[i] + 1;
			}
		}
		Fano(L, m, k, C, Lenght, P);
		Fano(m + 1, R, k, C, Lenght, P);
	}
	return (*C)[14];
}

void DataReadingChar(char* arrayUnicueSym, string path)
{
	ifstream reading(path);
	char arrayEncodedFile[100000];
	if (reading)
	{
		int sizeUnicueSym = 0;
		int count = 0;
		char getSym = NULL;
		char arraySort[170] = {'0'};
		int arrayChance[170] = {0};
		int tmp_cnt = 0;
		while (reading) {
			reading.get(getSym);
			for (int j = 0; j < sizeUnicueSym; j++)
			{
				if (arrayUnicueSym[j] == getSym) {
					count = 1;
					arrayChance[j] += 1;
					break;
				}
			}
			if (count == 0) {
				arrayUnicueSym[sizeUnicueSym] = getSym;
				arrayChance[sizeUnicueSym] = 1;
				sizeUnicueSym++;
				tmp_cnt++;
				cout << tmp_cnt  << "    "  << getSym << "\n";
			}
			count = 0;
		}
		//cout << endl << endl << sizeUnicueSym << endl << endl;

		for (int j = 0; j < sizeUnicueSym; j++)
		{
			//cout << array[j] << " = " << arrayChance[j] << endl;
		}
		int maxChance = 0;
		int index = 0;
		int temp;
		for (int k = 0; k < sizeUnicueSym; k++)
		{
			for (int j = k; j < sizeUnicueSym; j++)
			{
				if (arrayChance[j] > maxChance) {
					maxChance = arrayChance[j];
					index = j;
				}
			}
			temp = arrayChance[index];
			arrayChance[index] = arrayChance[k];
			arrayChance[k] = temp;
			arraySort[k] = arrayUnicueSym[index];
			maxChance = 0;
		}

		int arrayBinary[130][15];

		int wordLenght[130];
		for (int n = 0; n < sizeUnicueSym; n++)
		{
			wordLenght[n] = 0;
		}
		Fano(0, sizeUnicueSym - 1, -1, arrayBinary, wordLenght, arrayChance);
		
		int sumChance = 0;

		for (int n = 0; n < sizeUnicueSym; n++)
		{
			/*for (int j = 0; j < 15; j++)
			{
				if(arrayBinary[n][j] == 0 || arrayBinary[n][j] == 1)
					cout << arrayBinary[n][j] << ' ';
			}*/
			//cout << endl;
			sumChance += arrayChance[n];
		}
		/*for (int n = 0; n < sizeUnicueSym; n++)
		{
			cout << wordLenght[n] << '\t';
		}*/
		float arrayNewChance[130] = {0};
		for (int n = 0; n < sizeUnicueSym; n++)
		{
			arrayNewChance[n] = arrayChance[n] / float(sumChance);
			//cout << arrayChance[n] << ' ' << arrayNewChance[n] << '\n';
		}
		//cout << endl << sumChance << endl;
		float float_arr = 0;
		for (int n = 0; n < sizeUnicueSym; n++)
		{
			float_arr += arrayNewChance[n];
		}
		//cout << endl<< float_arr << '\n';

		float averageLength= 0;

		for (int n = 0; n < sizeUnicueSym; n++)
		{
			averageLength += arrayNewChance[n] * wordLenght[n];
		}
		cout << endl << "average lenght  = " << averageLength << endl;

		float entropy = 0;
		for (int n = 0; n < sizeUnicueSym; n++)
		{
			entropy -= arrayNewChance[n] * log2(arrayNewChance[n]);
		}

		cout << endl << "entropy = " << entropy << endl;

		ifstream reading_new(path);
		ofstream writeBinary;
		writeBinary.open("encoded.txt");
		int l = 0;
		while (reading_new) {
			reading_new.get(getSym);
			temp = NULL;
			for (sizeUnicueSym = 0; sizeUnicueSym < 130; sizeUnicueSym++)
			{
				temp = arraySort[sizeUnicueSym];
				if (temp == getSym)
				{
					break;
				}
			} 

			for (int i = 0; i < 15; i++)
			{
				if (arrayBinary[sizeUnicueSym][i] == 0)
				{
					arrayEncodedFile[l] = '0';
					writeBinary << '0';
					cout << arrayEncodedFile[l];
					l++;
				} else if (arrayBinary[sizeUnicueSym][i] == 1)
				{
					arrayEncodedFile[l] = '1';
					writeBinary << '1';
					cout << arrayEncodedFile[l];
					l++;
				}
			}
		}
	}
	//cout << array_new[0];	
}

int main()
{
	char key[3];
	int key_apartment;
	int action;

	std::cout << " 1 - Open base 4: ";
	std::cin >> action;

	string path = "testBase4.dat";

	ifstream file(path);

	List Lst;
	List LstSearch;
	Tree* tree = NULL;
	char arrayUnicueSym[200];
	for (int j = 0; j < 200; j++)
	{
		arrayUnicueSym[j] = '0';
	}

	if (action == 1)
	{
		system("cls");

		Lst.DataReading(path);
	}

	int size = Lst.GetSize();
	List::Node* Arr[111];

	int count = 0;

	MergeSort(Lst.GetHead());

	for (int i = 0; i < 111; i++)
	{
		Arr[i] = Lst.Record(i);
	}

	Lst.Print(0);

	for (;;) {
		switch (_getch()) {
		case 72:
			if (count == 0)
				break;
			else
			{
				count -= 20;
				system("cls");
				Lst.Print(count);
				break;
			}
		case 80:
			count += 20;
			system("cls");
			Lst.Print(count);
			break;
		case 27:
			exit(1);
		case 77:
			cout << "Street: ";
			cin >> key;
			system("cls");
			cout << key << endl;
			if (LstSearch.head != NULL)
			{
				LstSearch.Clear(LstSearch.GetHead1());
				LstSearch.size = 0;
			}
			BinSearch(111, Arr, key, &LstSearch);
			//Search(Lst.GetHead1(), &LstSearch, key);
			LstSearch.SearchPrint(LstSearch.GetHead1());
			cout << LstSearch.GetSize();
			break;
		case 75:
			if (tree != NULL) {
				FreeTree(tree);
				tree = NULL;
			}
			if (LstSearch.head != NULL)
			{
				system("cls");
				cout << key << endl;
				DOP_A1(LstSearch, LstSearch.head, &tree, LstSearch.GetSize());
				treeprint(tree);
			}
			break;
		case 's':
			cout << "Apartment: ";
			cin >> key_apartment;
			SearchTree(tree, key_apartment);
			break;
		case 'e':
			system("cls");
			DataReadingChar(arrayUnicueSym, path);
			break;
		}
	}
}

