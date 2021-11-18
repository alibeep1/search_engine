#include "Graph.h"

Graph::Graph(vector<Edge> const& edges, int N)
{

	_n = N;
	adjList.resize(_n);
	bool* exists = new bool[_n];
	for (int i = 0; i < WEB_SIZE; i++)
	{
		currPr[i] = 0;
	}
	for (int i = 0; i < WEB_SIZE; i++)
	{
		visitedAsNode[i] = false;
	}
	for (int i = 0; i < WEB_SIZE; i++)
	{
		oldPr[i] = 1.0 / WEB_SIZE;
	}

	for (int i = 0; i < WEB_SIZE; i++)
	{
		visitedAsRoot[i] = false;
	}
	for (int i = 0; i < _n; i++)
	{
		exists[i] = 0;
	}
	for (int i = 0; i < edges.size(); i++)
	{
		//cout << "(" << edges[i].src.getUrl() << ", " << edges[i].dest.getUrl() << ")" << endl;
		int source_number = edges[i].src.getVertexNo();
		//cout << "source number = " << source_number << endl;
		int dest_number = edges[i].dest.getVertexNo();

		map[edges[i].src.getUrl()] = edges[i].src.getVertexNo();

		if (exists[source_number] == 0) {
			/*cout << "edges["<< i<< "].src = "<<edges[i].src.getUrl()  << endl;*/
			adjList[source_number].push_back(edges[i].src.getUrl());

			exists[source_number] = true;
		}

		if (exists[dest_number] == 0) {
			map[edges[i].dest.getUrl()] = edges[i].dest.getVertexNo();
			adjList[dest_number].push_back(edges[i].dest.getUrl());

			exists[dest_number] = true;

		}


		adjList[source_number].push_back(edges[i].dest.getUrl());
	}

	for (int i = 0; i < WEB_SIZE; i++)
	{
		//cout << "adjList[i][0].begin() = " << adjList[i][0] << "; adjList[i].size() = " <<adjList[i].size()<<endl;
		if (adjList[i].size() == 1)
		{
			string sink = adjList[i][0];
			for (int j = 0; j < WEB_SIZE; j++)
			{
				string vertex = adjList[j][0];
				if (vertex != sink)
				{
					adjList[i].push_back(vertex);
				}

			}
		}
	}
}

void Graph::addEdge(Edge const& newEdge)
{
	adjList[newEdge.src.getVertexNo()].push_back(newEdge.dest.getUrl());
}

void Graph::printGraph()
{
	cout << endl << "printing Graph" << endl;
	for (int i = 0; i < _n; i++)
	{

		for (auto x = adjList[i].begin(); x != adjList[i].end(); x++)
		{
			if (x == adjList[i].begin())
			{
				cout << (*x) << " --> ";
			}
			else {
				cout << (*x) << " ";
			}
		}
		cout << endl;
	}
}

void Graph::copyNewPrToOld()
{
	for (int i = 0; i < WEB_SIZE; i++){
		oldPr[i] = currPr[i];
	}
}



void Graph::PageRank()
{

	ofstream myFile;
	//cout << endl << "PageRank initiating..." << endl;
	double c;
	string root;
	
	
	for (int i = 0; i < WEB_SIZE; i++)
	{
		visitedAsNode[i] = false;
		currPr[i] = 0;
	}
	
	for (int i = 0; i < _n; i++)
	{
		string root = adjList[i][0];	//stores the name of the source being visited for the current iteration
		int rootIndex = map[root];		//index of the root
		c = adjList[i].size() - 1;		//stores the number of outgoing links or edges from the current root

		for (auto x = adjList[i].begin(); x != adjList[i].end(); x++)
		{
			int xIndex = map[*x];		//index of the node being visited currently

			if (*x != root) {		//given that the current node is not the root node, do...

				if (visitedAsNode[xIndex] == false)		//If it is the first time visiting the node, do...
				{
					visitedAsNode[xIndex] = true;		//mark this node as visited

					//increment current page rank by the product of the damping factor and the old pagerank of the source + constant of normalization
					currPr[xIndex] = currPr[xIndex] + (0.85 * (oldPr[rootIndex] / c)) + (0.15 / WEB_SIZE);		
				}
				//if the current node had been previously visited as a destination, then do...
				else {

					//increment current pageRank by [...] BUT DON'T add to it the constant of normalization
					currPr[xIndex] = currPr[xIndex] + (0.85 * (oldPr[rootIndex] / c));
				}
			}
		}
	}

	copyNewPrToOld();
	
	//Write the PageRank values to a CSV file
	myFile.open("pagerank.csv");

	unordered_map<string, int>::iterator it = map.begin();
	for (int i = 0; i < _n; i++)
	{
		string url = it->first;
		double pr = currPr[i];
		it++;

		myFile << url << "," << pr << endl;
	}
	myFile.close();

	first_run = false;
	
}
