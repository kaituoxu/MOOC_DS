#include <iostream>
#include <stack>
#include <string>

using namespace std;

int pre[30];
int in[30];
int post[30];

void solve(int preL, int inL, int postL, int n);

int main()
{
	int n, x, pre_idx, in_idx, i;
	stack<int> s;
	string op;

	cin >> n;
	pre_idx = in_idx = 0;
	for (int i = 0; i != 2 * n; ++i) {
		cin >> op;
		if (op == "Push") {
			cin >> x;
			pre[pre_idx++] = x;
			s.push(x);
		} else {//op == "Pop"
			in[in_idx++] = s.top();
			s.pop();
		}
	}

	solve(0, 0, 0, n);
	
	for (i = 0; i != n - 1; ++i) {
		cout << post[i] << " ";
	}
	cout << post[i] << endl;

}

//recursive solution
void solve(int preL, int inL, int postL, int n)
{
	int root, i, L, R;
	if (n == 0) return;
	if (n == 1) {
		post[postL] = pre[preL];
		return;
	}
	root = pre[preL];
	post[postL + n - 1] = root;
	for (i = 0; i != n; ++i) {
		if (in[inL + i] == root) break;
	}
	L = i;
	R = n - L - 1;
	solve(preL + 1, inL, postL, L);
	solve(preL + L + 1, inL + L + 1, postL + L, R);
}
