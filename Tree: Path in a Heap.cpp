#include <iostream>

using namespace std;

const int MAXSIZE = 1000;
const int MINDATA = -10001;
typedef struct HeapStruct* MinHeap;
typedef int ElementType;
struct HeapStruct {
	ElementType *Elements;
	int Size;
	int Capacity;
};
MinHeap CreateMinHeap(int MaxSize);
void InsertMinHeap(MinHeap H, ElementType item);
void PrintPath(MinHeap H, int idx);
int main()
{
	int Check[MAXSIZE];
	int N, M, tmp;

	cin >> N >> M;
	MinHeap H = CreateMinHeap(N);
	for (int i = 0; i != N; ++i) {
		cin >> tmp;
		InsertMinHeap(H, tmp);
	}
	for (int i = 0; i != M; ++i) {
		cin >> Check[i];
	}

	for (int i = 0; i != M; ++i) {
		PrintPath(H, Check[i]);
	}
}

MinHeap CreateMinHeap(int MaxSize)
{
	MinHeap H = (MinHeap)malloc(sizeof(HeapStruct));
	H->Elements = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = MINDATA;
	return H;
}

void InsertMinHeap(MinHeap H, ElementType item)
{
	int i;
	if (H->Capacity == 0) {
		return;
	}
	--H->Capacity;
	i = ++H->Size;
	for (; H->Elements[i / 2] > item; i /= 2) {
		H->Elements[i] = H->Elements[i / 2];
	}
	H->Elements[i] = item;
}

void PrintPath(MinHeap H, int idx)
{
	int pos = idx;
	while (pos > 1) {
		cout << H->Elements[pos] << " ";
		pos /= 2;
	}
	cout << H->Elements[pos] << endl;
}
