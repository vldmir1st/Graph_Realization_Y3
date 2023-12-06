#pragma once

#include <iostream>

using namespace std;

//шаблонный тип списка (внешний список “ - Node;
//внутренние списки “ - Node*)
template <typename T>
struct NodeList {
	T data;
	NodeList* next;
};

class Node {
	friend class Graph;
private:
	int value;
	NodeList<Node*>* connectedNodes;

	Node(int value);
	void addEdgeToNode(Node* node);
	void delEdgeToNode(Node* node);
	void print();
public:
	int getValue();
};

class Graph {
private:
	NodeList<Node>* nodes;
public:
	Graph();
	void print();
	void addNode(int value);
	void delNode(int value);
	Node* searchNode(int value);	//можеть вернуть null
	void addEdge(int firstNodeValue, int secondNodeValue);
	void delEdge(int firstNodeValue, int secondNodeValue);
	void searchEdge(int indexFrom, int indexTo);
	void traverse();
	void printAllIndependentSets();
};