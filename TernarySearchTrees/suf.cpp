#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef struct Node* TST;

struct Node {
    char c;
    int size;
    bool end;
    TST l, m, r;
};

TST newNode(char c) {
    TST t = new Node();
    t->c = c;
    t->size = 0;
    t->end = false;
    t->l = t->m = t->r = nullptr;
    return t;
}

void reset(TST& t) {
    if (!t) {
        return;
    }
    reset(t->l);
    reset(t->m);
    reset(t->r);
    delete t;
    t = nullptr;
}

bool insert(TST& t, const string& word, int i) {
    if (!t) {
        t = newNode(word[i]);
    }
    if (word[i] < t->c) return insert(t->l, word, i);
    if (word[i] > t->c) return insert(t->r, word, i);
    bool inserted = false;
    if (i < word.size() - 1) inserted = insert(t->m, word, i + 1);
    else if (!t->end) {
        t->end = true;
        inserted = true;
    }
    if (inserted) {
        t->size++;
    }
    return inserted;
}

bool erase(TST& t, const string& word, int i) {
    if (!t) {
        return false;
    }
    if (word[i] < t->c) return erase(t->l, word, i);
    if (word[i] > t->c) return erase(t->r, word, i);
    bool deleted = false;
    if (i < word.size() - 1) deleted = erase(t->m, word, i + 1);
    else if (t->end) {
            t->end = false;
            deleted = true;
    }
    if (deleted) {
        t->size--;
        // Only delete the node if it has no children and is not the end of a string
        if (t->size == 0 && !t->end && !t->l && !t->m && !t->r) {
            delete t;
            t = nullptr;
        }
    }
    return deleted;
}

int count(Node* t, const string& s, int i) {
    if (!t) return 0;
    if (s[i] < t->c) return count(t->l, s, i);
    else if (s[i] > t->c) return count(t->r, s, i);
    else {
        if (i < s.size() - 1) return count(t->m, s, i + 1);
        else return t->size;
    }
}

void printTST(TST t, string prefix = "") {
    if (!t) return;
    string current = prefix + t->c;
    cout << "Char: " << t->c << ", Size: " << t->size << endl;
    if (t->l) {
        cout << "   Left child of " << t->c << ": " << t->l->c << endl;
    }
    if (t->m) {
        cout << "   Middle child of " << t->c << ": " << t->m->c << endl;
    }
    if (t->r) {
        cout << "   Right child of " << t->c << ": " << t->r->c << endl;
    }
    printTST(t->l, current);
    printTST(t->m, current + t->c);
    printTST(t->r, current);
}
void dome(TST root, string t) {
    for (char& c : t) {
        cout << c << "-";
    }
    cout << endl;
    printTST(root);
    cout << endl << endl;
}

string reverseString(string s) {
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    TST t = nullptr;
    bool nani = false;
    string op, s;
    while (cin >> op) {
        if (op == "R"){
            reset(t);
            cout << "---" << endl;
        }
        else{
            cin >> s;
            s = reverseString(s);
        }

        if (op == "I") {
            insert(t, s, 0);
        } else if (op == "E") {
            erase(t, s, 0);
        } else if (op == "C") {
            cout << count(t, s, 0) << endl;
        }

    }
    return 0;
}