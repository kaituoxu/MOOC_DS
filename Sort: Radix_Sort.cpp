#include <iostream>
#include <cmath>
using namespace std;

#define MAX_NUM_OF_KEY	8
#define RADIX			10
typedef int KeysType;
struct SLCell {
	//KeysType keys[MAX_NUM_OF_KEY];
	int keys;
	int next;
};
struct SLList {
	SLCell *r;
	int keynum;
	int recnum;
};
typedef int ArrType[RADIX];

void Distribute(SLCell r[], int i, ArrType &f, ArrType &e)
{
	int j;
	for (j = 0; j < RADIX; ++j) {
		f[j] = 0;
	}
	for (int p = r[0].next; p; p = r[p].next) {
		j = r[p].keys / (int)pow(10, i) % 10;   // ord(r[p].keys[i]);
		if (!f[j]) f[j] = p;
		else r[e[j]].next = p;
		e[j] = p;
	}
}

void Collect(SLCell r[], int i, ArrType f, ArrType e)
{
	int j, t;
	for (j = 0; !f[j]; ++j);
	r[0].next = f[j];
	t = e[j];
	while (j < RADIX - 1) {
		for (++j; j < RADIX - 1 && !f[j]; ++j);
		if (f[j]) {
			r[t].next = f[j];
			t = e[j];
		}
	}
	r[t].next = 0;
}
void Radix_Sort(SLList &L)
{
	ArrType f, e;
	for (int i = 0; i < L.recnum; ++i) {
		L.r[i].next = i + 1;
	}
	L.r[L.recnum].next = 0;
	for (int i = 0; i < L.keynum; ++i) {
		Distribute(L.r, i, f, e);
		Collect(L.r, i, f, e);
	}
}
int main()
{
	//Radix Sort
	int kNum, max = 0;
	SLList L;

	cin >> L.recnum;
	L.r = (SLCell *)malloc(L.recnum * sizeof(SLCell));
	for (int i = 0; i != L.recnum; ++i) {
		cin >> L.r[i + 1].keys;
		if (L.r[i + 1].keys > max) max = L.r[i + 1].keys;
	}
	for (kNum = 1;; ++kNum) {
		if (0 == max / 10) break;
		max /= 10;
	}
	L.keynum = kNum;

	Radix_Sort(L);

	//right output method
	int p;
	for (p = L.r[0].next; L.r[p].next; p = L.r[p].next) {
		cout << L.r[p].keys << " ";
	}
	cout << L.r[p].keys << endl;

	//wrong output method
	//for (int i = 0; i != L.recnum; ++i) {
	//	cout << L.r[i + 1].keys << " ";
	//}
	//cout << endl;
}
