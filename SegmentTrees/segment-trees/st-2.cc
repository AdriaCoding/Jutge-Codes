// Position updates.


#include <bits/stdc++.h>
using namespace std;


const int INF = 1e9;


using VI = vector<int>;


int n;
VI ST;


void print() {
  for (int i = 0; i < 4*n; ++i) cout << ' ' << setw(2) << i;
  cout << endl;
  for (int x : ST) cout << ' ' << setw(2) << x;
  cout << endl;
}


void update(int p, int l, int r, int i, int x) {
  if (l == r) {
    ST[p] = x;
    return;
  }

  int m = (l + r)/2;
  int pl = 2*p;
  int pr = pl + 1;
  if (i <= m) update(pl, l, m, i, x);
  else update(pr, m + 1, r, i, x);
  ST[p] = max(ST[pl], ST[pr]);
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


int main() {
  cin >> n;
  ST = VI(4*n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    update(1, 0, n - 1, i, x);
  }

  print();

  char c;
  while (cin >> c) {
    if (c == 'q') {
      int e, d;
      cin >> e >> d;
      cout << query(1, 0, n - 1, e, d) << endl;
    }
    else {
      int i, x;
      cin >> i >> x;
      update(1, 0, n - 1, i, x);
      print();
    }
  }
}
