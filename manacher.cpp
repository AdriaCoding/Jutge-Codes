#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longest_palindromic_suffix(string s) {
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }
    int n = t.size();
    vector<int> P(n);
    int C = 0, R = 0;
    for (int i = 1; i < n - 1; i++) {
        int i_mirror = 2 * C - i;
        if (R > i) {
            P[i] = min(R - i, P[i_mirror]);
        }
        while (t[i + 1 + P[i]] == t[i - 1 - P[i]]) {
            P[i]++;
        }
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
    int len = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (i - P[i] == 0) {
            len = max(len, P[i]);
        }
    }
    return len;
}

int main(){
    string s;
    while (cin >> s) {
        cout << longest_palindromic_suffix(s) << endl;
    }
    return 0;
}