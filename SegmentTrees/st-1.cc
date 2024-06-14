// Only queries after the inicialization.


#include <bits/stdc++.h>
using namespace std;


const int INF = 1e9;


using VI = vector<int>;


int n;
VI V;
VI ST;


void print() {
  for (int i = 0; i < 4*n; ++i) cout << ' ' << setw(2) << i;
  cout << endl;
  for (int x : ST) cout << ' ' << setw(2) << x;
  cout << endl;
}


int query(int p, int l, int r, int e, int d) {
  if (l == e and r == d) return ST[p];

  int m = (l + r)/2;
  int pl = 2*p;
  int pr = pl + 1;
  int res = -INF;
  if (e <= m) res = max(res, query(pl, l, m, e, min(m, d)));
  if (d > m) res = max(res, query(pr, m + 1, r, max(m + 1, e), d));
  return res;
}


void ini(int p, int l, int r) {
  if (l == r) {
    ST[p] = V[l];
    return;
  }

  int m = (l + r)/2;
  int pl = 2*p;
  int pr = pl + 1;
  ini(pl, l, m);
  ini(pr, m + 1, r);
  ST[p] = max(ST[pl], ST[pr]);
}


int main() {
  cin >> n;
  V = VI(n);
  for (int& x : V) cin >> x;

  ST = VI(4*n);
  ini(1, 0, n - 1);

  print();

  int e, d;
  while (cin >> e >> d) cout << query(1, 0, n - 1, e, d) << endl;
}
