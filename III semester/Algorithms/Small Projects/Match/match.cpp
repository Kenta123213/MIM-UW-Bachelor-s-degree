#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    int m;
    cin >> n;
    cin >> m;
    uint64_t tab[n];
    for (int i = 0; i < n; i++) tab[i] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n/2; j++){
            int x;
            cin >> x;
            tab[x - 1] <<= 1;
            tab[x - 1] ++;
            
        }
        for (int j = n/2; j < n; j++){
            int x;
            cin >> x;
            tab[x - 1] <<= 1;
        }
    }
    sort(tab, tab + n);
    int max = 1;
    int counter = 1;
    uint64_t x = tab[0];
    for(int i = 1; i < n; i++) {
        if (tab[i] == x) {
            counter++;
            if (counter > max) max = counter;
        }
        else counter = 1;
        x = tab[i];
    }
    cout << max;
}