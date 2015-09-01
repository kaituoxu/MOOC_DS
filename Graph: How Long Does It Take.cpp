#include <iostream>
#include <queue>

#define INF 65535
using namespace std;

const int MAXSIZE = 100;
struct MGraph {
	int Edges[MAXSIZE][MAXSIZE];
	int InD[MAXSIZE];//in-degree
	int Early[MAXSIZE];
	int N, E;
};

void CreateGraph(MGraph &G)
{
	int x, y, t;
	cin >> G.N >> G.E;
	for (int i = 0; i != G.N; ++i) {
		G.InD[i] = 0;
		for (int j = 0; j != G.N; ++j) {
			G.Edges[i][j] = INF;
		}
	}
	for (int i = 0; i != G.E; ++i) {
		cin >> x >> y >> t;
		G.Edges[x][y] = t;
		++(G.InD[y]);
	}
}

int FirstAdjV(MGraph G, int i)
{
	for (int j = 0; j != G.N; ++j) {
		if (G.Edges[i][j] != INF) {
			return j;
		}
	}
	return -1;
}
int NextAdjV(MGraph G, int p, int v)
{
	for (int j = p + 1; j != G.N; ++j) {
		if (G.Edges[v][j] != INF) {
			return j;
		}
	}
	return -1;
}

//topSort
void CriticalPath(MGraph &G)
{
	int v, cnt = 0;
	queue<int> Q;

	//only one vertex's in-degree is 0
	for (int i = 0; i != G.N; ++i) {
		if (0 == G.InD[i]) {
			Q.push(i);
			G.Early[i] = 0;
		}
	}
	// key operation
	while (!Q.empty()) {
		v = Q.front(); Q.pop();
		++cnt;
		for (int p = FirstAdjV(G, v); p != -1; p = NextAdjV(G, p, v)) {
			--(G.InD[p]);
			if (0 == G.InD[p]) {
				Q.push(p);

				int max = 0;
				for (int i = 0; i != G.N; ++i) {
					if (G.Edges[i][p] != INF && G.Early[i] + G.Edges[i][p] > max) {//edge from i to p
						max = G.Early[i] + G.Edges[i][p];
					}
				}
				G.Early[p] = max;
			}
		}
	}
	if (cnt != G.N) {
		cout << "Impossible" << endl;
	} else {
		cout << G.Early[v] << endl;
	}
}

int main()
{
	MGraph G;
	CreateGraph(G);
	CriticalPath(G);
}
