#include "Graph.h"

Graph::Graph(vector<Edge> const	& edges, int N)
{
	cout << "in the constructor " << endl;
	_n = N;
	adjList.resize(_n);
	bool* exists = new bool[_n];
	/*for (int i = 0; i < WEB_SIZE; i++)
	{
		temp[i] = 0.25;
	}*/
	for (int i = 0; i < WEB_SIZE; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < WEB_SIZE; i++)
	{
		oldTemp[i] = 1.0 / WEB_SIZE;
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
		cout << "(" << edges[i].src.getUrl() << ", " << edges[i].dest.getUrl() << ")" << endl;
		int source_number = edges[i].src.getVertexNo();
		//cout << "source number = " << source_number << endl;
		int dest_number = edges[i].dest.getVertexNo();

		if (exists[source_number] == 0) {
			/*cout << "edges["<< i<< "].src = "<<edges[i].src.getUrl()  << endl;*/
			adjList[source_number].push_back(edges[i].src);
			exists[source_number] = true;
		}

		if (exists[dest_number] == 0) {

			adjList[dest_number].push_back(edges[i].dest);
			exists[dest_number] = true;
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

void Graph::PageRank()
{
	cout << endl << "PageRank initiating..." << endl;

	for (int i = 0; i < _n; i++)
	{
		

		cout << endl<<"In the i-th iteration for i = " << i;
		
		
		double pageRank = 0;
		WebPage* root = nullptr;
		double numerator = 0;
		double childrenCount = 0;;

		for (auto x = adjList[i].begin(); x != adjList[i].end(); x++)
		{
			if (x == adjList[i].begin())
			{
				root = &(*x);
				cout << " for the webPage: " << root->getUrl()<<" with vertexNo = "<<root->getVertexNo() << endl;
			}
			
			else 
			{
				numerator = oldTemp[root->getVertexNo()];
				childrenCount = adjList[root->getVertexNo()].size() - 1;
				//double numerator = oldTemp[root->getVertexNo()];
				cout << "For the page: " << x->getUrl() <<" with vertexNo = "<<x->getVertexNo()<< endl;
				cout << "numerator = " << numerator << endl;
				//double childrenCount = adjList[root->getVertexNo()].size() - 1;
				cout << "childrenCount = " << childrenCount << endl;
				cout << "Supposed pageRank = " << numerator / childrenCount<< endl;

				pointedTo[x->getVertexNo()] = true;

				if (/*temp[x->getVertexNo()]*/ visited[x->getVertexNo()] == 0 && oldTemp[x->getVertexNo()]== 0.25 && adjList[x->getVertexNo()].size() >=1)
				{
					visited[x->getVertexNo()] = 1;
					cout << "in the if statement!" << endl;
					oldTemp[x->getVertexNo()] = x->getPageRank();

					x->setPageRank(numerator / childrenCount);


					cout << "actual pageRank = " << x->getPageRank()<< endl;
					//temp[x->getVertexNo()] = numerator / childrenCount;

				}
				else {
					oldTemp[x->getVertexNo()] = x->getPageRank();

					cout << "in the ELSE statement!" << endl;
					cout << "pageRank before incrementation: "<<x->getPageRank()<<endl;

					//temp[x->getVertexNo()] += numerator / childrenCount;
					x->incrementPageRank(numerator / childrenCount);

					cout << "pageRank after incrementation: "<<x->getPageRank()<<endl;
					
				}
				
				
			}
			if (!pointedTo[x->getVertexNo()]) {
				x->setPageRank(0);
				//temp[x->getVertexNo()] = 0;
			}
			//temp[root->getVertexNo()] = pageRank;
			
		}
		
		//cout << "pageRank = " << temp[root->getVertexNo()] << endl;
		
		
	}
	/*for (int i = 0; i < WEB_SIZE; i++)
	{
		cout << "pageRank for vertexNo " << i << " equals " << temp[i] << endl;
	}*/

	cout << endl << "printing pageRanks" << endl;

	vector<WebPage>::iterator it;
	for (int i = 0; i < _n; i++)
	{
		//it = adjList[i].begin();

		for (auto x = adjList[i].begin(); x != adjList[i].end(); x++)
		{
			
			if(x!=adjList[i].begin())
				cout << x->getUrl() << ", pageRank = " << x->getPageRank() << endl;

			
			
		}
		cout << endl;
		
	}

	//normalization
		//output vertexNo,PageRank
		//			2,0.7
	//score calculation

	//check if test1 will be zero
	cout << endl << "Executed PageRank" << endl;
}

