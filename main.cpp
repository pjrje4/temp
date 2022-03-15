#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct student {
	char* first;
	char* last;
	int id;
	float gpa;
	student(char* firstIn, char* lastIn, int idIn, float gpaIn) {
		first = new char(strlen(firstIn) + 1);
		strcpy(first,firstIn);
		last = new char(strlen(lastIn) + 1);
		strcpy(last,lastIn);
		id = idIn;
		gpa = gpaIn;
	}
	~student() {
		delete first;
		delete last;
	}
};
struct item {
	student* s = NULL;
	item* next = NULL;
	item(student* sIn) {
		s = sIn;
	}
};
/*
struct hashT {
	int tablelength;
	item* items[];
	hashT(int length) {
		item* items[length];
		//items = new item*[length];
		tablelength = length;
	}
};*/
template <int N>
struct hashT {
  int tablelength = N;
  item* items[N];
};

int hashify(student* sIn, hashT* hashtable) {
	return (sIn->id % hashtable->tablelength);
}

char* randomName(char names[][20], int length) {
	srand(time(NULL));
	int randN = rand() % length;
	return names[randN];
}

void addStudent(hashT* &hash, student* sIn) {
	cout << "2 = " << hash->items[2] << endl;
	int slot = hashify(sIn, hash);
	cout << "2after hash = " << hash->items[2] << endl;
	item* newItem = new item(sIn);
	cout << "2afternewitem = " << hash->items[2] << endl;
	newItem->next = NULL;
	cout << "2afternextset = " << hash->items[2] << endl;
	cout << slot << endl;
	cout << "2 = " << hash->items[2] << endl;

	item* insert = hash->items[slot];

	cout << "2 = " << hash->items[2] << endl;
	if (insert == NULL) {
		hash->items[slot] = newItem;
	}
	else {	
		cout << "not null" << endl;
		while (insert->next != NULL) {
			insert = insert->next;
		}
		insert->next = newItem;
	}

	cout << "2 = " << hash->items[2] << endl;
}
hashT* newHashTable(int size) {
	//hashT* hashPointer1 = new hashT(size);
	hashT<size>* hashPointer;
	for (int i=0; i<size; i++) {
		hashPointer->items[i] = nullptr;
		cout << ""; // DONT REMOVE THIS IF YOU DO THE ENTIRE PROGRAM BREAKS HELP
	}
	return hashPointer;
}
bool rehash(hashT* &hashIn) {
	cout << "in rehash" << endl;
	bool re = false;
	for (int i = 0; i < hashIn->tablelength; i++) {	
		int col = 0;
		item* reader1 = hashIn->items[i];
		if (reader1 != NULL) {
			cout << "not empty: " << i << endl;
			col++;
			while (reader1->next != NULL) {
				col++;
				cout << "collisions: " << col << endl;
				if (col > 3) {
					re = true;
				}
				reader1 = reader1->next;
			}
		}
	}
	if (!re) {
		return false;
	}
	cout << "rehashing" << endl;
	hashT* newHash = newHashTable(hashIn->tablelength * 2);
	cout << "hashin2 = " << hashIn->items[2] << endl;
	cout << "newhash2 = " << newHash->items[2] << endl;
	for (int i = 0; i < hashIn->tablelength; i++) {
		item* reader = hashIn->items[i];
		if (reader != NULL) {
			cout << "2 = " << newHash->items[2] << endl;
			addStudent(newHash, reader->s);
			cout << "2 = " << newHash->items[2] << endl;

			while (reader->next != NULL) {
				reader = reader->next;
				cout << "2 = " << newHash->items[2] << endl;
				addStudent(newHash, reader->s);
				cout << "2 = " << newHash->items[2] << endl;
			}
		}
	}
	cout << "2 = " << newHash->items[2] << endl;
	hashIn = newHash;
	cout << "2 = " << hashIn->items[2] << endl;
	return true;	
}
int main() {	
	hashT* studentHash = newHashTable(100);
	char firstNames [1000] [20];
	char lastNames [1000] [20];
	
	//firstnames
        fstream firstfile;
        firstfile.open("fnames.txt", ios::in);
        if (!firstfile) {
                cout << "Can't find fnames.txt." << endl;
        }
        else {
                int reading = 0;
                while (reading <= 999) {
                        if (firstfile.eof()) { // end break
                                break;
                        }
                        char temp[20] = {'\0'};
                        firstfile.getline(temp, 20);
                        for (int i=0;i<20;i++) {
                                firstNames[reading][i] = temp[i];
                        }
                        reading++;
                }

        }
	//lastnames
	fstream lastfile;
	lastfile.open("lnames.txt", ios::in);
	if (!lastfile) {
		cout << "Can't find lnames.txt." << endl;
	}
	else {
		int reading = 0;
		while (reading <= 999) {
			if (lastfile.eof()) { // end break
				break;
			}
			char temp[20] = {'\0'};
			lastfile.getline(temp, 20);
			for (int i=0;i<20;i++) {
				lastNames[reading][i] = temp[i];
			}
			reading++;
		}

        }	
	while (true) { //loop
		char input[20];
		bool reh = false;
		cout << "Enter a command (ADD, PRINT, DELETE, QUIT): ";
		cin >> input;
		if (strcmp(input, "ADD") == 0) { //add students
			char sfname[20];
			char slname[20];
			int sid;
			float sgpa;

			cout << "What is the students first name? ";
			cin >> sfname;

			cout << "What is the students last name? ";
			cin >> slname;

			cout << "What is the students id? ";
			cin >> sid;
			
			cout << "What is the students gpa? ";
			cin >> sgpa;

			student* s = new student(sfname, slname, sid, sgpa);

			addStudent(studentHash, s);

		}
		else if (strcmp(input, "PRINT") == 0) { //print students
			//printStudent(students);
		}
		else if (strcmp(input, "DELETE") == 0) { //delete students
			//deleteStudent(students);
		}
		else if (strcmp(input, "QUIT") == 0) { //quit program
			return 0;
        	}
		while (rehash(studentHash)) {
			cout << "rehashed" << endl;
		}
	}
	return 0;
}
