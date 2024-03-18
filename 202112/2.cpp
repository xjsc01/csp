#include <bits/stdc++.h>
using namespace std;
#define int long long
const int M = 2e5;
int f[M], g[M], a[M];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, N;
    cin >> n >> N;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    a[n + 1] = N;
    int ans = 0;
    int r = 0;
    r = (N) / (n + 1);
    int now, nxtf, nxtg, idx, valf, valg;
    now = 0;
    idx = 1;
    nxtf = now + a[idx] - a[idx - 1];
    nxtg = now + r;
    valf = idx - 1;
    valg = now / r;
    while(now < N){
        ans += abs(valf - valg)*(min(nxtg, nxtf) - now);
        // cout << ans << "   ";
        now = min(nxtg, nxtf);
        if(nxtf > nxtg){
            nxtg = now + r;
            valg = now / r;
        }
        else {
            idx ++;
            valf = idx - 1;
            nxtf = now + a[idx] - a[idx-1];
        }
    }
    cout << ans;
    return 0;
}