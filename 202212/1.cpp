#include <bits/stdc++.h>
using namespace std;
int n;
double c;
int main()
{
    scanf("%d%lf", &n, &c);
    double ans = 0;
    c = 1 + c;
    for(int i = 0; i <= n; i++){
        double t;
        scanf("%lf", &t);
        double vv = pow(c, -i);
        ans += t * vv;
    }
    printf("%lf\n", ans);
    return 0;
}