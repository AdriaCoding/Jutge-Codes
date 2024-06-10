#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;
    int count = 0;
};

class Trie {
public:
    TrieNode* root = new TrieNode();

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->count++;
        }
    }

    void query(string prefix) {
        TrieNode* node = root;
        cout << prefix << ": ";
        for (char c : prefix) {
            if (!node->children[c]) {
                cout << "0 ";
                break;
            }
            node = node->children[c];
            cout << node->count << " ";
        }
        cout << endl;
    }
};

int main() {
    Trie trie;
    string line;
    while (getline(cin, line)) {
        if (line.find(' ') != string::npos) {
            stringstream ss(line);
            string t, s;
            ss >> t >> s;
            trie.insert(t);
        } else {
            trie.query(line);
        }
    }
    return 0;
}