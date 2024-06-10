#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef struct Node* TST;

struct Node {
    char c;
    int count;
    TST l, m, r;
};


TST newNode(char c) {
    TST t = new Node();
    t->c = c;
    t->count = 0;
    t->l = t->m = t->r = nullptr;
    return t;
}

void insert(TST& t, const string& word, int i) {
    if (i < word.size()) {
        if (!t) {
            t = newNode(word[i]);
        }
        if (word[i] < t->c) {
            insert(t->l, word, i);
        } else if (word[i] > t->c) {
            insert(t->r, word, i);
        } else {
            if (i < word.size() - 1) {
                insert(t->m, word, i + 1);
            }
            t->count++;
        }
    }
}

void search(TST t, const string& word, int i) {
    if (!t) {
        cout << " 0";
        return;
    }
    if (i == word.size()) {
        cout << " " << t->count;
        return;
    }
    if (word[i] < t->c) search(t->l, word, i);
    else if (word[i] > t->c) search(t->r, word, i);
    else {
        cout << " " << t->count;
        if (i < word.size() - 1) search(t->m, word, i + 1);
    }
}

void printTST(TST t, string prefix = "") {
    if (!t) return;
    string current = prefix + t->c;
    cout << "Char: " << t->c << ", Count: " << t->count << endl;
    if (t->l) {
        cout << "Left child of " << t->c << ": " << t->l->c << endl;
        printTST(t->l, current);
    }
    if (t->m) {
        cout << "Middle child of " << t->c << ": " << t->m->c << endl;
        printTST(t->m, current + t->c);
    }
    if (t->r) {
        cout << "Right child of " << t->c << ": " << t->r->c << endl;
        printTST(t->r, current);
    }
}

void dome(TST root, string t) {
    for (char& c : t) {
        cout << c << "-";
    }
    cout << endl;
    printTST(root);
    cout << endl << endl;
}
int main() {
    TST root = NULL;
    string line;
    while (getline(cin, line)) {
        if (line.find(' ') != string::npos) {
            stringstream ss(line);
            string t, s;
            ss >> t >> s;
            insert(root, t, 0);
            //dome(root,   t);
        } else {
            cout << line << ":";
            search(root, line, 0);
            cout << endl;
        }
    }
    return 0;
}