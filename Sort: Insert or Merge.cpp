#include <iostream>
#include <cmath>

using namespace std;

typedef int ElementType;
bool Is_Insertion_Sort(ElementType A[], ElementType PR[], int N)
{
	int p, i, flag = 0;
	ElementType tmp;
	for (p = 1; p != N; ++p) {
		tmp = A[p];
		for (i = p; i != 0 && A[i - 1] > tmp; --i) {
			A[i] = A[i - 1];
		}
		A[i] = tmp;

		//Judge step
		//one more iterations
		if (1 == flag) {
			return true;
		}
		int j;
		for (j = 0; j != N; ++j) {
			if (A[j] != PR[j]) {
				break;
			}
		}
		if (N == j) {
			flag = 1;
		}
	}
	if (1 == flag) return true;
	else return false;
}

//2 road Merge Sort + judge
void Merge2Road(ElementType A[], ElementType PR[], int N)
{
	int i, j, p, tmp, k, m, flag = 0;
	for (i = 1; i <= N; i *= 2) {
		int times = N / i;
		for (j = 0; j < times; ++j) {
			//Insert_Sort[i*j, i*j+i-1]
			int l = i * j;
			int r = l + i - 1;
			for (p = l + 1; p <= r; ++p) { //i - 1 passes
				tmp = A[p];
				for (k = p; k != l && A[k - 1] > tmp; --k) {
					A[k] = A[k - 1];
				}
				A[k] = tmp;
			}//for p
		}//for j
		if (times * i < N) {
			int l = times * i;
			int r = N - 1;
			for (p = l + 1; p <= r; ++p) { //i - 1 passes
				tmp = A[p];
				for (k = p; k != l && A[k - 1] > tmp; --k) {
					A[k] = A[k - 1];
				}
				A[k] = tmp;
			}//for p
		}

		if (1 == flag) {
			return ;
		}

		if (2*i > N) {
			for (p = 1; p < N; ++p) { //N - 1 passes
				tmp = A[p];
				for (k = p; k != 0 && A[k - 1] > tmp; --k) {
					A[k] = A[k - 1];
				}
				A[k] = tmp;
			}//for p
		}

		//Judge Step
		for (m = 0; m != N; ++m) {
			if (A[m] != PR[m])
				break;
		}
		if (m == N) {
			flag = 1;
		}
	}//for i
	return;
}
int main()
{
	ElementType *A1, *A2, *PartResult;
	int N;

	//input
	cin >> N;
	A1 = (ElementType *)malloc(N*sizeof(ElementType));
	A2 = (ElementType *)malloc(N*sizeof(ElementType));
	PartResult = (ElementType *)malloc(N*sizeof(ElementType));
	for (int i = 0; i != N; ++i) {
		cin >> A1[i];
		A2[i] = A1[i];
	}
	for (int i = 0; i != N; ++i) {
		cin >> PartResult[i];
	}


	if (Is_Insertion_Sort(A1, PartResult, N)) {
		cout << "Insertion Sort" << endl;
		for (int i = 0; i != N - 1; ++i) {
			cout << A1[i] << " ";
		}
		cout << A1[N - 1] << endl;
	} else {
		Merge2Road(A2, PartResult, N);
		cout << "Merge Sort" << endl;
		for (int i = 0; i != N - 1; ++i) {
			cout << A2[i] << " ";
		}
		cout << A2[N - 1] << endl;
	}

	free(A1);
	free(A2);
}
