#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 1e3 + 30;
const int M = 12;
int a[N][M];

bool ck(int i, int j){
    for(int x = 1; x <= m; x++){
        if(a[i][x] >= a[j][x]) return false;
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &a[i][j]);
        }
    }

    for(int i = 1; i <= n; i++){
        int ans = 0;
        for(int j = 1; j <= n; j++){
            if(ck(i, j)){
                ans = j;
                break;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}