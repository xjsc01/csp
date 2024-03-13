#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 400;
int a[N];
vector<int> son[N];
int fast[N], last[N];
int fa[N];
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int t;
        scanf("%d", &t);
        son[t].push_back(i);
        fa[i] = t;
    }
    for(int i = 1; i <= m; i++){
        scanf("%d", a + i);
    }
    bool ok = true;
    for(int i = 1; i <= n; i++){
        fast[i] = max(fast[i], 1);
        for(int y : son[i]){
            fast[y] = max(fast[y], fast[i] + a[i]);
        }
        if(fast[i] + a[i] - 1 > n) ok = false;
    }
    for(int i = 1; i <= m; i++){
        if(i != 1) printf(" ");
        printf("%d", fast[i]);
    }
    puts("");
    if(!ok) return 0;
    for(int x = n; x >= 1; x --){
        last[x] = n - a[x] + 1;
        for(int y : son[x]){
            last[x] = min(last[x], last[y] - a[x]);
        }
    }
    for(int i = 1; i <= m; i++){
        if(i != 1) printf(" ");
        printf("%d", last[i]);
    }
    puts("");
    return 0;
}