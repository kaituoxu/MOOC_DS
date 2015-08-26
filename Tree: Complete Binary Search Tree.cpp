#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdlib>

const int MAXSIZE = 1001;
using namespace std;

typedef struct TreeNode* BinTree;
typedef int ElementType;
struct TreeNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};
int seq[MAXSIZE];

BinTree Create(BinTree T, int L, int R);
void LevelOrderTraversal(BinTree T, int N);

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i != N; ++i) {
		cin >> seq[i + 1];
	}
	//sort seq[1...N]
	sort(&seq[1], &seq[N + 1]);

	//for (int i = 0; i != N; ++i) {
	//	cout << seq[i + 1] << " ";
	//}
	//cout << endl;

	BinTree T = nullptr;
	T = Create(T, 1, N);
	LevelOrderTraversal(T, N);
}

BinTree Create(BinTree T, int L, int R)
{
	//cout << L << " " << R << endl;
	
	if (L == R && !T) {
		T = (BinTree)malloc(sizeof(TreeNode));
		T->Data = seq[L];
		T->Left = T->Right = nullptr;
		return T;
	}

	int N = R - L + 1;
	int k;
	for (k = 0; ; ++k) {
		if (pow(2, k) - 1 < N && N <= pow(2, k + 1) - 1) break;
	}
	int a = pow(2, k - 1);
	int b = N - (pow(2, k) - 1);
	int x = a < b ? a : b;
	int root = x + (pow(2, k) - 1 - 1) / 2 + 1 + L - 1;

	//cout << k << " " << a << " " << b << " " << x << " " << root << endl;;

	if (!T) {
		T = (BinTree)malloc(sizeof(TreeNode));
		T->Data = seq[root];
		T->Left = T->Right = nullptr;
	}
	T->Left = Create(T->Left, L, root - 1);
	if (root + 1 <= R) {
		T->Right = Create(T->Right, root + 1, R);
	}
	return T;
}

void LevelOrderTraversal(BinTree T, int N)
{
	BinTree Tmp;
	queue<BinTree> Q;
	if (!T) return;
	Q.push(T);
	while (!Q.empty()) {
		Tmp = Q.front(); Q.pop();
		if (--N) {
			cout << Tmp->Data << " ";
		} else {
			cout << Tmp->Data << endl;
		}
		if (Tmp->Left) Q.push(Tmp->Left);
		if (Tmp->Right) Q.push(Tmp->Right);
	}
}
