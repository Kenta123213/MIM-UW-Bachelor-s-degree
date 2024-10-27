#include <iostream>
#include <string>
using namespace std;

int main()
{
    string wzor;
    cin >> wzor;
    char ostatni;
    int min = -1;
    int i = 0;
    bool x = true;
    bool y = false;
    for (int j = 0; j < wzor.length() - 1; j++) {
        if (wzor[j] != '*' && wzor[j+1] != '*' && wzor[j] != wzor[j + 1]) x = false;
    }
    if (x) {
    while (wzor[i] == '*') i++;
    while (i < wzor.length()){
        if (wzor[i] == '*') {
            int j = 0;
            while (i < wzor.length() && wzor[i] == '*') {
                i++;
                j++;
            }
            if (i != wzor.length()) {
                if (wzor[i] != ostatni) {
                    y = true;
                    if (min == -1) min = j;
                    else if (min > j) min = j;
                    ostatni = wzor[i];
                }
            }
        } else {
            ostatni = wzor[i];
        }
        i++;
    }
    }
    if (!x) {
        cout << wzor.length();
    } else if (!y) {
        cout << 1;
    } else {
        cout << wzor.length() - min;
    }
    return 0;
}