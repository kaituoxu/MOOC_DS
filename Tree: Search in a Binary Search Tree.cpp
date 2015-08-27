#include <iostream>
#include <cstdlib>

const int MAXSIZE = 100;
using namespace std;

typedef struct TreeNode* BinTree;
typedef int ElementType;
struct TreeNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};
int seq[MAXSIZE];
int test[MAXSIZE];
int idx = 0;

BinTree Find(ElementType, BinTree);
BinTree Insert(ElementType, BinTree);

int main()
{
	int N, M;
	
	cin >> N >> M;
	for (int j = 0; j != N; ++j) {
		BinTree BST = nullptr;
		idx = 0;
		for (int i = 0; i != M; ++i) {
			cin >> seq[i];
			BST = Insert(seq[i], BST);
		}
		Find(seq[M - 1], BST);
		int i;
		for (i = 0; i != M; ++i) {
			if (seq[i] != test[i]) break;
			//cout << test[i] << " ";
		}
		//cout << endl;
		if (i == M) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}

}

BinTree Find(ElementType X, BinTree BST)
{
	while (BST) {
		test[idx++] = BST->Data;
		if (X < BST->Data) {
			BST = BST->Left;
		} else if (X > BST->Data) {
			BST = BST->Right;
		} else {
			return BST;
		}
	}
	return nullptr;
}
BinTree Insert(ElementType X, BinTree BST)
{
	if (!BST) {
		BST = (BinTree)malloc(sizeof(TreeNode));
		BST->Data = X;
		BST->Left = BST->Right = nullptr;
	} else {
		if (X > BST->Data) {
			BST->Right = Insert(X, BST->Right);
		} else if (X < BST->Data) {
			BST->Left = Insert(X, BST->Left);
		} 
	}
	return BST;
}
