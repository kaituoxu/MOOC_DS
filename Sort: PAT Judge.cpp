#include <iostream>
#include <cmath>
using namespace std;

#define MAX_NUM_OF_KEY	8
#define RADIX			10
typedef int KeysType;
struct SLCell {
	//KeysType keys[MAX_NUM_OF_KEY];
	int *keys[4];
	int unpass[6];//process -1
	int next;
};
struct SLList {
	SLCell *r;
	int keynum;
	int recnum;
	int Kpass[2];
};
typedef int ArrType[RADIX];

void Distribute(SLCell r[], int i, ArrType &f, ArrType &e, int u)
{
	int j;
	for (j = 0; j < RADIX; ++j) {
		f[j] = 0;
	}
	for (int p = r[0].next; p; p = r[p].next) {
		//j = ord(r[p].keys[i]);
		j = r[p].keys[i][0] / (int)pow(10, u) % 10;
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
void Distribute2(SLCell r[], int i, ArrType &f, ArrType &e, int u)
{
	int j;
	for (j = 0; j < RADIX; ++j) {
		f[j] = 0;
	}
	int p2;
	for (int p = r[0].next; p; p = p2) {
		//j = ord(r[p].keys[i]);
		j = r[p].keys[i][0] / (int)pow(10, u) % 10;
		p2 = r[p].next;
		if (!f[j]) {
			e[j] = p;
		} else {
			r[p].next = f[j];
		}
		f[j] = p;
	}
}
void Collect2(SLCell r[], int i, ArrType f, ArrType e)
{
	int j, t;
	for (j = RADIX - 1; !f[j]; --j);
	r[0].next = f[j];
	t = e[j];
	while (j > 0) {
		for (--j; j > 0 && !f[j]; --j);
		if (f[j]) {
			r[t].next = f[j];
			t = e[j];
		}
	}
	r[t].next = 0;
}
void Radix_Sort2(SLList &L)
{
	ArrType f, e;
	for (int i = L.recnum; i > 0; --i) {
		L.r[i].next = i - 1;
	}
	L.r[0].next = L.recnum;
	for (int i = L.keynum - 3; i >= 0; --i) {
		for (int j = 0; j < L.Kpass[i]; ++j) {
			Distribute2(L.r, i, f, e, j);
			Collect2(L.r, i, f, e);
		}
	}
}
void Radix_Sort(SLList &L)
{
	ArrType f, e;
	for (int i = 0; i < L.recnum; ++i) {
		L.r[i].next = i + 1;
	}
	L.r[L.recnum].next = 0;
	for (int i = L.keynum - 3; i >= 0; --i) {
		for (int j = 0; j < L.Kpass[i]; ++j) {
			Distribute(L.r, i, f, e, j);
			Collect2(L.r, i, f, e);
		}
	}
}

int main()
{
	int N, K, M, id, proNum, proScore, kNum, max = 0;
	int *p;	//full scores
	SLList L;

	cin >> N >> K >> M;

	p = (int *)malloc((K + 1) * sizeof(int));
	for (int i = 0; i != K; ++i) {
		cin >> p[i + 1];	//p[1..K] is scores
	}

	//allocate memory
	L.recnum = N;
	L.r = (SLCell *)malloc((N + 1) * sizeof(SLCell));
	for (int i = 0; i != N + 1; ++i) {
		L.r[i].keys[0] = (int *)malloc(sizeof(int));
		L.r[i].keys[1] = (int *)malloc(sizeof(int));
		L.r[i].keys[2] = (int *)malloc((K + 1) * sizeof(int));
	}
	//initialize
	for (int i = 0; i != N + 1; ++i) {
		L.r[i].keys[0][0] = 0;
		L.r[i].keys[1][0] = 0;
		for (int j = 0; j != K + 1; ++j) {
			L.r[i].keys[2][j] = 0;
		}
		for (int j = 0; j != 6; ++j) {
			L.r[i].unpass[j] = -1;
		}
	}

	int Kpass[2] = { 0, 0 };
	//input
	for (int i = 0; i != M; ++i) {
		cin >> id >> proNum >> proScore;

		if (proScore == p[proNum]) {
			++(L.r[id].keys[1][0]);

			if (L.r[id].keys[1][0] > Kpass[1]) {
				Kpass[1] = L.r[id].keys[1][0];
			}
		}
		if (proScore > L.r[id].keys[2][proNum]) {
			L.r[id].keys[2][proNum] = proScore;
		}
		L.r[id].unpass[proNum] = 0;
	}
	for (int i = 1; i != N + 1; ++i) {
		int sum = 0;
		for (int j = 1; j != K + 1; ++j) {
			sum += L.r[i].keys[2][j];
		}
		L.r[i].keys[0][0] = sum;

		if (sum > Kpass[0]) {
			Kpass[0] = sum;
		}
	}
	L.keynum = 4;
	//get Kpass
	for (int i = 0; i < 2; ++i) {
		int k;
		for (k = 1; ; ++k) {
			Kpass[i] /= 10;
			if (0 == Kpass[i]) break;
		}
		L.Kpass[i] = k;
	}

	Radix_Sort(L);

	//output
	int pos;
	int rank = 0, rank2 = 0;
	int preScore = 0;
	for (pos = L.r[0].next; pos; pos = L.r[pos].next) {
		if (L.r[pos].keys[0][0] != 0) {
			++rank2;
			if (L.r[pos].keys[0][0] != preScore) {
				rank = rank2;
				preScore = L.r[pos].keys[0][0];
			}
			cout << rank << " ";
			printf("%05d ", pos);
			cout << L.r[pos].keys[0][0] << " ";
			int i;
			for (i = 1; i != K; ++i) {
				if (L.r[pos].unpass[i] != -1) {
					cout << L.r[pos].keys[2][i] << " ";
				} else {
					cout << "-" << " ";
				}
			}
			if (L.r[pos].unpass[i] != -1) {
				cout << L.r[pos].keys[2][i] << endl;
			} else {
				cout << "-" << endl;
			}
		}
	}

	//right output method
	//int p;
	//for (p = L.r[0].next; L.r[p].next; p = L.r[p].next) {
	//	cout << L.r[p].keys << " ";
	//}
	//cout << L.r[p].keys << endl;

}
