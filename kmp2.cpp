#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> kmp(string s){
    int n = s.size();
    vector<int> P(n);
    int j = -1;
    for (int i = 0; i < n; i++){
        while(j >= 0 and s[i] != s[j]) j = (j ? P[j-1]: -1);
        P[i] = ++j;
    }
    return P;
}

int count_rotations(string s, string t) {
    string u = s + s;
    vector<int> P = kmp(t + "#" + u);
    int count = 0;
    for (int i = t.size() + 1; i < P.size() - 1; i++) {
        if (P[i] == t.size()) count++;
    }
    return count;
}

int main(){
    string s, t;
    while (cin >> s >> t) {
        cout << count_rotations(s, t) << endl;
    }
    return 0;
}