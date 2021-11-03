#include <iostream>
#include "WebPage.h"
#include<fstream>
#include<iomanip>
#include<sstream>
#include <vector>
#include"graph.h"
#include"Graph.h"
#include"Trie.h"
#include<string>
#include<unordered_map>


//#include"Graph.h"
using namespace std;


void read_url_keywords(WebPage pages[WEB_SIZE], Trie* h);
vector<Edge> read_web_graph(unordered_map<string, WebPage>& const umap);
void read_impressions(unordered_map<string, WebPage>&  umap);

void printMap(unordered_map<string, WebPage>& umap);
void initializeMap(WebPage  pages[WEB_SIZE], unordered_map<string, WebPage>& umap);

int main() {
	

	
	WebPage pages[WEB_SIZE];	//array of webpages

	unordered_map<string, WebPage> umap;


	Trie* head = new Trie();

	
	read_url_keywords(pages,head);
	initializeMap(pages, umap);
	read_impressions(umap);

	vector<Edge> edges = read_web_graph(umap);
	Graph graph(edges, WEB_SIZE);		//web graph
	//printUmap(umap);
	//vector<Edge> edges = { {pages[0], pages[1]}, {pages[1], pages[2]}, {pages[2], pages[3]}, {pages[1], pages[3]} };

	//printMap(umap);
	//cout << head->search("programming") << endl;
	//pages[0].printWebPage();
	graph.PageRank();
	//graph.printGraph();
	
	return 0;
}

void read_impressions(unordered_map<string, WebPage>& umap)
{
	ifstream myFile;

	myFile.open("F:/AUC/21-22/Analysis and Design of Algorithms - Lab/search_engine/Project1/impressions.csv");


	string line, word;


	while (myFile.good())
	{


		getline(myFile, line, '\n');

		stringstream s(line);

		int wordCounter = 0;
		string temp_word;
		while (getline(s, word, ','))
		{
			

			if (wordCounter == 0)
			{
				temp_word = word;
			}
			else {
				/*cout << "word = " << word << endl;
				cout << "umap[temp_word] = " << umap[temp_word].getUrl() << endl;*/
				umap[temp_word].setImpressions(stof(word));
			}
			

			wordCounter++;
			//cout << "inner loop" << endl;
		}

		//cout << "outer loop" << endl;
	}
	myFile.close();
}


vector<Edge> read_web_graph(unordered_map<string, WebPage>& const umap)
{
	vector<Edge> edges;
	
	ifstream myfile;
	myfile.open("f:/auc/21-22/analysis and design of algorithms - lab/search_engine/project1/web_graph.csv");

	string line, word;

	while (myfile.good())
	{
		getline(myfile, line, '\n');
		//cout << line << endl;
		stringstream s(line);

		int wordcounter = 0;

		Edge tempEdge;
		while (getline(s, word, ','))
		{
			//cout << "wordcounter = " << wordcounter << endl;
			if (wordcounter == 0)
			{
				//cout << "source-word = " << word << endl;
				tempEdge.src = umap[word];
			}
			else {
				//cout << "dest-word = " << word << endl;
				tempEdge.dest = umap[word];
			}

				/*cout << "tempEdge.src = " << tempEdge.src.getUrl() << endl;
				cout << "tempEdge.dest = " << tempEdge.dest.getUrl() << endl;*/

			wordcounter++;
			//cout << "inner loop" << endl;
		}
			edges.push_back(tempEdge);

		
		//cout << "outer loop" << endl;
	}
	myfile.close();
	return edges;
}


void read_url_keywords(WebPage  pages[WEB_SIZE], Trie* h)
{
	ifstream myFile;

	myFile.open("F:/AUC/21-22/Analysis and Design of Algorithms - Lab/search_engine/Project1/keywords.csv");

	
	string line, word;

	int vertexCount = 0;

	while (myFile.good())
	{

		/*cout << endl;
		cout << "vertexCount = " << vertexCount << endl;*/

		getline(myFile, line, '\n');
		//cout << line << endl;
		stringstream s(line);

		int wordCounter = 0;

		while (getline(s, word, ','))
		{
			//cout << endl;
			//cout << "counter = " << wordCounter << endl;
			////cout << "in the if condition" << endl;
			/*cout << "word = " << word << endl;*/
			//cout << "inner while loop" << endl;

			if (wordCounter == 0)
			{
				//pages[vertexCount].setImpressions(10);
				pages[vertexCount].setVertexNo(vertexCount);
				pages[vertexCount].setUrl(word);
			}
			else {
				h->insert(word, pages[vertexCount]);
			}

			wordCounter++;
			//cout << "inner loop" << endl;
		}

		vertexCount++;
		//cout << "outer loop" << endl;
	}
	myFile.close();
}



void initializeMap(WebPage  pages[WEB_SIZE], unordered_map<string, WebPage>& umap)
{
	//assigns the name of the webpage as keys and the WebPage object as the corresponding value;
	for (int i = 0; i < WEB_SIZE; i++)
	{
		string url = pages[i].getUrl();
		umap[url] = pages[i];
	}
}

void printMap(unordered_map<string, WebPage>& umap)
{
	for (auto x : umap)
	{
		cout << endl;
		cout << "key: " << x.first <<  endl;
		x.second.printWebPage();
	}
	cout << endl;
}