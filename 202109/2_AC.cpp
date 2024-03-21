#include <bits/stdc++.h>
using namespace std;
const int N = 6e5;
const int M = 1e4 + 10;
int a[N];
int ca[M+20];
int n;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", a + i);
    }
    a[0] = a[n + 1] = -1;
    n = unique(a, a + n + 2) - a - 2;
    for(int i = 1; i <= n; i++){
        if(a[i] < a[i+1] && a[i] < a[i-1]){
            ca[a[i]+1]++;
        }
        else if(a[i] > a[i+1] && a[i] > a[i-1]){
            ca[a[i]+1]--;
        }
    }
    int ans = 0;
    for(int i = 1, sum = 1; i <= M; i++){
        sum += ca[i];
        ans = max(ans, sum);
    }
    printf("%d\n", ans);
    return 0;
}