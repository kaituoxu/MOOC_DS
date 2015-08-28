//adjacency list version
//this will not lead to overtime
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXSIZE = 10000;
struct EdgeNode {
	int AdjV;
	EdgeNode *Next;
};
struct VertexNode {
	EdgeNode *FirstEdge;
};
typedef VertexNode AdjList[MAXSIZE];
struct Graph {
	AdjList adjlist;
	int N, M;
};
bool Visited[MAXSIZE];

void Create(Graph &G);
int BFS(Graph G, int i);
void SDS(Graph G);
//int FirstAdjV(Graph G, int i);
//int NextAdjV(Graph G, int i, int k);

int main()
{
	Graph G;
	Create(G);
	SDS(G);
}

void Create(Graph &G)
{
	int N, M, x, y;
	EdgeNode *edge1, *edge2;

	cin >> N >> M;
	G.N = N;
	G.M = M;
	for (int i = 0; i != N; ++i) {
		G.adjlist[i].FirstEdge = nullptr;
	}
	for (int i = 0; i != M; ++i) {
		cin >> x >> y;
		--x; --y;
		edge1 = (EdgeNode *)malloc(sizeof(EdgeNode));
		edge1->AdjV = y;
		edge1->Next = G.adjlist[x].FirstEdge;
		G.adjlist[x].FirstEdge = edge1;

		edge2 = (EdgeNode *)malloc(sizeof(EdgeNode));
		edge2->AdjV = x;
		edge2->Next = G.adjlist[y].FirstEdge;
		G.adjlist[y].FirstEdge = edge2;
	}
}
void SDS(Graph G)
{
	int cnt;
	for (int i = 0; i != G.N; ++i) {
		cnt = BFS(G, i);
		printf("%d: %.2f%%\n", i + 1, (double)cnt / G.N*100.0);
	}
}
int BFS(Graph G, int v)
{
	queue<int> Q;
	int i, cnt, level, last, tail;

	for (int k = 0; k != G.N; ++k) {
		Visited[k] = false;
	}

	Visited[v] = true;
	cnt = 1;
	level = 0;
	last = v;
	tail = v;
	Q.push(v);
	while (!Q.empty()) {
		i = Q.front(); Q.pop();
		for (EdgeNode *e = G.adjlist[i].FirstEdge; e != nullptr; e = e->Next) {
			int j = e->AdjV;
			if (!Visited[j]) {
				Visited[j] = true;
				++cnt;
				tail = j;
				Q.push(j);
			}
		}
		//this loop will lead to overtime
		//for (int j = FirstAdjV(G, i); j != -1; j = NextAdjV(G, i, j)) {
		//	if (!Visited[j]) {
		//		Visited[j] = true;
		//		++cnt;
		//		tail = j;
		//		Q.push(j);
		//	}
		//}
		if (last == i) {
			++level;
			last = tail;
		}
		if (6 == level) break;
	}
	return cnt;
}
//int FirstAdjV(Graph G, int i)
//{
//	if (G.adjlist[i].FirstEdge != nullptr) {
//		return G.adjlist[i].FirstEdge->AdjV;
//	} else {
//		return -1;
//	}
//}
//int NextAdjV(Graph G, int i, int j)
//{
//	EdgeNode *t = G.adjlist[i].FirstEdge;
//	while (t != nullptr) {
//		if (t->AdjV == j) {
//			if (t->Next != nullptr) {
//				return t->Next->AdjV;
//			} else {
//				return -1;
//			}
//		}
//		t = t->Next;
//	}
//	return -1;
//}



//adjacency matrix version
//This will lead to overtime.

//#include <iostream>
//#include <queue>
//#include <cstdio>
//
//using namespace std;
//
//const int MAXSIZE = 1000;
//struct Graph {
//	int N, M;
//	int E[MAXSIZE][MAXSIZE];
//};
//bool Visited[MAXSIZE];
//
//void Create(Graph &G);
//int BFS(Graph G, int i);
//void SDS(Graph G);
//int FirstAdjV(Graph G, int i);
//int NextAdjV(Graph G, int i, int k);
//
//int main()
//{
//	Graph G;
//	Create(G);
//	SDS(G);
//}
//
//void Create(Graph &G)
//{
//	int N, M, x, y;
//
//	cin >> N >> M;
//	G.N = N;
//	G.M = M;
//	for (int i = 0; i != N; ++i) {
//		for (int j = 0; j != N; ++j) {
//			G.E[i][j] = 0;
//		}
//	}
//	for (int i = 0; i != M; ++i) {
//		cin >> x >> y;
//		G.E[x-1][y-1] = 1;//Ps here
//		G.E[y-1][x-1] = 1;//Ps here
//	}
//}
//void SDS(Graph G)
//{
//	int cnt;
//	for (int i = 0; i != G.N; ++i) {
//		cnt = BFS(G, i);
//		printf("%d: %.2f%%\n", i + 1, (double)cnt / G.N*100.0);
//	}
//}
//int BFS(Graph G, int v)
//{
//	queue<int> Q;
//	int i, cnt, level, last, tail;
//	
//	for (int k = 0; k != G.N; ++k) {
//		Visited[k] = false;
//	}
//
//	Visited[v] = true;
//	cnt = 1;
//	level = 0;
//	last = v;
//	tail = v;
//	Q.push(v);
//	while (!Q.empty()) {
//		i = Q.front(); Q.pop();
//		for (int j = FirstAdjV(G, i); j != -1; j = NextAdjV(G, i, j)) {
//			if (!Visited[j]) {
//				Visited[j] = true;
//				++cnt;
//				tail = j;
//				Q.push(j);
//			}
//		}
//		if (last == i) {
//			++level;
//			last = tail;
//		}
//		if (6 == level) break;
//	}
//	return cnt;
//}
//
//int FirstAdjV(Graph G, int i)
//{
//	for (int j = 0; j != G.N; ++j) {
//		if (G.E[i][j]) return j;
//	}
//	return -1;
//}
//int NextAdjV(Graph G, int i, int k)
//{
//	for (int j = k + 1; j != G.N; ++j) {
//		if (G.E[i][j]) return j;
//	}
//	return -1;
//}
