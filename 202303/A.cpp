#include <bits/stdc++.h>
using namespace std;
int n, a, b;
int main()
{
    int ans = 0;
    scanf("%d%d%d", &n, &a, &b);
    for(int i = 1; i <= n; i++){
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 = max(x1, 0), y1 = max(y1, 0);
        x2 = min(x2, a), y2 = min(y2, b);
        ans += max(0, x2-x1) * max(0, y2-y1);
    }
    printf("%d\n", ans);
    return 0;
}