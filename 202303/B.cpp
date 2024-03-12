#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int n, m, k;
int t[N], c[N];

bool ck(int mid){
    int all = 0;
    for(int i = 1; i <= n; i++){
        all += max(0, (t[i] - mid) * c[i]);
    }
    if(all <= m) return true;
    else return false;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    int r = 0;
    for(int i = 1; i <= n; i++){
        scanf("%d%d", t + i, c + i);
        r = max(r, t[i]);
    }
    int l = k;
    while(l < r){
        int mid = (l + r) >> 1;
        if(ck(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}