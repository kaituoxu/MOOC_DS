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
void PercDown(ElementType A[], int i, int N)
{
	int p, j;
	ElementType tmp = A[i];
	for (p = i; p * 2 + 1 <= N - 1; p = j) {
		j = p * 2 + 1;
		if (j != N - 1 && A[j] < A[j + 1]) ++j;
		if (tmp >= A[j]) {
			break;
		} else {
			A[p] = A[j];
		}
	}
	A[p] = tmp;
}
void Heap_Sort(ElementType A[], ElementType PR[], int N)
{
	int j, flag = 0;
	for (int i = N / 2 - 1; i >= 0; --i) {	//ps i >= 0
		PercDown(A, i, N);
	}
	for (int i = N - 1; i != 0; --i) {	//N-1 passes
		int tmp = A[0];
		A[0] = A[i];
		A[i] = tmp;
		PercDown(A, 0, i);
		//Judge
		if (1 == flag)
			return;
		for (j = 0; j != N; ++j) {
			if (A[j] != PR[j]) {
				break;
			}
		}
		if (N == j) {
			flag = 1;
		}
	}
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
		Heap_Sort(A2, PartResult, N);
		cout << "Heap Sort" << endl;
		for (int i = 0; i != N - 1; ++i) {
			cout << A2[i] << " ";
		}
		cout << A2[N - 1] << endl;
	}
	
	free(A1);
	free(A2);
}
