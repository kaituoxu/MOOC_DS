//ps: The central island is a disk centered at (0,0) with the diameter of 15
#include <iostream>
#include <cmath>

#define YES 1
#define NO  0

using namespace std;

const int MAXSIZE = 100;
struct Vertex {
	int x, y;
};
struct Graph {
	Vertex V[MAXSIZE];
	int N;
};
bool Visited[MAXSIZE];
int D = 0;

void Create(Graph &G);
void save007(Graph G);
bool jump(Vertex V, Vertex W);
bool IsSafe(Vertex V);
int DFS(Graph G, int i);
bool FirstJump(Vertex V);//ps here

int main()
{
	Graph G;
	Create(G);
	save007(G);
}

void Create(Graph &G)
{
	int n;

	cin >> n >> D;
	G.N = n;
	for (int i = 0; i != n; ++i) {
		cin >> G.V[i].x >> G.V[i].y;
		Visited[i] = false;
	}
}
void save007(Graph G)
{
	int answer = NO;
	for (int i = 0; i != G.N; ++i) {
		if (!Visited[i] && FirstJump(G.V[i])) {
			answer = DFS(G, i);
			if (answer == YES) break;
		}
	}
	if (answer == YES) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
}
bool FirstJump(Vertex V)
{
	double dis;
	dis = pow(V.x, 2) + pow(V.y, 2);
	dis = sqrt(dis);
	if (dis <= D+7.5) {//ps +7.5
		return true;
	} else {
		return false;
	}
}
int DFS(Graph G, int i)
{
	int answer = NO;
	Visited[i] = true;
	if (IsSafe(G.V[i])) {
		answer = YES;
	} else {
		for (int j = 0; j != G.N; ++j) {
			if (!Visited[j] && jump(G.V[i], G.V[j])) {
				answer = DFS(G, j);
				if (answer == YES) break;
			}
		}
	}
	return answer;
}
bool IsSafe(Vertex V)
{
	if ((50 - abs(V.x) <= D) || (50 - abs(V.y) <= D)) {
		return true;
	} else {
		return false;
	}
}
bool jump(Vertex V, Vertex W)
{
	double dis;
	dis = pow(V.x - W.x, 2) + pow(V.y - W.y, 2);
	dis = sqrt(dis);
	if (dis <= D) {
		return true;
	} else {
		return false;
	}
}
