#include "Graph.h"

Graph::Graph() {
	nodes = nullptr;
}

void Graph::addNode(int value) {
	if (nodes == nullptr || value < nodes->data.value) {
		nodes = new NodeList<Node>{ Node(value), nodes };
		return;
	}
	if (nodes->data.value == value) {
		cout << "Node with such value already exists in graph" << endl;
		return;
	}
	NodeList<Node>* nodeListPointer = nodes;
	while (nodeListPointer->next != nullptr && nodeListPointer->next->data.value < value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer->next != nullptr) {
		//≈сли элемент с таким значением уже есть, то в граф нова€ вершина не добавл€етс€
		if (nodeListPointer->next->data.value != value)
			nodeListPointer->next = new NodeList<Node>{ Node(value), nodeListPointer->next };
	}
	else
		nodeListPointer->next = new NodeList<Node>{ Node(value), nullptr };
}

Node::Node(int value) {
	this->value = value;
	connectedNodes = nullptr;
}

void Graph::print() {
	if (nodes != nullptr) {
		NodeList<Node>* nodeListPointer = nodes;
		while (nodeListPointer != nullptr) {
			nodeListPointer->data.print();
			nodeListPointer = nodeListPointer->next;
		}
	}
	cout << "\n";
}

void Node::print() {
	if (connectedNodes != nullptr) {
		cout << value << " -> ";
		NodeList<Node*>* nodeListPointer = connectedNodes;
		while (nodeListPointer->next != nullptr) {
			cout << nodeListPointer->data->value << ", ";
			nodeListPointer = nodeListPointer->next;
		}
		cout << nodeListPointer->data->value << endl;
	}
	else
		cout << value << endl;
}

void Graph::addEdge(int firstNodeValue, int secondNodeValue) {
	NodeList<Node>* nodeListPointer = nodes;
	bool isFirstNodeFound = false, isSecondNodeFound = false;
	Node* firstNode = nullptr;
	Node* secondNode = nullptr;
	while (nodeListPointer != nullptr && !(isFirstNodeFound && isSecondNodeFound)) {
		//“.к. список упор€доченный, то в случае неудачи 
		//данное условие позвол€ет раньше выйти из цикла
		if (nodeListPointer->data.value > firstNodeValue && !isFirstNodeFound ||
			nodeListPointer->data.value > secondNodeValue && !isSecondNodeFound) {
			cout << "At least one node wasn't found" << endl;
			return;
		}
		if (nodeListPointer->data.value == firstNodeValue) {
			firstNode = &nodeListPointer->data;
			isFirstNodeFound = true;
		}
		if (nodeListPointer->data.value == secondNodeValue) {
			secondNode = &nodeListPointer->data;
			isSecondNodeFound = true;
		}
		nodeListPointer = nodeListPointer->next;
	}
	if (isFirstNodeFound && isSecondNodeFound) {
		firstNode->addEdgeToNode(secondNode);
		secondNode->addEdgeToNode(firstNode);
	}
	else 
		cout << "At least one node wasn't found" << endl;
}

void Node::addEdgeToNode(Node* node) {
	NodeList<Node*>* nodeListPointer = connectedNodes;
	if (nodeListPointer == nullptr || node->value < nodeListPointer->data->value) {
		connectedNodes = new NodeList<Node*>{ node, connectedNodes };
		return;
	}
	if (connectedNodes->data->value == node->value) {
		cout << "Edge to this node already exists" << endl;
		return;
	}
	while (nodeListPointer->next != nullptr && nodeListPointer->next->data->value < node->value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer->next != nullptr) {
		//≈сли дуга к этой вершине уже есть, то ничего не делаем
		if (nodeListPointer->next->data->value != node->value)
			nodeListPointer->next = new NodeList<Node*>{ node, nodeListPointer->next };
		else
			cout << "Edge to this node already exists" << endl;
	}
	else
		nodeListPointer->next = new NodeList<Node*>{ node, nullptr };
}
