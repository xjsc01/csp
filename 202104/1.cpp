#include <bits/stdc++.h>
using namespace std;
const int N = 600;
// int a[N][N];
int n, m, L;
int sum[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> L;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int t;
            cin >> t;
            sum[t]++;
        }
    }
    for(int i = 0; i < L; i++){
        if(i!=0) cout << " ";
        cout << sum[i];
    }
    cout << '\n';
    return 0;
}