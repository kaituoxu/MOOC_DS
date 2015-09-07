#include <iostream>
#include <queue>

using namespace std;

//Graph defination
struct EdgeNode {
	int AdjV;
	EdgeNode *Next;
};
struct VNode {
	int Element;
	int InDegree;
	EdgeNode *FirstEdge;
};
typedef VNode *AdjList;
struct AdjGraph {
	AdjList adjList;
	int N;
};

//HashTable Defination

struct HashTbl {
	int *Elements;
	int TableSize;
};
typedef HashTbl * HashTable;

AdjGraph Hash2Graph(HashTable H);
void TopSort(AdjGraph G);

int main()
{
	HashTable H;
	AdjGraph G;
	int N;

	//Create hash table
	H = new HashTbl;
	cin >> N;
	H->Elements = new int[N];
	H->TableSize = N;
	for (int i = 0; i != N; ++i) {
		//H->Elements[i] equal to -1 means this position is empty.
		cin >> H->Elements[i];
	}

	//Build AdjGraph to topsort, given hash table.
	G = Hash2Graph(H);

	//output topsort sequence
	TopSort(G);

	//free memory
	delete []H->Elements;
	delete H;
	delete []G.adjList;
}

AdjGraph Hash2Graph(HashTable H)
{
	AdjGraph G;

	//Initialize G
	G.adjList = new VNode[H->TableSize];
	G.N = H->TableSize;
	for (int i = 0; i != G.N; ++i) {
		G.adjList[i].Element = H->Elements[i];
		G.adjList[i].InDegree = 0;
		G.adjList[i].FirstEdge = nullptr;
	}

	//Bulid Graph
	int N = H->TableSize;
	for (int i = 0; i != N && H->Elements[i] != -1; ++i) {
		if (H->Elements[i] % N == i) {
			continue;
		} else {
			int pos = H->Elements[i] % N;
			while (pos != i) {
				// add edge pos->i, using head insert method
				EdgeNode *p = new EdgeNode;
				p->AdjV = i;
				p->Next = G.adjList[pos].FirstEdge;
				G.adjList[pos].FirstEdge = p;

				++(G.adjList[i].InDegree);

				//linear probing to solve collision
				++pos;
				if (pos >= N) pos -= N;
			}//while
		}//else
	}//for

	return G;
}

void TopSort(AdjGraph G)
{
	int v, cnt = 0;
	int validNum = 0;

	//count the valid num
	for (int i = 0; i != G.N; ++i) {
		if (G.adjList[i].Element != -1) {
			++validNum;
		}
	}

	//SortSeq is a prior queue, the less value is, the higher prior is.
	//allocate memory and initialize SortSeq
	int *SortSeq;
	int beg, end;	//SortSeq[beg, end-1] is valid
	SortSeq = new int[G.N];
	for (int i = 0; i != G.N; ++i) {
		SortSeq[i] = -1;
	}
	beg = 0; end = 0;


	for (int i = 0; i != G.N; ++i) {
		if (G.adjList[i].InDegree == 0 && G.adjList[i].Element != -1) {
			//Insert SortSeq using insertion sort
			int j, tmp = G.adjList[i].Element;
			for (j = end; j > beg && SortSeq[j - 1] > tmp; --j) {
				SortSeq[j] = SortSeq[j - 1];
			}
			SortSeq[j] = tmp;
			++end;
		}
	}

	while (end - beg > 0) {
		v = SortSeq[beg];
		++beg;//should be ++beg
		++cnt;
		//control output format
		if (cnt < validNum) {	//ps here, maybe not G.N
			cout << v << " ";
		} else {//cnt == G.N
			cout << v << endl;
		}


		for (int i = 0; i != G.N; ++i) {
			if (G.adjList[i].Element == v) {
				v = i;
				break;
			}
		}
		//each of v's adjancy vertex's indegree substract 1
		for (EdgeNode *p = G.adjList[v].FirstEdge; p; p = p->Next) {
			int i = p->AdjV;
			--(G.adjList[i].InDegree);
			if (G.adjList[i].InDegree == 0) {
				//Insert SortSeq using insertion sort
				int j, tmp = G.adjList[i].Element;
				for (j = end; j > beg && SortSeq[j - 1] > tmp; --j) {
					SortSeq[j] = SortSeq[j - 1];
				}
				SortSeq[j] = tmp;
				++end;
			}
		}//for p
	}//while
}
