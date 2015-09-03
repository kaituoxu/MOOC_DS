#include <iostream>

using namespace std;

//teacher's solution
int main()
{
	int N, K = 0, S = 0;
	int *A, *v;

	cin >> N;
	A = (int *)malloc(N * sizeof(int));
	v = (int *)malloc(N * sizeof(int));
	for (int i = 0; i != N; ++i) {
		cin >> A[i];
		v[i] = 0;
	}

	int next;
	for (int b = 0; b != N; ++b) {
		if (0 == v[b]) {
			v[b] = 1;
			next = A[b];
		} else {
			continue;
		}
		int cnt = 0;
		while (1) {
			if (next == b) {
				if (cnt != 0) {
					++K;
				} else {
					++S;
				}
				break;
			}
			v[next] = 1;
			next = A[next];
			++cnt;
		}
	}

	cout << (N - S + K - 2 < 0 ? 0 : N - S + K - 2) << endl;
}

//my solution

//int main()
//{
//	int N, i, j, k = 0, cnt = 0, tmp;
//	int *A;
//
//	cin >> N;
//	A = (int *)malloc(N * sizeof(int));
//	for (int i = 0; i != N; ++i) {
//		cin >> A[i];
//	}
//
//	for (i = 0; i != N; ++i) {
//		if (0 == A[i]) break;
//	}
//	while (1) {
//		for (j = 0; j != N; ++j) {
//			if (i == A[j]) break;
//		}
//
//		//swap(&A[i], &A[j]);
//		tmp = A[i];
//		A[i] = A[j];
//		A[j] = tmp;
//
//		i = j;
//
//		if (0 == A[0]) {
//			for (k = 0; k != N; ++k) {
//				if (k != A[k]) break;
//			}
//			if (k == N) {
//				break;
//			} else {
//				//swap(&A[0], &A[k])
//				tmp = A[0];
//				A[0] = A[k];
//				A[k] = tmp;
//				++cnt;
//				i = k;
//			}
//		}//if
//		++cnt;
//	}//while
//
//
//	cout << cnt << endl;
//
//}
