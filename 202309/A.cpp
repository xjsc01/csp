#include <bits/stdc++.h>
using namespace std;
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    int dx = 0, dy =0 ;
    for(int i = 1;i <= n; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        dx += x;
        dy += y;
    }
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d %d\n", x + dx, y + dy);
    }
    return 0;
}