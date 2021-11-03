#pragma once
#include <iostream>
#include<vector>
#include<string>
#include "WebPage.h"
#include<unordered_map>

using namespace std;

struct Edge { WebPage src, dest; };

class Graph
{
private:
	int _n;
public:
	vector<vector<WebPage>> adjList;
	double temp[WEB_SIZE];
	Graph(vector<Edge> const& edges, int N);

	void addEdge(Edge const& newEdge);
	void printGraph();
	void PageRank();

};

