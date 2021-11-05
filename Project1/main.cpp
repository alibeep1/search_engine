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

//Reads urls and assigns the corresponding keywords
void read_url_keywords(unordered_map<string, WebPage>& umap, Trie* h);

//Reads and assigns impressions to websites by indexing them via their url
void read_impressions(unordered_map<string, WebPage>&  umap);

//Returns a vector of edges whose source is the first webpage (appearing in the line) and destination is the second one after the comma
vector<Edge> read_web_graph(unordered_map<string, WebPage>& const umap);

//Reads the calculated pageRank values from the generated pagerank.csv file and updates the pageRank values to the corresponding WebPages
void read_pageRank(unordered_map <string, WebPage>& umap);

//Executes printWebPage() for every WebPage object
//Used mainly for debugging purposes
void printMap(unordered_map<string, WebPage>& umap);

//void initializeMap(WebPage  pages[WEB_SIZE], unordered_map<string, WebPage>& umap);

int main() {
	
	
	
	WebPage pages[WEB_SIZE];	//array of webpages	//has become deprecated and unnecessary thanks for the unordered map

	unordered_map<string, WebPage> umap;


	Trie* head = new Trie();		//is the head of the trie data structure
	
	
	read_url_keywords(umap,head);		
	
	read_impressions(umap);

	vector<Edge> edges = read_web_graph(umap);

	Graph graph(edges, WEB_SIZE);		//web graph

	//graph.printGraph();
	graph.PageRank();
	
	read_pageRank(umap);
	printMap(umap);

	
	cout<<endl<<head->search("programming");

	
	return 0;
}

void read_pageRank(unordered_map <string, WebPage>& umap) {
	ifstream myFile;

	myFile.open("F:/AUC/21-22/Analysis and Design of Algorithms - Lab/search_engine/Project1/pagerank.csv");


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
				umap[temp_word].setPageRank(stof(word));
			}


			wordCounter++;
			//cout << "inner loop" << endl;
		}

		//cout << "outer loop" << endl;
	}
	myFile.close();
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


void read_url_keywords(unordered_map<string, WebPage>& umap, Trie* h)
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
		string temp_word;
		while (getline(s, word, ','))
		{
			
			if (wordCounter == 0)
			{
				temp_word = word;
				umap[temp_word].setVertexNo(vertexCount);
				umap[temp_word].setUrl(temp_word);

				//pages[vertexCount].setVertexNo(vertexCount);
				//pages[vertexCount].setUrl(word);
			}
			else {
				h->insert(word, umap[temp_word]);
				//h->insert(word, pages[vertexCount]);
			}

			wordCounter++;
			
		}

		vertexCount++;
		//cout << "outer loop" << endl;
	}
	myFile.close();
}



//void initializeMap(WebPage  pages[WEB_SIZE], unordered_map<string, WebPage>& umap)
//{
//	//assigns the name of the webpage as keys and the WebPage object as the corresponding value;
//	for (int i = 0; i < WEB_SIZE; i++)
//	{
//		string url = pages[i].getUrl();
//		umap[url] = pages[i];
//	}
//}

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