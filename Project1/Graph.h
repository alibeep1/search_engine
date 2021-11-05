#pragma once
#include <iostream>
#include<vector>
#include<string>
#include "WebPage.h"
#include<unordered_map>
#include<fstream>
#include<iomanip>
#include<sstream>

using namespace std;

struct Edge { WebPage src, dest; };

class Graph
{
private:
	int _n;
public:
	vector<vector<string>> adjList;
	unordered_map<string, int> map;
	double temp[WEB_SIZE];
	bool visited[WEB_SIZE];
	double oldTemp[WEB_SIZE];
	bool pointedTo[WEB_SIZE];

	Graph(vector<Edge> const& edges, int N);

	void addEdge(Edge const& newEdge);
	void printGraph();
	void PageRank();

};

