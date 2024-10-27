#include <stdio.h>
 
int main()
{
    int n;
    int m;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    int x[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &x[i]);
    }
 
    long long b[n];
    long long sum = 0;
    int minp = -1; //indeks najmniejszej parzystej w sumie
    int minn = -1;  //indeks najmniejszej nieparzystej w sumie
    int nextp = -2; //indeks nastepnej parzystej (-2 oznacza że jeszcze nie szukany, -1 że już nie ma parzystych)
    int nextn = -2;
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) {
            if (a[i] % 2 == 1) {
                b[i] = a[i];
                minn = i;
            }
            else {
                int j = n - 2;
                while (j >= 0 && a[j] % 2 == 0) {
                    j--;
                }
                if (j < 0) {
                    nextn = -1;
                    b[i] = -1;
                }
                else {
                    nextn = j;
                    b[i] = a[nextn];
                }
                minp = i;
            }
            sum = a[i];
        }
        else {
        if (a[i] % 2 == 1) minn = i;
            else minp = i;
 
        if ((a[i] + sum) % 2 == 1) {
            b[i] = a[i] + sum;
        }
        else {
            if (i == 0) b[i] = -1;
            long long sum1 = 0;   //zastapienie parzystej
            long long sum2 = 0;   //zastapienie nieparzystej
            //szukanie parzystej do zastapienia najmniejszej nieparzystej
            if (minn != -1) {
                if (nextp >= i || nextp == -2) {
                    int j = i - 1;
                    while (j >= 0 && a[j] % 2 == 1) {
                        j--;
                    }
                    if (j < 0) nextp = -1;
                    else { 
                        nextp = j;
                        sum2 = a[i] + sum - a[minn] + a[nextp];
                    }
                } else if (nextp < i && nextp > -1) {
                    sum2 = a[i] + sum - a[minn] + a[nextp];
                }
            }
            //szukanie nieparzystej do zastapienia najmniejszej parzystej
            if (minp != -1) {
                if (nextn >= i || nextn == -2) {
                    int j = i - 1;
                    while (j >= 0 && a[j] % 2 == 0) {
                        j--;
                    }
                    if (j < 0) nextn = -1;
                    else { 
                        nextn = j;
                        sum1 = a[i] + sum - a[minp] + a[nextn];
                    }
                } else if (nextn < i && nextn > -1) {
                    sum1 = a[i] + sum - a[minp] + a[nextn];
                }
            }
            if (sum1 == 0 && sum2 == 0) b[i] = -1;
            else if (sum1 > sum2) b[i] = sum1;
            else b[i] = sum2;
        }
        sum = a[i] + sum;
        }
    }
    for (int i = 0; i < m; i++) {
        printf("%lld\n", b[n - x[i]]);
    }
}