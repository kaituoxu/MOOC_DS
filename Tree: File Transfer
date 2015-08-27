#include <iostream>

using namespace std;
typedef int ElementType;
struct SetType{
	ElementType Data;
	int Parent;
};
const int MAXSIZE = 10001;

//int Find(SetType S[], ElementType X)
//{
//	int i;
//	for (i = 0; i < MAXSIZE && S[i].Data != X; ++i) ;
//	if (i >= MAXSIZE) return -1;
//	for (; S[i].Parent >= 0; i = S[i].Parent) ;
//	return i;//return the root of the set which includes X
//}
int Find(SetType S[], ElementType X) //ps overtime
{
	int r = X - 1;
	while ( S[r].Parent >= 0) {
		r = S[r].Parent;
	}
	return r;
}
void Union(SetType S[], ElementType X1, ElementType X2)
{
	int Root1, Root2;
	Root1 = Find(S, X1);
	Root2 = Find(S, X2);
	if (Root1 != Root2) {
		if (S[Root1].Parent <= S[Root2].Parent) {
			S[Root1].Parent += S[Root2].Parent;
			S[Root2].Parent = Root1;
		} else {
			S[Root2].Parent += S[Root1].Parent;
			S[Root1].Parent = Root2;
		}
	}
}

int main()
{
	int N, cnt;
	char op;
	SetType S[10000];
	ElementType c1, c2, r1, r2;

	cin >> N;
	for (int i = 0; i != N; ++i) {
		S[i].Data = i + 1;		//ps here
		S[i].Parent = -1;
	}
	while(true) {
		cin >> op;
		if (op == 'C') {
			cin >> c1 >> c2;
			r1 = Find(S, c1);
			r2 = Find(S, c2);
			if (r1 == r2) {
				cout << "yes" << endl;
			} else {
				cout << "no" << endl;
			}
		} else if (op == 'I') {
			cin >> c1 >> c2;
			Union(S, c1, c2);
		} else { //op == 'S'
			break;
		}
	}

	cnt = 0;
	for (int i = 0; i != N; ++i) {
		if (S[i].Parent < 0) ++cnt;
	}
	if (cnt == 1) {
		cout << "The network is connected." << endl;
	} else {
		cout << "There are " << cnt << " components." << endl;
	}
}
