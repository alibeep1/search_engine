#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
#define WEB_SIZE 4
#pragma once


class WebPage
{
private:

	string url;
	double impressions;
	double clicks;
	double ctr;
	int vertexNo;
	double pageRank;
	double score;
	void updateCTR();
	vector<string> keywords;
public:

	void calcScore();
	double getScore();
	//string myName(string x, int y);
	WebPage(const string url, int vertexNo);
	WebPage();
	string getUrl() const;
	double getImpressions();
	double getClicks();
	double getCTR();
	double getPageRank();
	int getVertexNo() const;
	void incrementImpressions();
	void incrementClicks();
	void incrementPageRank(double pr);
	void setUrl(string url);
	void setImpressions(double impressions);
	void setClicks(double clicks);
	void setVertexNo(int number);
	void setPageRank(double pageRank);
	void appendKeyword(string word);

	void printWebPage();
};

