//PAT: Phone Chat Carzy

#include <iostream>
#include <string>

using namespace std;

typedef int Index;
typedef string ElementType;
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
Index Hash(ElementType Key, int TableSize);
Position FindMax(HashTable H, int &maxSame);

Position MAXP;
int MAXSAME = 1;
int MAXCNT = 0;

int main()
{
	HashTable H;
	int N, maxSame = 1;
	ElementType send, rec;
	Position maxP;

	cin >> N;
	H = InitializeTable(100000);
	for (int i = 0; i != N; ++i) {
		cin >> send >> rec;
		//cout << send << " " << rec << endl;
		Insert(send, H);
		Insert(rec, H);
	}
	//cout << Find("13588625832", H)->cnt << endl;//debug

	cout << MAXP->PhoneNum << " " << MAXP->cnt;
	if (1 != MAXSAME) {
		cout << " " << MAXSAME;
	}
	cout << endl;
	//maxP = FindMax(H, maxSame);
	//cout << maxP->PhoneNum << " " << maxP->cnt;
	//if (1 != maxSame) {
	//	cout << " " << maxSame;
	//}
	//cout << endl;

	DestroyTable(H);
}

int NextPrime(int x)
{
	for (int Next = x; ; ++Next) {
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
	delete []H->TheLists;
	delete H;
}

Position Find(ElementType Key, HashTable H)
{
	Position P;
	List L;

	L = H->TheLists[Hash(Key, H->TableSize)];
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

	Pos = Find(Key, H);
	if (nullptr == Pos) {
		NewCell = new ListNode;
		L = H->TheLists[Hash(Key, H->TableSize)];
		NewCell->Next = L->Next;
		NewCell->PhoneNum = Key;
		NewCell->cnt = 1;
		L->Next = NewCell;
	} else {
		++(Pos->cnt);
		if (Pos->cnt > MAXCNT) {
			MAXCNT = Pos->cnt;
			MAXP = Pos;
			MAXSAME = 1;
		} else if (Pos->cnt == MAXP->cnt) {
			if (Pos->PhoneNum < MAXP->PhoneNum) {
				MAXP = Pos;
			}
			++MAXSAME;
		}
	}
}

Index Hash(ElementType Key, int TableSize)
{
	unsigned int HashVal = 0;
	//int i = 0;

	//while (Key[i] != '\0') {
	//	HashVal += Key[i++]-'0';
	//}
	HashVal = atoi(&Key[6]);
	return HashVal % TableSize;
}

Position FindMax(HashTable H, int &maxSame)
{
	Position P, maxP = H->TheLists[0]->Next;
	int maxCnt = 0;

	maxSame = 1;
	for (int i = 0; i != H->TableSize; ++i) {
		P = H->TheLists[i]->Next;
		while (P != nullptr) {
			if (P->cnt > maxCnt) {
				maxP = P;
				maxCnt = P->cnt;
				maxSame = 1;
			} else if (P->cnt == maxCnt) {
				if (P->PhoneNum < maxP->PhoneNum) {
					maxP = P;
				}
				++maxSame;
			}
			P = P->Next;
		}
	}
	return maxP;
}
