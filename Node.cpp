#include "Node.hpp"

Node::Node() {
	this->state = 0; //estado não descoberto
	this->SCC = -1; //não faz parte de uma SCC inicialmente
	this->head = false;
	this->body = false;
	this->cycleStart = false;
}