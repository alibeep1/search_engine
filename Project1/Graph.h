#pragma once
#include <iostream>
#include<vector>
#include "WebPage.h"


using namespace std;

struct Edge { WebPage src, dest; };

class Graph
{
private:
	int _n;
public:
	vector<vector<WebPage>> adjList;

	Graph(vector<Edge> const& edges, int N);

	void addEdge(Edge const& newEdge);
	void printGraph();


};

