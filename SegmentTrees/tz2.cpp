#include <bits/stdc++.h>
using namespace std;

using ST = struct Node*;


struct Node{
    double l, r, yl, yr;
    ST lt, rt;

    double height(double x) const {
        if (x < l) return 0;
        if (x > r) return 0;
        double slope = (yr - yl) / (r - l);
        return yl + slope * (x - l);
    }

    Node(double l, double r, double yl=0, double yr=0):
         l(l), r(r), yl(yl), yr(yr),
         lt(nullptr), rt(nullptr) {}
};

void print_tree(ST t) {
    if (!t) return;
    print_tree(t->lt);
    std::cout << "Key: [" << t->l << "-" << t->r << "], abcises: ->" << t->yl << " " << t->yr << "\n";
    if (t->lt && t->rt && t->lt->r == t->rt->l)    
        cout << "     midpoint = " << t->rt->l << endl;
    print_tree(t->rt);
}


void update(ST& t, double l, double r, double yl, double yr) {
    if (!t) {
        t = new Node(l, r, yl, yr);
        return;
    }

    // Handle partial overlaps and split nodes if necessary
    if (r <= t->l) {
        if (!t->lt) {
            t->lt = new Node(l, r, yl, yr);
        } else {
            update(t->lt, l, r, yl, yr);
        }
    } else if (l >= t->r) {
        if (!t->rt) {
            t->rt = new Node(l, r, yl, yr);
        } else {
            update(t->rt, l, r, yl, yr);
        }
    } else {
        // Partial overlaps require splitting the current node
        double hl = t->height(l);
        double hr = t->height(r);

        if (l > t->l) {
            if (!t->lt) t->lt = new Node(t->l, l, t->yl, hl);
            else update(t->lt, t->l, l, t->yl, hl);
        }
        if (r < t->r) {
            if (!t->rt) t->rt = new Node(r, t->r, hr, t->yr);
            else update(t->rt, r, t->r, hr, t->yr);
        }

        if (!t->lt && !t->rt) {
            t->lt = new Node(t->l, l, t->yl, hl);
            t->rt = new Node(r, t->r, hr, t->yr);
        }

        t->l = l;
        t->r = r;
        t->yl = yl;
        t->yr = yr;
    }
}

double query(ST& t, double x) {
    if (!t) return -1.0; //no se si es pot arribar aquí mai
    if (t->lt && x < t->lt->r) return query(t->lt, x);
    if (t->rt && x > t->rt->l) return query(t->rt, x);
    return t->height(x); //potser cal contemplar mes casos
}

int main(){
    int n;
    while(cin >> n){
        ST root = new Node(0, 1e4, 0, 0);
        for(int i=1; i<= n; i++){
            char op;
            cin >> op;
            if(op == 'A') {
                double l, r, yl, yr;
                cin >> l >> r >> yl >> yr;
                update(root, l, r, yl, yr);
                print_tree(root);
                cout << endl;
            } else {
                double x;
                cin >> x;
                cout << fixed << setprecision(3) << query(root, x) << endl;
            }
        }
    }
}
