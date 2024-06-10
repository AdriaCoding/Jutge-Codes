#include <iostream>
#include <set>
#include <vector>
#include <numeric>

using namespace std;

class Treap {
public:
    set<int> treap;
    
    bool insert(int z) {
        auto result = treap.insert(z);
        return result.second;
    }
};

int main() {
    int m;
    while (cin >> m) {
        if (m == 0) break;
        
        Treap treap;
        treap.insert(0);  // Initial element

        vector<int> elements = {0};  // Start with 0
        while (m--) {
            int y, i, j;
            cin >> y >> i >> j;

            // Calculate the sum in the range i to j (1-based index)
            int sum = accumulate(elements.begin() + i, elements.begin() + j + 1, 0);

            // Calculate z
            int z = (y + sum) % 1000000000;

            // Insert z into treap and print the result
            if (treap.insert(z)) {
                cout << "I " << z << endl;
                elements.push_back(z);  // Maintain elements in sorted order
            } else {
                cout << "R " << z << endl;
            }
        }
        cout << "----------" << endl;
    }
    return 0;
}
