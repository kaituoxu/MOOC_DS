#include <iostream>
#include <queue>

using namespace std;
const int MAXSIZE = 10;
struct Graph {
	int Vertex[MAXSIZE];
	int Edges[MAXSIZE][MAXSIZE];
	int n, e;
};
bool Visited[MAXSIZE];

void ListComponents(Graph G);
void CreateGraph(Graph &G);
void DFS(Graph G, int i);
void BFS(Graph G, int V);
int FirstAdjV(Graph G, int i);
int NextAdjV(Graph G, int i, int j);

int main()
{
	Graph G;
	CreateGraph(G);
	ListComponents(G);
}

void CreateGraph(Graph &G)
{
	int N, E, a, b;
	cin >> N >> E;
	G.n = N;
	G.e = E;
	for (int i = 0; i != N; ++i) {
		G.Vertex[i] = i;
		Visited[i] = false;
		for (int j = 0; j != N; ++j) {
			G.Edges[i][j] = 0;
		}
	}
	for (int i = 0; i != E; ++i) {
		cin >> a >> b;
		G.Edges[a][b] = 1;
		G.Edges[b][a] = 1;
	}
}

void ListComponents(Graph G)
{
	for (int i = 0; i != G.n; ++i) {
		if (!Visited[G.Vertex[i]]) {
			cout << "{ ";
			DFS(G, G.Vertex[i]);
			cout << "}" << endl;
		}
	}
	for (int i = 0; i != G.n; ++i) {
		Visited[i] = false;
	}
	for (int i = 0; i != G.n; ++i) {
		if (!Visited[G.Vertex[i]]) {
			cout << "{ ";
			BFS(G, G.Vertex[i]);
			cout << "}" << endl;
		}
	}
}
void DFS(Graph G, int i)
{
	cout << G.Vertex[i] << " ";
	Visited[i] = true;
	for (int j = FirstAdjV(G, i); j != -1; j = NextAdjV(G, i, j)) {
		if (!Visited[j]) {
			DFS(G, j);
		}
	}
}
void BFS(Graph G, int i)
{
	int a;
	queue<int> Q;

	Visited[i] = true;
	cout << G.Vertex[i] << " ";
	Q.push(G.Vertex[i]);
	while (!Q.empty()) {
		a = Q.front(); Q.pop();
		for (int j = FirstAdjV(G, a); j != -1; j = NextAdjV(G, a, j)) {
			if (!Visited[j]) {
				Visited[j] = true;
				cout << G.Vertex[j] << " ";
				Q.push(j);
			}
		}
	}
}
int FirstAdjV(Graph G, int i)
{
	for (int j = 0; j != G.n; ++j) {
		if (G.Edges[i][j]) return j;
	}
	return -1;
}
int NextAdjV(Graph G, int i, int j)
{
	for (int k = j + 1; k != G.n; ++k) {
		if (G.Edges[i][k]) return k;
	}
	return -1;
}
