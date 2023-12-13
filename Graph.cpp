#include "Graph.h"

Graph::Graph() {
	nodes = nullptr;
}

//Возвращает 1, если в графе уже существует такая вершина, иначе - 0
int Graph::addNode(int value) {
	//Добавление вершины в пустой граф
	if (nodes == nullptr || value < nodes->data.value) {
		nodes = new NodeList<Node>{ Node(value), nodes };
		return 0;
	}
	//Если первая вершина имеет значение value, то выходим из методом с кодом ошибки 1
	if (nodes->data.value == value)
		return 1;

	NodeList<Node>* nodeListPointer = nodes;
	//Идем до конца или пока не встретим элемент больше value 
	while (nodeListPointer->next != nullptr && nodeListPointer->next->data.value < value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer->next != nullptr) {
		//Если элемент с таким значением уже есть, то в граф новая вершина не добавляется
		if (nodeListPointer->next->data.value != value)
			nodeListPointer->next = new NodeList<Node>{ Node(value), nodeListPointer->next };
		else
			return 1;
	}
	//Добавление в вершины в конец списка
	else
		nodeListPointer->next = new NodeList<Node>{ Node(value), nullptr };
	return 0;
}

Node::Node(int value) {
	this->value = value;
	isMarked = false;
	connectedNodes = nullptr;
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

//Возвращает 1, если хотя бы одна вершина не была найдена, иначе - 0
int Graph::addEdge(int firstNodeValue, int secondNodeValue) {
	Node* firstNode = searchNodeExt(firstNodeValue);
	Node* secondNode = searchNodeExt(secondNodeValue);

	if (firstNode != nullptr && secondNode != nullptr) {
		firstNode->addEdgeToNode(secondNode);
		secondNode->addEdgeToNode(firstNode);
		return 0;
	}
	return 1;
}

// Возвращает 1, если такое ребро уже существует, иначе - 0
int Node::addEdgeToNode(Node* node) {
	NodeList<Node*>* nodeListPointer = connectedNodes;
	//Добавление в начало списка
	if (nodeListPointer == nullptr || node->value < nodeListPointer->data->value) {
		connectedNodes = new NodeList<Node*>{ node, connectedNodes };
		return 0;
	}
	//Проверка первой вершины
	if (connectedNodes->data->value == node->value)
		//Такое ребро уже есть
		return 1;

	while (nodeListPointer->next != nullptr &&
		nodeListPointer->next->data->value < node->value)
		nodeListPointer = nodeListPointer->next;

	if (nodeListPointer->next != nullptr) {
		//Если ребро к этой вершине уже есть, то выдаем код ошибки 1
		if (nodeListPointer->next->data->value != node->value)
			nodeListPointer->next = new NodeList<Node*>{ node, nodeListPointer->next };
		else
			return 1;
	}
	else
		nodeListPointer->next = new NodeList<Node*>{ node, nullptr };
	return 0;
}

//Возвращает 1, если хотя бы одна из вершин не была найдена,
//возвращает 2, если хотя бы у одной вершины нет ребер
//иначе возвращает 0
int Graph::delEdge(int firstNodeValue, int secondNodeValue) {
	Node* firstNode = searchNodeExt(firstNodeValue);
	Node* secondNode = searchNodeExt(secondNodeValue);

	if (firstNode != nullptr && secondNode != nullptr) {
		if (firstNode->connectedNodes == nullptr ||
			secondNode->connectedNodes == nullptr)
			return 2;
		else {
			firstNode->delEdgeToNode(secondNode);
			secondNode->delEdgeToNode(firstNode);
			return 0;
		}
	}
	return 1;
}

//Возвращает 1, если до данной вершины не существует ребра, иначе 0
int Node::delEdgeToNode(Node* node) {
	//Проверка первого элемента
	if (connectedNodes->data->value == node->value) {
		NodeList<Node*>* edgeToDelete = connectedNodes;
		connectedNodes = connectedNodes->next;
		delete(edgeToDelete);
		return 0;
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
		return 0;
	}
	return 1;
}

bool Graph::searchNode(int value) {
	if (searchNodeExt(value) != nullptr)
		return true;
	return false;
}

Node* Graph::searchNodeExt(int value) {
	if (nodes == nullptr)
		return nullptr;
	NodeList<Node>* nodeListPointer = nodes;
	while (nodeListPointer != nullptr && nodeListPointer->data.value < value)
		nodeListPointer = nodeListPointer->next;
	if (nodeListPointer != nullptr && nodeListPointer->data.value == value)
		return &nodeListPointer->data;
	else
		return nullptr;
}

//Возвращает 1, если в графе нет такой вершины, иначе 0
int Graph::delNode(int value) {
	if (nodes != nullptr) {
		NodeList<Node>* listElementToDelete = searchNodeInOrderToDeleteIt(value);
		//Вершина не была найдена
		if (listElementToDelete == nullptr)
			return 1;
		deleteAllEdgesConnectedWithNode(listElementToDelete);
		//Непосредственно удаление вершины
		listElementToDelete->next = nullptr;
		delete(listElementToDelete);
		return 0;
	}
	//Пустой граф
	return 1;
}

NodeList<Node>* Graph::searchNodeInOrderToDeleteIt(int value) {
	NodeList<Node>* listElementToDelete = nullptr;
	//Проверка первого элемента списка
	if (nodes->data.value == value) {
		listElementToDelete = nodes;
		nodes = nodes->next;
	}
	//Поиск по оставшейся части списка
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
	}
	return listElementToDelete;
}

