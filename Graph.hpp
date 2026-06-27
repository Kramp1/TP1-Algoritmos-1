#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "vector"
#include "forward_list"
#include <cstdio>

class Graph {
public:
	std::vector<int> adj; //vetor que armazena o id do vértice adjacente
	std::vector<Node*> nodes; //vetor de vértices
	std::vector<std::vector<int>> SCCs; //matriz com cada estrutura ciclo-árvore. Tecnicamente não são SCCs, pois do ciclo não se chega na árvore, mas foi o nome que usei.

	Graph(int V);
	void addEdge(int u, int v);
	void DFS();
	int DFS_Visit(int u, int origin);
	void mergeSCC();
	void printNewEdges(std::vector<std::pair<int, int>>* newEdges);
};

#endif
