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

int longest_palindromic_suffix(string s) {
    string r = s;
    reverse(r.begin(), r.end());
    string t = r + "#" + s;
    vector<int> P = kmp(t);
    return P.back();
}

int main(){
    string s;
    while (cin >> s) {
        cout << longest_palindromic_suffix(s) << endl;
    }
    return 0;
}