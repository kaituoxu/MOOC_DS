#include <iostream>
#include <cmath>

#define CUTOFF 50	//Qucik_Sort

using namespace std;

typedef int ElementType;

void Bubble_Sort(ElementType A[], int N)
{
	for (int i = 0; i != N; ++i) {
		int flag = 0;
		for (int j = 0; j != N - i - 1; ++j) {
			if (A[j] > A[j + 1]) {
				int tmp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = tmp;
				flag = 1;
			}
		}
		if (0 == flag) break;
	}
}

void Insertion_Sort(ElementType A[], int N)
{
	int p, i;
	ElementType tmp;
	for (p = 1; p != N; ++p) {
		tmp = A[p];
		for (i = p; i != 0 && A[i - 1] > tmp; --i) {
			A[i] = A[i - 1];
		}
		A[i] = tmp;
	}
}

void Shell_Sort(ElementType A[], int N)
{
	//with Sedgewick
	int j = 0;
	for (j = 0;; ++j) {
		if ((9 * pow(4, j) - 9 * pow(2, j) + 1) > N) break;
	}
	--j;
	for (; j >= 0; --j) {
		int D = 9 * pow(4, j) - 9 * pow(2, j) + 1;
		for (int p = D; p != N; ++p) {
			int tmp = A[p], i;
			for (i = p; i >= D && A[i - D] > tmp; i -= D) {
				A[i] = A[i - D];
			}
			A[i] = tmp;
		}
	}
}

void Selection_Sort(ElementType A[], int N)
{
	ElementType t;
	for (int i = 0; i != N; ++i) {
		int minPos = i;
		for (int p = i + 1; p != N; ++p) {
			if (A[p] < A[minPos]) {
				minPos = p;
			}
		}
		t = A[i];
		A[i] = A[minPos];
		A[minPos] = t;
	}
}

//MaxHeap
//Sort A[0..N-1]
void PercDown(ElementType A[], int i, int N)
{
	//find A[i]'s position
	int t = A[i], p, j;
	for (p = i; (p * 2 + 1) <= N - 1; p = j) {
		j = p * 2 + 1;
		if ((j != N - 1) && (A[j + 1] > A[j])) ++j;
		if (t >= A[j]) {// not A[p] >= A[j]
			break;
		} else {
			A[p] = A[j];
		}
	}
	A[p] = t;
}
void Heap_Sort(ElementType A[], int N)
{
	for (int i = N / 2 - 1; i >= 0; --i) {
		PercDown(A, i, N);
	}
	for (int i = N - 1; i != 0; --i) {
		int tmp = A[i];
		A[i] = A[0];
		A[0] = tmp;
		PercDown(A, 0, i);
	}
}

void Merge(ElementType A[], ElementType Tmp[], int L, int R, int RightEnd)
{
	int LeftEnd = R - 1;
	int ElementNums = RightEnd - L + 1;
	int tmp = L;

	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R]) Tmp[tmp++] = A[L++];
		else			  Tmp[tmp++] = A[R++];
	}
	while (L <= LeftEnd) {
		Tmp[tmp++] = A[L++];
	}
	while (R <= RightEnd) {
		Tmp[tmp++] = A[R++];
	}
	while (ElementNums != 0) {
		A[RightEnd] = Tmp[RightEnd];
		--RightEnd;
		--ElementNums;
	}
}
void MSort(ElementType A[], ElementType Tmp[], int N, int L, int RightEnd)
{
	int mid;
	if (L < RightEnd) {
		mid = (L + RightEnd) / 2;
		MSort(A, Tmp, N, L, mid);
		MSort(A, Tmp, N, mid + 1, RightEnd);
		Merge(A, Tmp, L, mid + 1, RightEnd);
	}
}
void Merge_Sort(ElementType A[], int N)
{
	ElementType *Tmp;
	Tmp = (ElementType *)malloc(N * sizeof(ElementType));
	if (Tmp) {
		MSort(A, Tmp, N, 0, N - 1);
		free(Tmp);
	}
}

void TwoRoadMerge_Sort(ElementType A[], int N)
{
	int i, j, p, k;
	ElementType tmp;

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
	}//for i
	//the last sort
	if (i > N) {
		for (p = 1; p < N; ++p) { //N - 1 passes
			tmp = A[p];
			for (k = p; k != 0 && A[k - 1] > tmp; --k) {
				A[k] = A[k - 1];
			}
			A[k] = tmp;
		}//for p
	}
}

ElementType Median3(ElementType A[], int l, int r)
{
	ElementType t;
	int m = (l + r) / 2;
	if (A[l] > A[m]) {
		t = A[l];
		A[l] = A[m];
		A[m] = t;
	}
	if (A[l] > A[r]) {
		t = A[l];
		A[l] = A[r];
		A[r] = t;
	}
	if (A[m] > A[r]) {
		t = A[m];
		A[m] = A[r];
		A[r] = t;
	}
	t = A[m];
	A[m] = A[r - 1];
	A[r - 1] = t;
	return A[r - 1];
}
void QSort(ElementType A[], int l, int r)
{
	if (CUTOFF <= r - l) {
		//Median3 is better than A[l]
		ElementType t = Median3(A, l, r), tmp;
		//just sort A[l+1..r-2]
		int i = l, j = r - 1;

		while (1) {
			while (A[++i] < t);	//must <= but not <
			while (A[--j] > t);	//must >= but not >
			if (i < j) {
				tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
			} else {
				break;
			}
		}
		tmp = A[i];
		A[i] = A[r - 1];
		A[r - 1] = tmp;
		QSort(A, l, i - 1);
		QSort(A, i + 1, r);
	} else {
		Insertion_Sort(A + l, r - l + 1);
	}
}
void Quick_Sort(ElementType A[], int N)
{
	QSort(A, 0, N - 1);
}


int main()
{
	ElementType *A;
	int N;

	//input
	cin >> N;
	A = (ElementType *)malloc(N*sizeof(ElementType));
	for (int i = 0; i != N; ++i) {
		cin >> A[i];
	}

	//sort A[0..N-1]
	//Bubble_Sort(A, N);
	//Insertion_Sort(A, N);
	//Shell_Sort(A, N);
	//Selection_Sort(A, N);
	//Heap_Sort(A, N);
	//Merge_Sort(A, N);
	//TwoRoadMerge_Sort(A, N);
	Quick_Sort(A, N);

	//output
	for (int i = 0; i != N - 1; ++i) {
		cout << A[i] << " ";
	}
	cout << A[N-1] << endl;
	
	free(A);
}
