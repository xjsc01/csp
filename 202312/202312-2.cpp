#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> z;
void fenjie(map<int, int> &a, int n){
    int tmp = n;
    for(int i : z){
        if(i * i > tmp) break;
        while(tmp % i == 0){
            a[i] ++;
            tmp /= i;
        }
    }
    if(tmp != 1){
        a[tmp] ++;
    }
}
bool zhishu(int x){
    for(int i = 2; i * i <= x; i++){
        if(x % i == 0 && x != i)
            return false;
    }
    return true;
}

int hebin(map<int, int> &a, int k){
    int asn = 1;
    for(auto x : a){
        if(x.second >= k){
            for(int i = 1; i <= x.second; i++){
                asn *= x.first;
            }
        }
    }
    return asn;
}
signed main()
{
    for(int i = 2; i <= (int)2e5; i++){
        if(zhishu(i))
            z.push_back(i);
    }   
    int q;
    cin >> q;
    while(q--){
        int n, k;
        scanf("%lld%lld", &n, &k);
        map<int, int> a;
        fenjie(a, n);
        int ans = hebin(a, k);
        printf("%lld\n", ans);
    }
    return 0;
}