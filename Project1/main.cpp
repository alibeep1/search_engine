#include <iostream>
#include "WebPage.h"
#include<fstream>
#include<iomanip>
#include<sstream>
#include <vector>

#include"Trie.h"
#include<unordered_map>

#define WEB_SIZE 4
//#include"Graph.h"
using namespace std;

void read_url_keywords(WebPage pages[WEB_SIZE], Trie* h);
void printUmap(unordered_map<string, WebPage>& umap);
void initializeUmap(WebPage  pages[WEB_SIZE], unordered_map<string, WebPage>& umap);

int main() {
	//WebPage page1("www.wikipedia",10,3);
	//cout << "Website name: " << page1.getUrl() << endl;
	//cout << "impressions: " << page1.getImpressions() << endl;
	//cout << "clicks: " << page1.getClicks() << endl;

	//cout << page1.getCTR() << endl;		//pilot code to test the functionality of the WebPage class
	//page1.incrementClicks();
	//page1.incrementImpressions();
	//cout << "impressions: " << page1.getImpressions() << endl;
	//cout << "clicks: " << page1.getClicks() << endl;

	//cout<<page1.getCTR();

	/*WebPage page1("test1", 20, 1);
	WebPage page2("test2", 400, 2);
	WebPage page3("test3", 150, 3);
	WebPage page4("test4", 340, 4);*/
	
	//vector<Edge> graph1 = { {page1, page2}, {page2, page3}, {page3, page4}, {page1, page3} };

	//int x = 4;					//number of vertices
	////Edge _newEdge = { 0, 3 };
	//Graph graph(graph1, x);
	//graph.printGraph();
	unordered_map<string, WebPage> umap;
	WebPage pages[WEB_SIZE];	//array of webpages

	Trie* head = new Trie();

	Node node;


	/*for (int i = 0; i < WEB_SIZE; i++)
	{
		pages[i].printWebPage();
	}*/
	read_url_keywords(pages,head);


	initializeUmap(pages, umap);
	printUmap(umap);


	cout << endl;
	cout << "New pages!" << endl;
	//for (int i = 0; i < WEB_SIZE; i++)
	//{
	//	//pages[i].setUrl("hey");
	//	pages[i].printWebPage();
	//}
	/*node.pages.push_back(pages[0]);
	cout << "_________" << endl;
	cout << "URL "<<node.pages[0].getUrl();*/
	//head->insert("hello", pages[0]);		//keep for debugging the Trie data structure!
	//head->insert("hello", pages[1]);
	////head->insert("hello");
	//cout << "_______________" << endl;
	//cout << head->search("hello");
	/*cout << "______________-" << endl;
	cout << head->search("programming");*/

	return 0;
}

void initializeUmap(WebPage  pages[WEB_SIZE], unordered_map<string, WebPage>& umap)
{
	//assigns the name of the webpage as keys and the WebPage object as the corresponding value;
	for (int i = 0; i < WEB_SIZE; i++)
	{
		string url = pages[i].getUrl();
		umap[url] = pages[i];
	}
}

void printUmap(unordered_map<string, WebPage>& umap)
{
	for (auto x : umap)
	{
		cout << "key: " << x.first << "; value: " << x.second.getVertexNo() << endl;
	}
}


//void read_web_graph(WebPage pages[4])
//{
//	ifstream myFile;
//	myFile.open("F:/AUC/21-22/Analysis and Design of Algorithms - Lab/search_engine/Project1/web_graph.csv");
//	string line, word;
//
//	while (myFile.good())
//	{
//
//		
//
//		getline(myFile, line, '\n');
//		//cout << line << endl;
//		stringstream s(line);
//
//		int wordCounter = 0;
//
//		while (getline(s, word, ','))
//		{
//			cout << endl;
//			cout << "counter = " << wordCounter << endl;
//			//cout << "in the if condition" << endl;
//			cout << "word = " << word << endl;
//			//cout << "inner while loop" << endl;
//
//			if (wordCounter == 0)
//			{
//				//pages[vertexCount].setImpressions(10);
//				pages[vertexCount].setVertexNo(vertexCount);
//				pages[vertexCount].setUrl(word);
//			}
//			else {
//				pages[vertexCount].appendKeyword(word);
//			}
//
//			wordCounter++;
//			//cout << "inner loop" << endl;
//		}
//
//		vertexCount++;
//		//cout << "outer loop" << endl;
//	}
//	myFile.close();
//	
//}


void read_url_keywords(WebPage  pages[WEB_SIZE], Trie* h)
{
	ifstream myFile;

	myFile.open("F:/AUC/21-22/Analysis and Design of Algorithms - Lab/search_engine/Project1/keywords.csv");

	
	string line, word;

	int vertexCount = 0;

	while (myFile.good())
	{

		cout << endl;
		cout << "vertexCount = " << vertexCount << endl;

		getline(myFile, line, '\n');
		//cout << line << endl;
		stringstream s(line);

		int wordCounter = 0;

		while (getline(s, word, ','))
		{
			cout << endl;
			cout << "counter = " << wordCounter << endl;
			//cout << "in the if condition" << endl;
			cout << "word = " << word << endl;
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

