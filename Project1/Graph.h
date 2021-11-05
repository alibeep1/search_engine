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

//Holds our adjacency list which necessary for calculating pageRank
class Graph
{
private:
	int _n;
public:
	//Is our adjacency List of string values
	vector<vector<string>> adjList;

	//Maps for every unique url a corresponding unique vertexNumber
	unordered_map<string, int> map;

	//Holds the values for the (i)th iteration's pageRanks
	double temp[WEB_SIZE];

	//Checks whether a node was visited previously as a destination 
	bool visited[WEB_SIZE];

	//Holds the (i-1)th iteration's pageRanks
	double oldTemp[WEB_SIZE];

	//Checks whether a node is pointed to by any other node
	bool pointedTo[WEB_SIZE];

	Graph(vector<Edge> const& edges, int N);

	//unnecessary since the graph is static
	void addEdge(Edge const& newEdge);

	//prints the layout of the graph (adjacency list)
	void printGraph();

	//Calculates pageRanks for each WebPage and writes the output to pagerank.csv
	void PageRank();

};

