#include "Graph.h"

Graph::Graph(vector<Edge> const	& edges, int N)
{
	cout << "in the constructor " << endl;
	_n = N;
	adjList.resize(_n);
	bool* exists = new bool[_n];
	for (int i = 0; i < WEB_SIZE; i++)
	{
		temp[i] = 1.0 / WEB_SIZE;
	}
	for (int i = 0; i < WEB_SIZE; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < WEB_SIZE; i++)
	{
		oldTemp[i] = temp[i];
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
		//cout << i << " --> ";
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

void Graph::PageRank()
{
	ofstream myFile;
	cout << endl << "PageRank initiating..." << endl;
	for (int i = 0; i < _n; i++)
	{
		

		cout << endl<<"In the i-th iteration for i = " << i;
		
		
		double pageRank = 0;
		//WebPage* root = nullptr;
		string root;
		double numerator = 0;
		double childrenCount = 0;
		int indexOfX;
		
		for (auto x = adjList[i].begin(); x != adjList[i].end(); x++)
		{
			indexOfX = map[*x];
			if (x == adjList[i].begin())
			{
				root = *x;
				cout << "For the WebPage: " << *x << " with vertexNo = " << indexOfX << endl;
				cout << "indexNo for the root = " << map[root] << endl;
				//cout << " for the webPage: " << root->getUrl()<<" with vertexNo = "<<root->getVertexNo() << endl;
				if (adjList[map[root]].size() == 1) {
					cout << "true!" << endl;
					oldTemp[map[root]] = temp[map[root]];
					temp[map[root]] += temp[map[root]];
					cout <<"pageRank for root with no outgoing links = " <<temp[map[root]] << endl;
				}
					
			}
			
			
			else 
			{
				numerator = oldTemp[map[root]];
				cout << "numerator= " << numerator << endl;
				childrenCount = adjList[map[root]].size() -1;
				cout << "childrenCount = " << childrenCount << endl;

				cout << "For the page: " << *x <<" with vertexNo = "<< indexOfX << endl;

				if(!pointedTo[indexOfX] && adjList[indexOfX].size() >= 1){
					cout << "in the if statement!" << endl;
					pointedTo[indexOfX] = true;
					cout << "index of X: "<<indexOfX << endl;
					visited[indexOfX] = true;

					oldTemp[indexOfX] = temp[indexOfX];
					cout << "oldTemp of X: " << oldTemp[indexOfX] << endl;
					temp[indexOfX] = numerator / childrenCount;
					cout << "temp of X: " << temp[indexOfX] << endl;
				}

				else {
					//oldTemp[x->getVertexNo()] = x->getPageRank();
					cout << "In the else statement" << endl;

					//oldTemp[indexOfX] = temp[indexOfX];
					cout << "oldTemp of X: " << oldTemp[indexOfX] << endl;

					temp[indexOfX] += (numerator / childrenCount);
					

					cout << "pageRank after incrementation: "<<temp[indexOfX]<<endl;
					
				}
				
				
			}
			if (!visited[indexOfX]) {

				//x->setPageRank(0);

				temp[indexOfX] = 0;

				//temp[x->getVertexNo()] = 0;

			}
		}
	}
	

	cout << endl << "printing pageRanks" << endl;
	myFile.open("pagerank.csv");
	//vector<WebPage>::iterator it;
	unordered_map<string, int>::iterator it = map.begin();
	for (int i = 0; i < _n; i++)
	{
		cout << "in iteration #: " << i << endl;

		//it = adjList[i].begin();
		//double pr = temp[i];
		/*cout << it->first << ", vertexNo: " << it->second << ", pageRank = " << temp[i] << endl;
		it++;*/
		string url = it->first;
		double pr = temp[i];
		cout << "iterator = " << url << ", ";
		cout << "temp[i] = " << pr << endl;
		it++;
		
		myFile << url << "," << pr << endl;
		////myFile << " %s; %d", it->first, pr << endl;
		//myFile << url << endl;
	}
	myFile.close();
	


	//normalization
		//output vertexNo,PageRank
		//			2,0.7
	//score calculation

	//check if test1 will be zero
	cout << endl << "Executed PageRank" << endl;
}

