#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int>PII;
int n, k, t;
PII ld, ru;
#define N 2000
int jin[N], dou[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> k >> t >> ld.first >> ld.second >> ru.first >> ru.second;
    
    for(int i = 1; i <= n; i++){
        int cnt = 0;
        for(int j = 1; j <= t; j++){
            int x, y;
            cin >> x >> y;
            if(x >= ld.first && x <= ru.first
            && y >= ld.second && y <= ru.second){
                cnt++;
            }
            else{
                cnt = 0;
            }
            if(cnt) jin[i] = 1;
            if(cnt >= k) dou[i] = 1;
        }
    }
    int ans1=0, ans2=0;
    for(int i = 1; i <= n; i++){
        ans1 += jin[i];
        ans2 += dou[i];
    }
    cout << ans1 << "\n" << ans2 << "\n";
    return 0;   
}