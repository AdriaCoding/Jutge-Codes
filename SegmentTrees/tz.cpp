#include <bits/stdc++.h>
using namespace std;

using ST = struct Node*;


struct Node{
    double l, r, yl, yr;
    ST lt, rt;
    
    double height(double x) const {
        // we are guaranteed that l < r
        if (x < l) return 0;
        if (x > r) return 0;
        double slope = (yr - yl) / (r - l);
        return yl + slope * (x - l);
    }
    Node(double l, double r, double yl=0, double yr=0):
         l(l), r(r), yl(yl), yr(yr),
         lt(nullptr), rt(nullptr) {}
};

double height(double x, double l, double r, double yl, double yr) {
    // we are guaranteed that l < r
    if (x < l) return 0;
    if (x > r) return 0;
    double slope = (yr - yl) / (r - l);
    return yl + slope * (x - l);
}

void print_tree(ST t) {
    if (!t) return;
    print_tree(t->lt);
    std::cout << "Key: [" << t->l << "-" << t->r << "], abcises: ->" << t->yl << " " << t->yr << "\n";
    if (t->lt && t->rt && t->lt->r == t->rt->l)    
        cout << "     midpoint = " << t->rt->l << endl;
    print_tree(t->rt);
}


void update(ST& t, double l, double r, double yl, double yr){ 
    if (!t) {
        //if (l == r) return;
        t = new Node(l, r, yl, yr);    
        return;
    }
    double cut, ycut;
    if(t->lt) {
        cut = t->lt->r;
        if(cut > r) return update(t->lt, l, r, yl, yr);
        else if (cut > l) {
            ycut = height(cut, l, r, yl, yr);
            update(t->lt, l, cut, yl, ycut);
        }
    }
    if(t->rt) {
        cut = t->rt->l;
        if(cut < l) return update(t->rt, l, r, yl, yr);
        else if (cut < r){
            ycut = height(cut, l, r, yl, yr);
            update(t->rt, cut, r, ycut, yr);
        }
    }
    if (!t->rt && !t->lt){
        // I can suppose that t->l<= l < r <= t->r
        if (t->l == l && t->r == r) {
            t->yl += yl;
            t->yr += yr;
            return;
        }
        // Here we assume t->l  < l || r < t->r
        cut = (l == t->l ? r : l);
        ycut = t->height(cut);
        t->lt = new Node(t->l, cut, t->yl, ycut);
        t->rt = new Node(cut, t->r, ycut, t->yr);
        if (t->l < l && r < t->r){
            // we have to split the rightmost node into 2 nodes
            double hl = t->height(l);
            double hr = t->height(r);
            t->rt->lt = new Node(l, r, hl + yl, hr + yr);
            t->rt->rt = new Node(r, t->r, hr, t->yr);
        }
                   
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
                //print_tree(root); cout << endl;
            } else {
                double x;
                cin >> x;
                cout << fixed << setprecision(3) << query(root, x) << endl;
            }
        }
    }
}
