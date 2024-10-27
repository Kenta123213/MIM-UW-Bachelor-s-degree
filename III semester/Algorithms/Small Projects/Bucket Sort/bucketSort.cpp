#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int n;
vector<vector<vector<int>>> tab;

void dp (int i, int j, int k, int a[]);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    tab.resize(n, vector<vector<int>>(n, vector<int>(2, -1)));
    dp(0, n - 1, 0, a);
    dp(0, n - 1, 1, a);
    
    cout << (tab[0][n - 1][0] + tab[0][n - 1][1]) % 1000000000 << endl;
    
    return 0;
}

void dp (int i, int j, int k, int a[]) {
    if (j - i == 0) {
        tab[i][j][0] = 1;
        tab[i][j][1] = 0;
    }
    else {
        if (k == 0) {
            if (tab[i][j][0] == -1 && i + 1 < n) {
                dp(i + 1, j, 0, a);
                dp(i + 1, j, 1, a);
                tab[i][j][0] = ((a[i] < a[i + 1] ? 1 : 0) * tab[i + 1][j][0] + 
                (a[i] < a[j] ? 1 : 0) * tab[i + 1][j][1]) % 1000000000;
            }
        }
        else {
            if (tab[i][j][1] == -1 && j - 1 >= 0) {
                dp(i, j - 1, 0, a);
                dp(i, j - 1, 1, a);
                tab[i][j][1] = ((a[j] > a[i] ? 1 : 0) * tab[i][j - 1][0] + 
                (a[j] > a[j - 1] ? 1 : 0) * tab[i][j - 1][1]) % 1000000000;
            }
        }
    }
}