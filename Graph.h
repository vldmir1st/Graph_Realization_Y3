#pragma once

#include <iostream>

using namespace std;

//Реализация графа через список смежности
//Внешний и внутренние списки упорядочены

//Шаблонный тип списка (внешний список Т - Node;
//Внутренние списки Т - Node*)
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
	int addEdgeToNode(Node* node);	//возвращает код ошибки
	int delEdgeToNode(Node* node);	//возвращает код ошибки
	void print();
};

class Graph {
private:
	NodeList<Node>* nodes;
	Node* searchNodeExt(int value);		//можеть вернуть null
public:
	Graph();
	void print();
	int addNode(int value);		//возвращает код ошибки
	int delNode(int value);		//возвращает код ошибки
	bool searchNode(int value);
	int addEdge(int firstNodeValue, int secondNodeValue);	//возвращает код ошибки
	int delEdge(int firstNodeValue, int secondNodeValue);	//возвращает код ошибки
	bool searchEdge(int firstNodeValue, int secondNodeValue);
	void traverse();
	void printAllIndependentSets();
};