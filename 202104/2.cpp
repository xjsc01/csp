#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 800;
int a[N][N];
int n, L, R, T;
// int sum[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> L >> R >> T;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            a[i][j] += a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int x1, x2, y1, y2;
            x1 = i - R, y1 = j - R;
            x1 = max(1LL, x1), y1 = max(1LL, y1);
            x2 = i + R, y2 = j + R;
            x2 = min(n, x2), y2 = min(n, y2);
            int ret = a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
            int chu = (x2-x1+1)*(y2-y1+1);
            if(ret <= chu * T) 
            {
                // cout << "(" << i << ", " << j << ")\n";
                ans++;   
            }
        }
    }
    
    cout << ans << '\n';
    return 0;
}