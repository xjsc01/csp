#include <bits/stdc++.h>
using namespace std;
int n, m;
typedef pair<double, double> PDD;
PDD a[200000];
int main()
{
    a[0].first = 1;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        double x, y;
        scanf("%lf%lf", &x, &y);
        a[i] = a[i - 1];
        if(x == 1){
            a[i].first *= y;
        }
        else{
            a[i].second += y;
        }
    }
    for(int i = 1; i <= m; i++){
        int o1, o2;
        double x, y;
        scanf("%d%d%lf%lf", &o1, &o2, &x, &y);
        PDD now = {a[o2].first / a[o1 - 1].first, a[o2].second - a[o1 - 1].second};
        double x1, y1;
        x1 = x*cos(now.second)-y*sin(now.second);
        y1 = x*sin(now.second)+y*cos(now.second);
        x1 *= now.first;
        y1 *= now.first;


        printf("%f %f\n", x1, y1);
    }

    return 0;
}