void Graph::deleteAllEdgesConnectedWithNode(NodeList<Node>* listElementToDelete) {
	if (listElementToDelete->data.connectedNodes != nullptr) {
		NodeList<Node*>* edgeToDelete;
		while (listElementToDelete->data.connectedNodes != nullptr) {
			//Если ребро является петлёй, то просто пропускаем
			if (listElementToDelete->data.connectedNodes->data == &listElementToDelete->data) {
				listElementToDelete->data.connectedNodes =
					listElementToDelete->data.connectedNodes->next;
				continue;
			}
			edgeToDelete = listElementToDelete->data.connectedNodes;
			listElementToDelete->data.connectedNodes =
				listElementToDelete->data.connectedNodes->next;
			edgeToDelete->data->delEdgeToNode(&listElementToDelete->data);
			delete(edgeToDelete);
		}
	}
}

//Возвращает false, если между двумя вершинами с
//заданными значениями не имеется ребра или
//если хотя бы одной из вершин нет. Иначе возвращает true
bool Graph::searchEdge(int firstNodeValue, int secondNodeValue) {
	Node* firstNode = searchNodeExt(firstNodeValue);
	if (firstNode == nullptr || searchNodeExt(secondNodeValue) == nullptr)
		return false;
	if (firstNode->connectedNodes == nullptr)
		return false;
	NodeList<Node*>* edgeIterator = firstNode->connectedNodes;
	while (edgeIterator != nullptr && edgeIterator->data->value != secondNodeValue)
		edgeIterator = edgeIterator->next;
	if (edgeIterator != nullptr)
		return true;
	return false;
}

//Обход в ширину с использованием очереди
void Graph::traverse() {
	if (nodes != nullptr) {
		auto queueHead = new NodeList<Node*>{ &nodes->data, nullptr };
		auto queueTail = queueHead;
		queueTail->data->isMarked = true;
		while (queueHead != nullptr && queueTail != nullptr) {
			cout << queueHead->data->value << " ";
			addUnmarkedNodesToQueue(queueHead, queueTail);
			auto toDelete = queueHead;
			if (queueHead == queueTail)
				queueTail = queueTail->next;
			queueHead = queueHead->next;
			toDelete->data, toDelete->next = nullptr;
			delete(toDelete);
		}
	}
}

void Graph::addUnmarkedNodesToQueue(NodeList<Node*>*& queueHead,
	NodeList<Node*>*& queueTail) {
	auto connectedNodesIterator = queueHead->data->connectedNodes;
	while (connectedNodesIterator != nullptr) {
		if (!connectedNodesIterator->data->isMarked) {
			queueTail->next =
				new NodeList<Node*>{ connectedNodesIterator->data, nullptr };
			queueTail = queueTail->next;
			queueTail->data->isMarked = true;
		}
		connectedNodesIterator = connectedNodesIterator->next;
	}
}

