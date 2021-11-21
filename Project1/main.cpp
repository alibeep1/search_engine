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
//#include<cstring>
#include<unordered_map>
#include<list>
#include<algorithm>
#include<string>
#include <set>

#include <limits>

using namespace std;

//Reads urls and assigns the corresponding keywords
void read_url_keywords(unordered_map<string, WebPage>& umap, Trie* h);

//Reads and assigns impressions to websites by indexing them via their url
void read_impressions(unordered_map<string, WebPage>&  umap);

void read_clicks(unordered_map<string, WebPage>& umap);

void updateClicksFile();

void updateImpressionsFile();

//Returns a vector of edges whose source is the first webpage (appearing in the line) and destination is the second one after the comma
vector<Edge> read_web_graph(unordered_map<string, WebPage>& const umap);

//Reads the calculated pageRank values from the generated pagerank.csv file and updates the pageRank values to the corresponding WebPages
void read_pageRank(unordered_map <string, WebPage>& umap);

//Executes printWebPage() for every WebPage object
//Used mainly for debugging purposes
void printMap(unordered_map<string, WebPage>& umap);

/*Helper function that compares the score values of two webPages. 
It returns true if the first WebPage score is greater than that of the second WebPage (descending order).
Used by the sort function
*/
bool compareScore(string i1, string i2);

/*
	INPUT: sorted vector of website names
	OUTPUT: NONE
	FUNCTION: updates website impressions and clicks according to the 
		vector of website names and user choice of visit, respectively
*/
void handle_results(vector<string>& results);

/*
Receives user input and returns a vector of website names that match the query - using the trie head.
Accounts for exclusive uses of multiple OR/AND operators in the query.
Utilizes sets to return duplicates (in the event of AND queries) and
return 1 occurrences of duplicate websites (in the case of OR queries).
*/
vector<string> handle_input(string input, Trie* h);

//Holds the WebPage Objects which are indexed via their names
unordered_map<string, WebPage> umap;

int main() {
	
	
	
	//WebPage pages[WEB_SIZE];	//array of webpages	//has become deprecated and unnecessary thanks for the unordered map



	Trie* head = new Trie();		//is the head of the trie data structure
	
	
	read_url_keywords(umap,head);		
	
	read_impressions(umap);
	read_clicks(umap);

	vector<Edge> edges = read_web_graph(umap);

	Graph graph(edges, WEB_SIZE);		//web graph
	
	for (int i = 0; i < 100; i++)
	{
		graph.PageRank();
	}

	//graph.printGraph();
	read_pageRank(umap);

	printMap(umap);
	//indicates whether the user prefers to terminate or continue browsing
	string response;

	//Stores the retrieved search results unsorted!
	vector<string> results;

	//stores the search query
	do
	{
		string query ="";
		//system("CLS");
		cout << "Please enter your search query:";

		//clearing whitespace from the buffer such that the getline doesn't skip reading user input for subsequent iterations
		getline(cin>>ws, query);
		cout <<"query = "<< query << endl;
		//cout << "query = " << query << endl;

		results = handle_input(query, head);
		
		if (results.empty()) {
			cout << "Not found!" << endl;
			system("pause");
		}
		else {
			//cout << "in the else" << endl;
			bool resume = true;
			string browse;

			//sorts the results in descending order (from greatest to least) according to their pageScore
			sort(results.begin(), results.end(), compareScore);

			for (auto x : results) {
				
				umap[x].incrementImpressions();		//incrementing impressions and updating pageScore
			}
			do
			{
				//system("CLS");
				cout << "Search Results:" << endl;
				int ranking = 1;
				for (auto x : results) {

					cout <<"  "<< ranking<< ".  " << x << endl;
					ranking++;
				}
				cout
					<< endl
					<< left
					<< setw(5)
					<< "Would you like to: "
					<< endl
					<< left
					<< setw(5)
					<< "1. choose a webpage to open"
					<< endl
					<< left
					<< setw(5)
					<< "2. perform a new search"
					<< endl
					<< left
					<< setw(5)
					<< "3. Exit"
					<< endl;
				cin >> browse;
				
				if (browse == "1") {
					handle_results(results);
					system("pause");
					//response = "Y";
				}
				if (browse == "2") {
					resume = false;
					response = "Y";
				}
				if (browse == "3")
				{
					response = "N";
					resume = false;

				}

			} while (resume);

		}

	} while (response == "Y");

	system("CLS");		//clear screen
	
	printMap(umap);		//keep for debugging purposes

	updateImpressionsFile();

	updateClicksFile();

	system("pause");

	return 0;
}

