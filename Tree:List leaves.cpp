#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;

typedef int ElementType;
typedef struct TreeNode* BiTree;
struct TreeNode {
	ElementType Data;
	BiTree Left;
	BiTree Right;
};
int findRoot[10] = { 0 }; // in order to find root's number
char l[10];	//record input data
char r[10]; //record input data
int cnt = 0; // in order to print right space;

void LevelOrderCreateBiTree(BiTree &BT, char num);
void LevelOrderPrintLeaves(BiTree BT);
void PreOrderPrinLeaves(BiTree BT);

int main()
{
	//input data
	int N;
	cin >> N;
	for (int i = 0; i != N; ++i) {
		cin >> l[i] >> r[i];
		if (l[i] != '-') {
			l[i] = l[i] - '0';
			findRoot[l[i]] = 1;
		}
		if (r[i] != '-') {
			r[i] = r[i] - '0';
			findRoot[r[i]] = 1;
		}
		//in order to print right space
		if (l[i] == '-' && r[i] == '-') ++cnt;
	}
	//find root's number
	//explanation: root's number will not occur in the input.
	//e.g.: as the web shows, 3 is root, but not occurs in the input.
	int root = 0;
	for (int i = 0; i != N; ++i) {
		if (0 == findRoot[i]) {
			root = i;
			break;
		}
	}
	//create binary tree
	BiTree BT;
	LevelOrderCreateBiTree(BT, root);
	//list leaves
	LevelOrderPrintLeaves(BT);
	//debug info:
	//PreOrderPrinLeaves(BT);
	//cout << "debug info" << endl;
	return 0;
}

void LevelOrderCreateBiTree(BiTree &BT, char num)
{
	BT = (BiTree)malloc(sizeof(TreeNode));
	if (num != '-') {
		BT->Data = num;
	} else {
		//delete BT;
		free(BT);
		BT = NULL;
		return;
	}
	LevelOrderCreateBiTree(BT->Left, l[num]);
	LevelOrderCreateBiTree(BT->Right, r[num]);
}
void LevelOrderPrintLeaves(BiTree BT)
{
	BiTree T;
	queue<BiTree> Q;
	Q.push(BT);
	while (!Q.empty()) {
		T = Q.front();
		Q.pop();
		if (!T->Left && !T->Right) {
			//print right space
			--cnt;
			if (cnt) {
				cout << T->Data << " ";
			} else {
				cout << T->Data << endl;
			}
		}
		if (T->Left) Q.push(T->Left);
		if (T->Right) Q.push(T->Right);
	}
}
void PreOrderPrinLeaves(BiTree BT)
{
	if (BT) {
		cout << BT->Data << " ";
		PreOrderPrinLeaves(BT->Left);
		PreOrderPrinLeaves(BT->Right);
	}
}
