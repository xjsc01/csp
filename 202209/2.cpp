#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 4e5;
int a[N];
int dp[N];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", a + i);
    }
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 1; i <= n; i++){
        for(int j = m; j >= 1; j--){
            if(j - a[i] <= 0){
                dp[j] = min(dp[j], a[i]);
            }
            else{
                dp[j] = min(dp[j], a[i] + dp[j - a[i]]);
            }
        }
    }
    printf("%d\n", dp[m]);
    return 0;
}