#include "Graph.hpp"

Graph::Graph(int V) {
	this->adj.resize(V);
	this->nodes.resize(V);
	for (int i = 0; i < V; i++) {
		this->nodes[i] = new Node();
	}
	this->SCCs.resize(0);
}

void Graph::addEdge(int u, int v) {
	adj[u] = v;
}

void Graph::DFS() {
	for (int i = 0; i < this->nodes.size(); i++) {
		if (this->nodes[i]->state == 0) {
			this->DFS_Visit(i, i);
		}
	}
}	

int Graph::DFS_Visit(int u, int origin) {
	this->nodes[u]->state = 1;
	int SCC_idx;

	int next = adj[u];
	if (this->nodes[next - 1]->state == 0) {
		SCC_idx = DFS_Visit(next - 1, origin);
	}
	else if (this->nodes[next - 1]->state == 1) { //encontrou ciclo. Determina o SCC ao qual pertencerá
		SCC_idx = SCCs.size();
		this->SCCs.resize(this->SCCs.size() + 1);
		this->nodes[next - 1]->cycleStart = true;
	}
	else if (this->nodes[next - 1]->state == 2) { //encontrou vértice já visitado.
		SCC_idx = this->nodes[next - 1]->SCC;
		if (this->nodes[next - 1]->head) {
			this->nodes[next - 1]->head = false;
			this->nodes[next - 1]->body = true;
		}
	}


	this->nodes[u]->state = 2; //marca como visitado
	this->SCCs[SCC_idx].push_back(u);
	this->nodes[u]->SCC = SCC_idx;

	if (u == origin) {
		if (this->nodes[u]->cycleStart) { //impede que a origem, se membro do ciclo, seja head.
			this->nodes[u]->body = true;
		}
		else {
			this->nodes[u]->head = true; //origem membro da árvore é head.
		}
	}

	else {
		this->nodes[u]->body = true; //todo vértice sem ser a origem é body.
	}

	return SCC_idx;
}

void Graph::mergeSCC() {
	std::vector<std::pair<int, int>> edgesAdded;

	for (int i = 0; i < this->SCCs.size() - 1; i++) {
		int u, v;
		bool headFound = false;
		for (int j = 0; j < this->SCCs[i + 1].size(); j++) { //liga um membro do ciclo i às heads das árvores que chegam no ciclo i + 1
			v = SCCs[i + 1][j];
			if (this->nodes[v]->head) {
				headFound = true;
				u = SCCs[i][0]; //primeiro membro do SCC e membro do ciclo 
				addEdge(u, v);
				edgesAdded.emplace_back(u, v);
			}
		}
		if (!headFound) { //se não encontrou head, é porque encontrou um ciclo sozinho (sem árvores que levam a ele). Liga um membro do ciclo anterior ao próximo ciclo diretamente.
			u = SCCs[i][0];
			v = SCCs[i + 1][0];
			addEdge(u, v);
			edgesAdded.emplace_back(u, v);
		}
	}

	int n = this->SCCs.size(); //repete o processo anterior, mas da enésima SCC para a primeira.
	int u, v;
	bool headFound = false;
	if (n > 1) { 
		for (int j = 0; j < this->SCCs[0].size(); j++) {
			v = SCCs[0][j];
			if (this->nodes[v]->head) {
				headFound = true;
				u = SCCs[n - 1][0];
				addEdge(u, v);
				edgesAdded.emplace_back(u, v);
			}
		}
		if (!headFound) {
			v = SCCs[0][0];
			u = SCCs[n - 1][0];
			addEdge(u, v);
			edgesAdded.emplace_back(u, v);
		}
	}
	else { //no caso de haver somente 1 SCC não é feito nada caso não haja head.
		for (int j = 0; j < this->SCCs[0].size(); j++) {
			v = SCCs[0][j];
			if (this->nodes[v]->head) {
				headFound = true;
				u = SCCs[n - 1][0];
				addEdge(u, v);
				edgesAdded.emplace_back(u, v);
			}
		}
	}

	this->printNewEdges(&edgesAdded);

}

void Graph::printNewEdges(std::vector<std::pair<int, int>>* newEdges) {
	printf("%zu\n", newEdges->size());
	for (int i = 0; i < newEdges->size(); i++) {
		printf("%d %d\n", (*newEdges)[i].first + 1, (*newEdges)[i].second + 1);
	}
}