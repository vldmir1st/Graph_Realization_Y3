#include "Graph.h"

Graph::Graph() {
	nodes = nullptr;
}

void Graph::addNode(int value) {
	//���������� ������� � ������ ����
	if (nodes == nullptr || value < nodes->data.value) {
		nodes = new NodeList<Node>{ Node(value), nodes };
		return;
	}
	//���� ������ ������� ����� �������� value, �� ������ �� ����������
	if (nodes->data.value == value) {
		cout << "Node with such value already exists in graph" << endl;
		return;
	}
	NodeList<Node>* nodeListPointer = nodes;
	//���� �� ����� ��� ���� �� �������� ������� ������ value 
	while (nodeListPointer->next != nullptr && nodeListPointer->next->data.value < value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer->next != nullptr) {
		//���� ������� � ����� ��������� ��� ����, �� � ���� ����� ������� �� �����������
		if (nodeListPointer->next->data.value != value)
			nodeListPointer->next = new NodeList<Node>{ Node(value), nodeListPointer->next };
	}
	//���������� � ������� � ����� ������
	else
		nodeListPointer->next = new NodeList<Node>{ Node(value), nullptr };
}

Node::Node(int value) {
	this->value = value;
	connectedNodes = nullptr;
}

int Node::getValue() {
	return value;
}

void Graph::print() {
	if (nodes != nullptr) {
		NodeList<Node>* nodeListPointer = nodes;
		while (nodeListPointer != nullptr) {
			//������ nodeListPointer->data � ���� ��������� � ��� ������
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
	Node* firstNode = searchNode(firstNodeValue);
	Node* secondNode = searchNode(secondNodeValue);
	if (firstNode != nullptr && secondNode != nullptr) {
		firstNode->addEdgeToNode(secondNode);
		secondNode->addEdgeToNode(firstNode);
	}
	else 
		cout << "At least one node wasn't found" << endl;
}

void Node::addEdgeToNode(Node* node) {
	NodeList<Node*>* nodeListPointer = connectedNodes;
	//���������� � ������ ������
	if (nodeListPointer == nullptr || node->value < nodeListPointer->data->value) {
		connectedNodes = new NodeList<Node*>{ node, connectedNodes };
		return;
	}
	//�������� ������ �������
	if (connectedNodes->data->value == node->value) {
		cout << "Edge to this node already exists" << endl;
		return;
	}
	while (nodeListPointer->next != nullptr && nodeListPointer->next->data->value < node->value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer->next != nullptr) {
		//���� ���� � ���� ������� ��� ����, �� ������ �� ������
		if (nodeListPointer->next->data->value != node->value)
			nodeListPointer->next = new NodeList<Node*>{ node, nodeListPointer->next };
		else
			cout << "Edge to this node already exists" << endl;
	}
	else
		nodeListPointer->next = new NodeList<Node*>{ node, nullptr };
}

void Graph::delEdge(int firstNodeValue, int secondNodeValue) {
	Node* firstNode = searchNode(firstNodeValue);
	Node* secondNode = searchNode(secondNodeValue);;
	if (firstNode != nullptr && secondNode != nullptr) {
		firstNode->delEdgeToNode(secondNode);
		secondNode->delEdgeToNode(firstNode);
	}
	else
		cout << "At least one node wasn't found" << endl;
}

void Node::delEdgeToNode(Node* node) {
	if (connectedNodes->data->value == node->value) {
		connectedNodes = connectedNodes->next;
		return;
	}
	NodeList<Node*>* nodeListPointer = connectedNodes;
	while (nodeListPointer->next != nullptr && nodeListPointer->next->data->value != node->value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer->next != nullptr && nodeListPointer->next->data->value == node->value) {
		nodeListPointer->next = nodeListPointer->next->next;
		NodeList<Node*>* toDel = nodeListPointer->next;
		delete(toDel);
	}
	else
		cout << "Edge to this node doesn't exist" << endl;
}

Node* Graph::searchNode(int value) {
	if (nodes == nullptr) {
		cout << "Graph is empty" << endl;
		return nullptr;
	}
	NodeList<Node>* nodeListPointer = nodes;
	while (nodeListPointer != nullptr && nodeListPointer->data.value < value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer != nullptr && nodeListPointer->data.value == value)
		return &nodeListPointer->data;
	else
		return nullptr;
}