void Graph::printAllMaxIndependentSets() {
	cout << "Max independent sets:\n";
	if (nodes != nullptr) {
		NodeList<int>* currentIndependentSet = nullptr;
		NodeList<int>* candidates = nullptr;
		fillCandidates(candidates);
		NodeList<int>* usedNodes = nullptr;
		extendIndependentSet(currentIndependentSet, candidates, usedNodes);
	}
}

void Graph::fillCandidates(NodeList<int>* &candidates) {
	candidates = new NodeList<int>{ nodes->data.value, nullptr };
	NodeList<Node>* nodeListPointer = nodes->next;
	while (nodeListPointer != nullptr) {
		candidates = new NodeList<int>{ nodeListPointer->data.value, candidates };
		nodeListPointer = nodeListPointer->next;
	}
}

void Graph::extendIndependentSet(NodeList<int>* &currentIndependentSet,
	NodeList<int>* &candidates, NodeList<int>* &usedNodes) {
	while (candidates != nullptr && check(candidates, usedNodes)) {
		addNodeValueToSet(currentIndependentSet, candidates->data);
		auto newCandidates = makeNewSet(candidates, currentIndependentSet->data);
		auto newUsedNodes = makeNewSet(usedNodes, currentIndependentSet->data);
		if (newCandidates == nullptr && newUsedNodes == nullptr)
			printMaxIndependentSet(currentIndependentSet);
		else {
			extendIndependentSet(currentIndependentSet, newCandidates, newUsedNodes);
		}
		addNodeValueToSet(usedNodes, candidates->data);
		removeLastAddedElement(candidates);
		removeLastAddedElement(currentIndependentSet);
	}
	clearSet(candidates);
	clearSet(usedNodes);
}

bool Graph::check(NodeList<int>* candidates, NodeList<int>* usedNodes) {
	NodeList<int>* nodeListPointer1 = usedNodes;
	while (nodeListPointer1 != nullptr) {
		NodeList<int>* nodeListPointer2 = candidates;
		bool flag = true;
		while (nodeListPointer2 != nullptr) {
			if (searchEdge(nodeListPointer1->data, nodeListPointer2->data)) {
				flag = false;
				break;
			}
			nodeListPointer2 = nodeListPointer2->next;
		}
		if (flag) return false;
		nodeListPointer1 = nodeListPointer1->next;
	}
	return true;
}

NodeList<int>* Graph::makeNewSet(NodeList<int>* oldOne, int nodeValue) {
	NodeList<int>* newSet = nullptr;
	NodeList<int>* nodeListPointer = oldOne;
	while (nodeListPointer != nullptr) {
		if (!searchEdge(nodeListPointer->data, nodeValue) &&
			nodeListPointer->data != nodeValue)
			addNodeValueToSet(newSet, nodeListPointer->data);
		nodeListPointer = nodeListPointer->next;
	}
	return newSet;
}

void Graph::printMaxIndependentSet(NodeList<int>* set) {
	NodeList<int>* nodeListPointer = set;
	while (nodeListPointer != nullptr) {
		cout << nodeListPointer->data << " ";
		nodeListPointer = nodeListPointer->next;
	}
	cout << "\n";
}

void Graph::addNodeValueToSet(NodeList<int>* &set, int nodeValue) {
	if (set == nullptr)
		set = new NodeList<int>{ nodeValue, nullptr };
	else
		set = new NodeList<int>{ nodeValue, set };
}

void Graph::removeLastAddedElement(NodeList<int>* &set) {
	NodeList<int>* toDelete = set;
	set = set->next;
	toDelete->next = nullptr;
	delete(toDelete);
}

void Graph::clearSet(NodeList<int>* &set) {
	if (set != nullptr) {
		NodeList<int>* toDel;
		while (set != nullptr) {
			toDel = set;
			set = set->next;
			toDel->next = nullptr;
			delete(toDel);
		}
	}
}