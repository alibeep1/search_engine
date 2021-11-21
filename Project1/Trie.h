#include <iostream>
#include"WebPage.h"
using namespace std;

// Define the character size
#define CHAR_SIZE 128

struct Node {
    bool isLeaf;
    Node* character[CHAR_SIZE];
    vector<string> pages;
};
// A class to store a Trie node
class Trie
{
public:
    Node node;
    /*bool isLeaf;
    Trie* character[CHAR_SIZE];*/

    // Constructor
    Trie()
    {
        this->node.isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++) {
            this->node.character[i] = nullptr;
        }
    }

    void insert(string, string);
    void insertNode(Node);

    vector<string> search(string);
    bool haveChildren(Node const*);
};