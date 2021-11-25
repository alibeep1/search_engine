#include"Trie.h"

// Iterative function to insert a key into a Trie
void Trie::insert(string key, string page)
{
    // start from the root node
    Node* curr = &node;
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if the path doesn't exist
        if (curr->character[key[i]] == nullptr) {
            curr->character[key[i]] = new Node();
        }

        // go to the next node
        curr = curr->character[key[i]];

    }

    // mark the current node as a leaf
    curr->isLeaf = true;
    curr->pages.push_back(page);
}

void Trie::insertNode(Node)
{

}

// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
vector<string> Trie::search(string key)
{
    vector<string> vec;
    vec.resize(0);
    // return false if Trie is empty
    if (this->node.character == nullptr) {
        return vec;
        //return false;
    }

    Node* curr = &node;
    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[key[i]];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return vec;
            //return false;
        }
    }

    return curr->pages;
    //for (int i = 0; i < curr->pages.size(); i++)
    //{
    //    vec.push_back(curr->pages[i]);
    //   /* cout << curr->pages[i].getUrl();
    //    cout << endl;*/
    //}
    // return true if the current node is a leaf and the
    // end of the string is reached
    //return vec;
    //return curr->isLeaf;
}

// Returns true if a given node has any children
bool Trie::haveChildren(Node const* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // child found
        }
    }

    return false;
}

// Recursive function to delete a key in the Trie

// C++ implementation of Trie data structure
