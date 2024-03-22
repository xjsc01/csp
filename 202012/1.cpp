#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        int x, y;
        cin >> x >> y;
        ans += x * y;
    }
    ans = max(0LL, ans);
    cout << ans << "\n";
    return 0;
}