#include<iostream>
#include<vector>
using namespace std;

#pragma once
class WebPage
{
private:

	string url;
	double impressions;
	double clicks;
	double ctr;
	int vertexNo;
	//double pageRank;
	void updateCTR();
	vector<string> keywords;
public:
	WebPage(const string url, int vertexNo);
	WebPage();
	string getUrl();
	double getImpressions();
	double getClicks();
	double getCTR();
	int getVertexNo() const;
	void incrementImpressions();
	void incrementClicks();
	void setUrl(string url);
	void setImpressions(double impressions);
	void setClicks(double clicks);
	void setVertexNo(int number);
	void appendKeyword(string word);
	void printWebPage();
};

