#include <bits/stdc++.h>
using namespace std;
int n;
double a[1000000];
int main()
{
    scanf("%d", &n);
    double sum = 0;
    for(int i = 1; i <= n; i++){
        scanf("%lf", a + i);
        sum += a[i];
    }
    double avg = sum / n;
    double D = 0;
    for(int i = 1; i <= n; i++){
        D += (a[i] - avg) * (a[i] - avg);
    }
    D /= n;
    double GD = sqrt(D);
    for(int i = 1; i <= n; i++){
        printf("%.8lf\n", (a[i] - avg) / GD);
    }
    return 0;
}