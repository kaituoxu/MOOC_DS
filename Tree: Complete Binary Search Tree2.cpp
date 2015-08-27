#include <iostream>
#include <algorithm>

using namespace std;
const int MAXSIZE = 1000;

void solve(int ALeft, int ARight, int ARoot, int *in, int *tree);
int GetLeftLength(int N);
void LevelOrderTraversal(int *tree, int N);

int main()
{
	int N;
	int in[MAXSIZE];
	int tree[MAXSIZE];

	cin >> N;
	for (int i = 0; i != N; ++i) {
		cin >> in[i];
	}
	//sort in[0...N-1]
	sort(in, &in[N]);

	solve(0, N - 1, 0, in, tree);
	LevelOrderTraversal(tree, N);
}

void solve(int ALeft, int ARight, int ARoot, int *in, int *tree)
{
	int n, L, LRoot, RRoot;
	n = ARight - ALeft + 1;
	if (n == 0) return;
	L = GetLeftLength(n);
	tree[ARoot] = in[ALeft + L];
	LRoot = 2 * ARoot + 1;
	RRoot = LRoot + 1;
	//cout << n << " " << L << " " << LRoot << " " << ALeft << " " << ARight << endl;
	solve(ALeft, ALeft + L - 1, LRoot, in, tree);
	solve(ALeft + L + 1, ARight, RRoot, in, tree);
}

int GetLeftLength(int N)
{
	int k;
	k = (int)log2(N + 1);
	int a = pow(2, k - 1);
	int b = N - (pow(2, k) - 1);
	int x = a < b ? a : b;
	//cout << k << " " << x << " " << N << endl;
	return x + pow(2, k - 1) - 1;
}

void LevelOrderTraversal(int *tree, int N)
{
	for (int i = 0; i != N - 1; ++i) {
		cout << tree[i] << " ";
	}
	cout << tree[N - 1] << endl;
}
