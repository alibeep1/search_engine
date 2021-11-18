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
	double d = 0.85;
	bool executed_pr = true;
	bool first_run = true;
	//Is our adjacency List of string values
	vector<vector<string>> adjList;

	//Maps for every unique url a corresponding unique vertexNumber
	unordered_map<string, int> map;

	//Holds the values for the (i)th iteration's pageRanks
	double currPr[WEB_SIZE];

	//Checks whether a node was visitedAsNode previously as a destination 
	bool visitedAsNode[WEB_SIZE];

	//Holds the (i-1)th iteration's pageRanks
	double oldPr[WEB_SIZE];

	//Checks whether a node is pointed to by any other node
	bool visitedAsRoot[WEB_SIZE];

	Graph(vector<Edge> const& edges, int N);

	//Unnecessary since the graph is static
	void addEdge(Edge const& newEdge);

	//Prints the layout of the graph (adjacency list)
	void printGraph();

	//Copies "currPr" values to the "oldPr" array for subsequent, i-th iterations of PageRank();
	void copyNewPrToOld();

	//Calculates pageRanks for each WebPage and writes the output to pagerank.csv
	void PageRank();

};

