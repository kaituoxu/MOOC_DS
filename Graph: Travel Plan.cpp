//PAT: travel plan

#include <iostream>
#define INF 65535

using namespace std;

const int MAXSIZE = 100;
struct MGraph {
	int Edges[MAXSIZE][MAXSIZE];
	int Costs[MAXSIZE][MAXSIZE];
	int N, E;
};


void CreateMGraph(MGraph &G, int &s, int &d)
{
	int x, y, len, cost;
	cin >> G.N >> G.E >> s >> d;
	for (int i = 0; i != G.N; ++i) {
		for (int j = 0; j != G.N; ++j) {
			if (i == j) {
				G.Edges[i][j] = 0;
				G.Costs[i][j] = 0;
			} else {
				G.Edges[i][j] = INF;
				G.Costs[i][j] = INF;
			}//here
		}
	}
	for (int i = 0; i != G.E; ++i) {
		cin >> x >> y >> len >> cost;
		G.Edges[x][y] = len;
		G.Edges[y][x] = len;
		G.Costs[x][y] = cost;
		G.Costs[y][x] = cost;//here
	}
}
void Dijkstra(MGraph G, int v, int dist[], int path[], int money[])
{
	int set[MAXSIZE];
	// Initialize dist[], path[], set[]
	for (int i = 0; i != G.N; ++i) {
		dist[i] = G.Edges[v][i];
		money[i] = G.Costs[v][i];	//here
		set[i] = 0;
		if (G.Edges[v][i] < INF) {
			path[i] = v;
		} else {
			path[i] = -1;
		}
	}
	set[v] = 1; path[v] = -1;
	//key operation
	for (int i = 0; i != G.N; ++i) {
		//find vertex u whose distance is shortest 
		int u, min = INF;
		for (int j = 0; j != G.N; ++j) {
			if (set[j] == 0 && dist[j] < min) {
				u = j;
				min = dist[u];
			}
		}
		set[u] = 1;
		//add u to set[], refresh dist[]
		for (int j = 0; j != G.N; ++j) {
			if (G.Edges[u][j] != INF) {
				if (set[j] == 0) {
					if (min + G.Edges[u][j] < dist[j]) {	
						dist[j] = min + G.Edges[u][j];	//min = dist[u];
						path[j] = u;
						money[j] = money[u] + G.Costs[u][j];
					} else if (min + G.Edges[u][j] == dist[j]) {	//here
						int nowCost = money[u] + G.Costs[u][j];
						if (nowCost < money[j]) {
							path[j] = u;
							money[j] = nowCost;
						}
					}
				}
			}
		} //for j
	} //for i

}
void PrintPath(MGraph G, int path[], int money[], int a)
{
	int stack[MAXSIZE], top = -1;
	int t = a;
	while (path[a] != -1) {
		stack[++top] = a;
		a = path[a];
	}
	cout << top + 2 << " " << money[t] << endl;
}

int main()
{
	MGraph G;
	int s, d;//source, destination
	int dist[MAXSIZE], path[MAXSIZE], money[MAXSIZE];
	CreateMGraph(G, s, d);
	Dijkstra(G, s, dist, path, money);
	PrintPath(G, path, money, d);
}
