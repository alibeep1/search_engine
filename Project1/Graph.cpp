#include "Graph.h"

Graph::Graph(vector<Edge> const	& edges, int N)
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
		visited[i] = 0;
	}
	for (int i = 0; i < WEB_SIZE; i++)
	{
		oldPr[i] = 1.0 / WEB_SIZE;
	}

	for (int i = 0; i < WEB_SIZE; i++)
	{
		pointedTo[i] = 0;
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
			for (int j = 0; j< WEB_SIZE; j++)
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
	cout << endl<<"printing Graph" << endl;
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

void Graph::normalizePr()
{
	for (int i = 0; i < WEB_SIZE; i++)
	{
		oldPr[i] = currPr[i];
		currPr[i] *= 0.85;
		currPr[i] += 0.15 / WEB_SIZE;
		cout << "currPr[i] = "<<currPr[i] << endl;
	}
	
}



void Graph::PageRank()
{
	ofstream myFile;
	//cout << endl << "PageRank initiating..." << endl;
	double c;
	string root;
	for (int i = 0; i < _n; i++)
	{
		//cout << endl<<"In the i-th iteration for i = " << i;	
		
		//string root;
		//double root_pr = 0;

		root = adjList[i][0];			// the name of the root
		int rootIndex = map[root];		//the index of the root
		c = adjList[i].size() - 1;		//number of outgoing links from the root
		pointedTo[rootIndex] = true;
		//cout << "for the root = " << root << ", ";

		for (auto x = adjList[i].begin(); x != adjList[i].end(); x++)
		{
				int indexOfX = map[*x];
			if (*x != root && !pointedTo[indexOfX]) {


				currPr[indexOfX] += oldPr[rootIndex] / c;

			}
			if (*x != root && pointedTo[indexOfX]) {
				oldPr[indexOfX] = currPr[indexOfX];

				currPr[indexOfX] += oldPr[rootIndex] / c;

			}
			
		}

	}
	normalizePr();
	

	//cout << endl << "printing pageRanks" << endl;
	myFile.open("pagerank.csv");
	
	unordered_map<string, int>::iterator it = map.begin();
	for (int i = 0; i < _n; i++)
	{
		//cout << "in iteration #: " << i << endl;

		string url = it->first;
		double pr = currPr[i];
		//cout << "iterator = " << url << ", ";
		//cout << "currPr[i] = " << pr << endl;
		it++;
		
		myFile << url << "," << pr << endl;
	}
	myFile.close();
	
	//cout << endl << "Executed PageRank" << endl;
}

