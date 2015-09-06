//remember to read your CSDN blog

#include <iostream>
#include <string>
#include <cstdlib> //atoi
#include <cstring> //
//#include <ctime>
//clock_t start, stop;
//double duration;

using namespace std;

typedef int Index;
typedef char ElementType[12];
typedef struct ListNode *Position;
typedef Position List;
struct ListNode {
	ElementType PhoneNum;
	int cnt;
	Position Next;
};
struct HashTbl {
	List *TheLists;
	int TableSize;
};
typedef struct HashTbl *HashTable;

int NextPrime(int x);
HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
void Insert(ElementType Key, HashTable H);
Position Find(ElementType Key, HashTable H);
Index Hash(int Key, int TableSize);
void FindMax(HashTable H);

int main()
{
	HashTable H;
	int N;
	char send[12], rec[12];

	//start = clock();

	cin >> N;
	H = InitializeTable(2 * N);

	//stop = clock();
	//duration = ((double)(stop - start)) / CLK_TCK;
	//cout << duration << endl;

	//start = clock();
	for (int i = 0; i != N; ++i) {
		cin >> send >> rec;
		//cout << send << " " << rec << endl;
		Insert(send, H);
		Insert(rec, H);
	}

	//stop = clock();
	//duration = ((double)(stop - start)) / CLK_TCK;
	//cout << duration << endl;

	//start = clock();

	FindMax(H);

	//stop = clock();
	//duration = ((double)(stop - start)) / CLK_TCK;
	//cout << duration << endl;

	DestroyTable(H);
}

int NextPrime(int x)
{
	for (int Next = x;; ++Next) {
		int i;
		for (i = 2; i * i <= Next; ++i) {
			if (Next % i == 0) break;
		}
		if (i * i > Next) {
			return Next;
		}
	}
}
//HashTable : Separate Chaining
HashTable InitializeTable(int TableSize)
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

void DestroyTable(HashTable H)
{
	for (int i = 0; i != H->TableSize; ++i) {
		delete H->TheLists[i];
	}
	delete[]H->TheLists;
	delete H;
}

Position Find(ElementType Key, HashTable H)
{
	Position P;
	List L;

	L = H->TheLists[Hash(atoi(&Key[6]), H->TableSize)];
	P = L->Next;
	while (P != nullptr && P->PhoneNum != Key) {
		P = P->Next;
	}
	return P;
}

void Insert(ElementType Key, HashTable H)
{
	Position Pos, NewCell;
	List L;

	//Pos = Find(Key, H);
	L = H->TheLists[Hash(atoi(Key + 6), H->TableSize)];//
	Pos = L->Next;
	while (Pos != nullptr && strcmp(Pos->PhoneNum, Key)){
		Pos = Pos->Next;
	}

	if (nullptr == Pos) {
		NewCell = new ListNode;
		//L = H->TheLists[Hash(Key, H->TableSize)];
		strcpy(NewCell->PhoneNum, Key);
		NewCell->cnt = 1;
		NewCell->Next = L->Next;
		L->Next = NewCell;
	} else {
		++(Pos->cnt);
	}
}

Index Hash(int Key, int TableSize)
{
	return Key % TableSize;
	//return atoi(&Key[6]) % TableSize;
}

void FindMax(HashTable H)
{
	Position P;// maxP = H->TheLists[0]->Next;
	int maxCnt = 0, maxSame;
	string MinPhone;

	maxSame = 1;
	for (int i = 0; i != H->TableSize; ++i) {
		P = H->TheLists[i]->Next;
		while (P != nullptr) {
			if (P->cnt > maxCnt) {
				//maxP = P;
				MinPhone = P->PhoneNum;
				maxCnt = P->cnt;
				maxSame = 1;
			} else if (P->cnt == maxCnt) {
				if (P->PhoneNum < MinPhone) {
					//maxP = P;
					MinPhone = P->PhoneNum;
				}
				++maxSame;
			}
			P = P->Next;
		}
	}
	cout << MinPhone << " " << maxCnt;
	if (1 < maxSame) {
		cout << " " << maxSame;
	}
	cout << endl;
}
