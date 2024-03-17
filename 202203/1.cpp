#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int n, k;
bool a[N];
int main()
{
    int ans = 0;
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    a[0] = true;
    cin >> n >> k;
    for(int _ = 1; _ <= k; _++){
        int x, y;
        cin >> x >> y;
        if(!a[y]) {
            ans ++;
            // cout << _ << "\n";
        }
        a[x] = true;
    }
    cout << ans;    
    return 0;
}