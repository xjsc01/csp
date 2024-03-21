#include <bits/stdc++.h>
using namespace std;
const int N = 3000;
int a[N];
int n;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    long long minv = 0, maxv = 0;

    for(int i = 1; i <= n; i++){
        if(a[i] == a[i - 1]){
            minv += 0;
            maxv += a[i];
        }
        else{
            minv += a[i];
            maxv += a[i];
        }
    }
    cout << maxv << "\n" << minv << "\n";
    return 0;
}