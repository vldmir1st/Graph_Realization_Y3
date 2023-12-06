#pragma once

#include <iostream>

struct ConnectedNodesList {
	Node* thisNode;
	Node* nextNode;
};

class Node {
	int index;
	ConnectedNodesList* firstNode;
};

class Graph {
	int counter;
	Node* nodes;
};