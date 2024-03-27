#include <bits/stdc++.h>
using namespace std;
int n, m, r;
array<int, 101> a[3000], c;

double distF(){

}

double getMin(int u, int v){
    array<double, 4>zhi;
    if(a[u][0] == a[v][0]){
        zhi[0] = 0, zhi[1] = 1, zhi[2] = a[u][1];
    }
    else{
        double k = (a[u][1] - a[v][1]) / (a[u][0] - a[v][0]);
        double b = a[u][1] - k*a[u][0];
        zhi[0] = k;
        zhi[1] = -1;
        zhi[2] = b;
    }
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> r;
    cin >> c[0] >> c[1];
    for(int i = 1; i <= m; i++){
        cin >> a[i][0] >> a[i][1];
    }
    for(int i = 1; i <= m; i++){
        double ans = 0;
        for(int j = 1; j <= m; j++){
            if(i == j) continue;
            ans += getMin();
        }
        cout << ans << "\n";
    }

    return 0;
}