#include "Graph.h"

Graph::Graph(vector<Edge> const& edges, int N)
{
	cout << "in the constructor ";
	_n = N;
	adjList.resize(_n);
	bool* exists = new bool[N];
	for (int i = 0; i < N; i++)
	{
		exists[i] = 0;
	}
	for (int i = 0; i < edges.size(); i++)
	{
		int source_number = edges[i].src.getVertexNo();
		//cout << "source number = " << source_number << endl;

		if (exists[source_number] == 0) {

			adjList[source_number].push_back(edges[i].src);
			exists[source_number] = true;
		}
		
			adjList[source_number].push_back(edges[i].dest);

		
	}
	//for (auto Edge : edges) //what is that?
	//{
	//	int source = Edge.src.getVertexNo();
	//	//cout << "Edge.src = " << Edge.src << "; Edge.dest = " << Edge.dest << endl;
	//	adjList[source].push_back(Edge.dest); //pushes back the destination to the source's internal vector!
	//	//adjList[Edge.dest].push_back(Edge.src); //for undirected graphs!
	//}
}

void Graph::addEdge(Edge const& newEdge)
{
	adjList[newEdge.src.getVertexNo()].push_back(newEdge.dest);
}

void Graph::printGraph()
{
	cout << endl<<"printing Graph" << endl;
	for (int i = 0; i < _n; i++)
	{
		//cout << i << " --> ";
		for (auto x = adjList[i].begin(); x != adjList[i].end(); x++)
		{
			if (x == adjList[i].begin())
			{
				cout << (*x).getUrl() << " --> ";
			}
			else {
				cout << (*x).getUrl() << " ";
			}
		}
		cout << endl;
	}
}

