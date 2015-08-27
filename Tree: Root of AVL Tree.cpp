#include <iostream>
#include <cstdlib>
using namespace std;
typedef struct avltreenode* avltree;
typedef int elementtype;
struct avltreenode {
	elementtype data;
	avltree left;
	avltree right;
	int height;
};

avltree avl_insertion(elementtype x, avltree t);
avltree singleleftrotation(avltree a);
avltree singlerightrotation(avltree a);
avltree doubleleftrightrotation(avltree a);
avltree doublerightleftrotation(avltree a);
int getheight(avltree t);
int max(int a, int b);

int main()
{
	int n;
	elementtype x;
	avltree t = nullptr;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		cin >> x;
		t = avl_insertion(x, t);
	}
	cout << t->data << endl;
}


avltree avl_insertion(elementtype x, avltree t)
{
	if (!t) {
		t = (avltree)malloc(sizeof(avltreenode));
		t->data = x;
		t->height = 0;
		t->left = t->right = nullptr;
	} else if (x < t->data) {
		t->left = avl_insertion(x, t->left);
		if (getheight(t->left) - getheight(t->right) == 2) {
			if (x < t->left->data) {
				t = singleleftrotation(t);
			} else {
				t = doubleleftrightrotation(t);
			}
		}
	} else if (x > t->data) {
		t->right = avl_insertion(x, t->right);
		if (getheight(t->left) - getheight(t->right) == -2) {
			if (x > t->right->data) {
				t = singlerightrotation(t);
			} else {
				t = doublerightleftrotation(t);
			}
		}
	}
	t->height = max(getheight(t->left), getheight(t->right)) + 1;
	return t;
}
avltree singleleftrotation(avltree a)
{
	avltree b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = max(getheight(a->left), getheight(a->right)) + 1;
	b->height = max(getheight(b->left), a->height) + 1;
	return b;
}
avltree singlerightrotation(avltree a)
{
	avltree b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = max(getheight(a->left), getheight(a->right)) + 1;
	b->height = max(a->height, getheight(b->right)) + 1;
	return b;
}
avltree doubleleftrightrotation(avltree a)
{
	a->left = singlerightrotation(a->left);
	return singleleftrotation(a);
}
avltree doublerightleftrotation(avltree a)
{
	a->right = singleleftrotation(a->right);
	return singlerightrotation(a);
}
int getheight(avltree t)
{
	int hl, hr, maxh;
	if (t) {
		hl = getheight(t->left);
		hr = getheight(t->right);
		maxh = (hl > hr) ? hl : hr;
		return maxh + 1;
	} else {
		return 0;
	}
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}
