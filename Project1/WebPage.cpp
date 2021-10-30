#include "WebPage.h"

WebPage::WebPage(const string url, int vertexNo) {
    this->vertexNo = vertexNo;
    clicks = 0;
  

    this->url = url;
    //this->clicks = clicks;
    //ctr = clicks/ this->impressions;
    //cout << this->clicks;
    //cout << "ctr = " << ctr << endl;
}

WebPage::WebPage()
{
    clicks = 0;
    impressions = 0;
    ctr = 0;
    url = "";
    vertexNo = 0;

}

string WebPage::getUrl()
{
    return url;
}

double WebPage::getImpressions()
{
    return impressions;
}

double WebPage::getClicks()
{
    return clicks;
}

double WebPage::getCTR()
{
    return ctr;
}

int WebPage::getVertexNo() const
{
    return vertexNo;
}

void WebPage::incrementClicks()
{
    //cout << getClicks() << endl;
    clicks +=1;
    updateCTR();
    //cout << getClicks();
}

void WebPage::setUrl(string url)
{
    this->url = url;
}

void WebPage::setImpressions(double impressions)
{
    this->impressions = impressions;
    updateCTR();
}

void WebPage::setClicks(double clicks)
{
    this->clicks = clicks;
    updateCTR();
}

void WebPage::setVertexNo(int number)
{
    this->vertexNo = number;
}

void WebPage::appendKeyword(string word)
{
    keywords.push_back(word);
}

void WebPage::incrementImpressions()
{
    impressions += 1;
    updateCTR();
}

void WebPage::printWebPage()
{
    cout << endl;
    cout << "URL: " << getUrl() << "; ";
    cout << "Vertex Number: " << getVertexNo() << "; ";
    cout << "Impressions: " << getImpressions() << "; ";
    cout << "Clicks: " << getClicks() << "; ";
    cout << "CTR: " << getCTR() << "; ";
    cout << "keywords: ";
    for (int i = 0; i < keywords.size(); i++)
    {
        cout << keywords[i] << " ";
    }
    
}

void WebPage::updateCTR()
{
    ctr = getClicks() / getImpressions();
}


