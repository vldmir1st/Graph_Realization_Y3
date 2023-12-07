#include "Graph.h"

Graph::Graph() {
	nodes = nullptr;
}

void Graph::addNode(int value) {
	//Добавление вершины в пустой граф
	if (nodes == nullptr || value < nodes->data.value) {
		nodes = new NodeList<Node>{ Node(value), nodes };
		return;
	}
	//Если первая вершина имеет значение value, то ничего не происходит
	if (nodes->data.value == value) {
		cout << "Node with such value already exists in graph" << endl;
		return;
	}

	NodeList<Node>* nodeListPointer = nodes;
	//Идем до конца или пока не встретим элемент больше value 
	while (nodeListPointer->next != nullptr && nodeListPointer->next->data.value < value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer->next != nullptr) {
		//Если элемент с таким значением уже есть, то в граф новая вершина не добавляется
		if (nodeListPointer->next->data.value != value)
			nodeListPointer->next = new NodeList<Node>{ Node(value), nodeListPointer->next };
	}
	//Добавление в вершины в конец списка
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
			//Печать nodeListPointer->data и всех связанных с ней вершин
			nodeListPointer->data.print();
			nodeListPointer = nodeListPointer->next;
		}
		cout << "\n";
	}
	else
		cout << "Graph is empty" << endl;
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
	//Добавление в начало списка
	if (nodeListPointer == nullptr || node->value < nodeListPointer->data->value) {
		connectedNodes = new NodeList<Node*>{ node, connectedNodes };
		return;
	}
	//Проверка первой вершины
	if (connectedNodes->data->value == node->value) {
		cout << "Edge to this node already exists" << endl;
		return;
	}

	while (nodeListPointer->next != nullptr &&
		nodeListPointer->next->data->value < node->value)
		nodeListPointer = nodeListPointer->next;

	if (nodeListPointer->next != nullptr) {
		//Если дуга к этой вершине уже есть, то ничего не делаем
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
	Node* secondNode = searchNode(secondNodeValue);

	if (firstNode != nullptr && secondNode != nullptr) {
		firstNode->delEdgeToNode(secondNode);
		secondNode->delEdgeToNode(firstNode);
	}
	else
		cout << "At least one node wasn't found" << endl;
}

void Node::delEdgeToNode(Node* node) {
	//Проверка первого элемента
	if (connectedNodes->data->value == node->value) {
		NodeList<Node*>* edgeToDelete = connectedNodes;
		connectedNodes = connectedNodes->next;
		delete(edgeToDelete);
		return;
	}

	NodeList<Node*>* nodeListPointer = connectedNodes;
	while (nodeListPointer->next != nullptr &&
		nodeListPointer->next->data->value != node->value)
		nodeListPointer = nodeListPointer->next;

	if (nodeListPointer->next != nullptr &&
		nodeListPointer->next->data->value == node->value) {
		//Удаление найденного ребра
		NodeList<Node*>* edgeToDelete = nodeListPointer->next;
		nodeListPointer->next = nodeListPointer->next->next;
		delete(edgeToDelete);
	}
	//До этой вершины не было ребра
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

void Graph::delNode(int value) {
	if (nodes != nullptr) {
		NodeList<Node>* listElementToDelete = nullptr;
		//Проверка первого элемента списка
		if (nodes->data.value == value) {
			listElementToDelete = nodes;
			nodes = nodes->next;
		}
		//Поиск по списку
		else {
			NodeList<Node>* nodeListPointer = nodes;
			while (nodeListPointer->next != nullptr &&
				nodeListPointer->next->data.value < value)
				nodeListPointer = nodeListPointer->next;
			//Проверка на то, что выход из цикла произошел по
			//причине нахождения нужной вершины.
			//Если это она, то запоминаем ее и перекидываем ссылки в списке
			if (nodeListPointer->next != nullptr &&
				nodeListPointer->next->data.value == value) {
				listElementToDelete = nodeListPointer->next;
				nodeListPointer->next = nodeListPointer->next->next;
			}
			//Вершина с этим значением не была найдена - выход из метода
			else {
				cout << "There is no node with such value" << endl;
				return;
			}
		}
		//Удаление всех ребер, связанных с удаляемой вершиной
		if (listElementToDelete->data.connectedNodes != nullptr) {
			NodeList<Node*>* edgeToDelete;
			while (listElementToDelete->data.connectedNodes != nullptr) {
				edgeToDelete = listElementToDelete->data.connectedNodes;
				listElementToDelete->data.connectedNodes =
					listElementToDelete->data.connectedNodes->next;
				edgeToDelete->data->delEdgeToNode(&listElementToDelete->data);
				delete(edgeToDelete);
			}
		}
		//Непосредственно удаление вершины
		listElementToDelete->next = nullptr;
		delete(listElementToDelete);
	}
	//Пустой граф
	else
		cout << "You can't delete node with such value - graph is empty" << endl;
}