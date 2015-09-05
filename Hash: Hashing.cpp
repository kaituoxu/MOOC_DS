//PAT: Hashing

#include <iostream>

using namespace std;

struct HashTbl {
	int *Elements;
	int *Status;
	int TableSize;
};
typedef HashTbl *HashTable;

int NextPrime(int x);
HashTable Create(int TableSize);
int Insert(int Key, HashTable H);

int main()
{
	int MSize, N, x, i, *Index;
	HashTable H;

	cin >> MSize >> N;
	H = Create(MSize);
	Index = new int[N];
	for (int i = 0; i != N; ++i) {
		cin >> x;
		Index[i] = Insert(x, H);
	}

	for (i = 0; i != N - 1; ++i) {
		if (Index[i] > -1) {
			cout << Index[i] << " ";
		} else {
			cout << "-" << " ";
		}
	}
	if (Index[i] > -1) {
		cout << Index[i] << endl;
	} else {
		cout << "-" << endl;
	}

	delete []H->Elements;
	delete []H->Status;
	delete H;

}

int NextPrime(int x)
{
	for (int next = x; ; ++next) {
		int i;
		for (i = 2; i * i <= next; ++i) {
			if (next % i == 0) break;
		}
		if (i * i > next) {
			//cout << next;
			return next;
		}
	}
}
HashTable Create(int TableSize)
{
	HashTable H;
	H = new HashTbl;
	H->TableSize = NextPrime(TableSize);
	H->Elements = new int[H->TableSize];
	H->Status = new int[H->TableSize];
	for (int i = 0; i != H->TableSize; ++i) {
		H->Status[i] = -1;
	}
	return H;
}
int Insert(int Key, HashTable H)
{
	int pos, nowPos;

	//Find
	nowPos = pos = Key % H->TableSize;
	for (int i = 1; H->Status[nowPos] != -1; ++i) {
		if (H->Status[nowPos] == 1) break;
		H->Status[nowPos] = 1;//collision have processed
		nowPos = pos + i * i;
		if (nowPos >= H->TableSize) {
			nowPos -= H->TableSize;
		}
	}

	//Insert
	if (H->Status[pos] == -1) {
		H->Elements[pos] = Key;
		H->Status[pos] = 0;
		return pos;
	} else {
		for (int i = 0; i != H->TableSize; ++i) {
			if (H->Status[i] == 1) {
				H->Status[i] = 0;
			}
		}
		return -1;
	}
}
