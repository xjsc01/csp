#include <bits/stdc++.h>
using namespace std;
int n, m, k;
const int N = 3e5 + 30;
int a[N], sum[N];

// 使用前缀和思想
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++){
        int y, d;
        cin >> y >> d;
        int x = max(y - d + 1, 0);
        a[x]++;
        a[y+1]--;
    }
    sum[0] = a[0];
    for(int i = 1; i < N; i++){
        sum[i] = sum[i-1] + a[i];
    }
    for(int i = 1; i <= m; i++){
        int t;
        cin >> t;
        t += k;// 现在是核酸结果出来的时候
        cout << sum[t] << "\n";
    }
    return 0;
}