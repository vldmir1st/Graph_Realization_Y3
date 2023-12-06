#pragma once

#include <iostream>

using namespace std;

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
	void print();
};

class Graph {
private:
	NodeList<Node>* nodes;
public:
	Graph();
	void print();
	void addNode(int value);
	void delNode(int value);
	bool searchNode(int index);
	void addEdge(int firstNodeValue, int secondNodeValue);
	void delEdge(int indexFrom, int indexTo);
	void searchEdge(int indexFrom, int indexTo);
	void traverse();
	void printAllIndependentSets();
};