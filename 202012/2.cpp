#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> mp;
pair<int, int> in[200000];
int a[00000];
int getIdx(int x){
    return lower_bound(mp.begin(), mp.end(), x) - mp.begin();
}
signed main()
{
    int n;
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld", &in[i].first, &in[i].second);
        mp.push_back(in[i].first);
    }
    sort(mp.begin(), mp.end());
    mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for(int i = 1; i <= n; i++){
        auto &x = in[i];
        if(x.second == 1){
            a[0]++;
            a[getIdx(x.first)+1]--;
        }
        else{
            a[getIdx(x.first)+1]++;
            a[mp.size()]--;
        }
    }
    for(int i = 1; i <= (int)mp.size(); i++){
        a[i] += a[i - 1];
    }
    int ans = 0;
    for(int i = 0; i < (int)mp.size(); i++){
        if(a[i] >= a[ans]) ans = i;
    }
    printf("%lld\n", mp[ans]);
    return 0;
}