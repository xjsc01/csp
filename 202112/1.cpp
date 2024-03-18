#include <bits/stdc++.h>
using namespace std;
int a[400];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, N;
    cin >> n >> N;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans = ans + ((long long)a[i] - a[i - 1]) * (i - 1);
    }
    ans += (N - a[n]) * n;
    cout << ans;
    return 0;
}