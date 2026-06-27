#include "Graph.hpp"

int main() {
	int n;
	scanf_s("%d", &n);
	Graph G(n);

	int v;
	for (int u = 0;u < n; u++) {
		scanf_s("%d", &v);
		G.addEdge(u, v);
	}
	G.DFS();
	G.mergeSCC();

	return 0;
}