void updateClicksFile()
{
	unordered_map<string, WebPage>::iterator it = umap.begin();
	ofstream clicks;

	clicks.open("clicks.csv");

	//it = umap.begin();
	for (int i = 0; i < WEB_SIZE; i++)
	{
		clicks << it->first << "," << it->second.getClicks() << endl;
		it++;
	}
	clicks.close();
}

void updateImpressionsFile()
{
	unordered_map<string, WebPage>::iterator it = umap.begin();
	ofstream myFile;
	myFile.open("impressions.csv");

	for (int i = 0; i < WEB_SIZE; i++)
	{

		myFile << it->first << "," << it->second.getImpressions() << endl;
		it++;
	}
	myFile.close();
}

void read_clicks(unordered_map<string, WebPage>& umap)
{
	ifstream myFile;
	myFile.open("clicks.csv");

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
				umap[temp_word].setClicks(stof(word));
			}
			wordCounter++;
		}
	}
	myFile.close();
}


vector<string> handle_input(string input, Trie* h) {
	vector<string> temp;

	set<string> set1;

	bool hasOr = true;
	int indexOr = -1;

	bool hasAnd = false;
	int indexAnd = -1;
	string x = "";
	
	if (input.empty()) {
		cout << "ERROR: input is empty!" << endl;
		system("pause");
		return temp;
	}
	
	
	for (int i = 0; i < input.size() -1; i++)
	{
		x = input.substr(i, 2);
		if (x == "OR") {
			input.replace(i, 3, "");
			indexOr = i;
			break;
		}
		
	}
	for (int i = 0; i < input.size() -2; i++)
	{
		x = input.substr(i, 3);
		if (x == "AND")
		{
			input.replace(i, 4,"");
			indexAnd = i;
			hasAnd = true;
			hasOr = false;
			break;
		}
	}

	//in the case that OR is not written explicitly
	if (hasOr && indexOr == -1)
	{
		temp = h->search(input);
		
	}
	//in the case that OR is written explicitly
	if (hasOr && indexOr != -1)
	{
		set<string> setA;
		string word;
		stringstream s(input);
		while (getline(s, word, ' ')) {
			//cout << "word = " << word << endl;
			vector<string> temp1 = h->search(word);
			for (auto d : temp1)
			{
				//to disallow duplicates
				setA.insert(d);
			}
			
		}
			for (auto x: setA)
			{
				temp.push_back(x);
			}
	
	}
	if (hasAnd)
	{
		unordered_map<string, int> tempMap;

		set<string> setB;
		string word;
		stringstream s(input);
		while (getline(s, word, ' '))
		{
			vector<string> temp1 = h->search(word);
			set<string>::iterator it = setB.begin();
			for (auto x : temp1)
			{
				//if there exists a duplicate, then push it to the vector
				if (setB.insert(x).second == false) {
					temp.push_back(x);
				}
				setB.insert(x);
				//it++;
			}
		}
	}

	
	return temp;
}

void handle_results(vector<string>& results)
{
	int _choice = -1;
	string choice = "";
	cout << "Which website would you like to visit?" << endl;

	cin >> _choice;
	cout << "user response = " << _choice;
	cout <<", Whose type is "<< typeid(_choice).name() << endl;
	if (_choice <= results.size() && _choice >0) {
		umap[results[_choice - 1]].incrementClicks();
		cout << "You are visiting: " << umap[results[_choice - 1]].getUrl() << endl;
	}
	else {
		cout << "page does not exist" << endl;
	}
	//cin >> choice;
	//if (umap.find(choice) == umap.end())
	//{
	//	cout << "Page does not exist!" << endl;
	//}
	//else {
	//	umap[choice].incrementClicks();		//incrementing clicks after choice
	//	cout << "You are visiting: " << choice << endl;
	//}
}

bool compareScore(string i1, string i2) {
	try {
		return (umap[i1].getScore() > umap[i2].getScore());
		throw i1;
	}
	catch(string x){
		cout << "exception caught: " << x << " is not in umap!" << endl;
	}
}



void read_pageRank(unordered_map <string, WebPage>& umap) {
	ifstream myFile;

	myFile.open("pagerank.csv");


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
				umap[temp_word].setPageRank(stof(word));
			}

			wordCounter++;
		}
	}
	myFile.close();
}

void read_impressions(unordered_map<string, WebPage>& umap)
{
	ifstream myFile;

	myFile.open("impressions.csv");


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
	myfile.open("web_graph.csv");

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
			if (wordcounter == 0)
			{
				tempEdge.src = umap[word];
			}
			else {
				tempEdge.dest = umap[word];
			}
			wordcounter++;
			
		}
			edges.push_back(tempEdge);
	}
	myfile.close();
	return edges;
}


void read_url_keywords(unordered_map<string, WebPage>& umap, Trie* h)
{
	ifstream myFile;

	myFile.open("keywords.csv");

	
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
				h->insert(word, temp_word);
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