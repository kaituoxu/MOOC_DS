#include <iostream>
#include <cstring>

using namespace std;

typedef struct ListNode *Position;
struct ListNode {
	char id[11];//QQ id
	char pw[17];//QQ password
	Position Next;
};
typedef Position List;
struct HashTbl {
	List *TheLists;
	int TableSize;
};
typedef HashTbl *HashTable;

int NextPrime(int N);
HashTable Create(int TableSize);
void Insert(char *id, char *pw, HashTable H);
int Hash(int Key, int TableSize);
void Find(char *id, char *pw, HashTable H);

int main()
{
	int N;
	char op;//operation
	char id[11];//QQ id
	char pw[17];//QQ password
	HashTable H;

	cin >> N;
	H = Create(N);
	for (int i = 0; i != N; ++i) {
		cin >> op >> id >> pw;
		//cout << op << " " << id << " " << pa << endl;
		if (op == 'N') {
			Insert(id, pw, H);
		} else {//op == 'L'
			Find(id, pw, H);
		}
	}
}

int NextPrime(int N)
{
	for (int next = N;; ++next) {
		int i = 0;
		for (i = 2; i * i <= next; ++i) {
			if (next % i == 0) break;
		}
		if (i * i > next) {
			//cout << next << endl;
			return next;
		}
	}
}
HashTable Create(int TableSize)
{
	HashTable H;
	H = new HashTbl;
	H->TableSize = NextPrime(TableSize);
	H->TheLists = new List[H->TableSize];
	for (int i = 0; i != H->TableSize; ++i) {
		H->TheLists[i] = new ListNode;
		H->TheLists[i]->Next = nullptr;
	}
	return H;
}
void Find(char *id, char *pw, HashTable H) 
{
	Position P, L;

	L = H->TheLists[Hash(atoi(id), H->TableSize)];
	P = L->Next;
	while (P != nullptr) {
		if (!strcmp(P->id, id)) {//P->id == id
			if (!strcmp(P->pw, pw)) {//P->pw == pw
				cout << "Login: OK" << endl;
				return;
			} else {//P->pw != pw
				cout << "ERROR: Wrong PW" << endl;
				return;
			}
		}
		P = P->Next;
	}
	cout << "ERROR: Not Exist" << endl;
	
}
void Insert(char *id, char *pw, HashTable H)
{
	Position P, L, NewCell;

	//Find
	L = H->TheLists[Hash(atoi(id), H->TableSize)];
	P = L->Next;
	while (P != nullptr && strcmp(P->id, id)) {
		P = P->Next;
	}

	//Insert
	if (P) {
		cout << "ERROR: Exist" << endl;
	} else {
		NewCell = new ListNode;
		strcpy(NewCell->id, id);
		strcpy(NewCell->pw, pw);
		NewCell->Next = L->Next;
		L->Next = NewCell;
		cout << "New: OK" << endl;
	}
}
int Hash(int Key, int TableSize)
{
	return Key % TableSize;
}
