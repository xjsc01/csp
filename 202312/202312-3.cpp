#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> son[2200];
int fa[2200];
int q[2200];
int qSon[2200];
bool inSub[2200];
bool ji[2200];
int root;
int cnt = 0;
int totVal = 0;
set<pair<int, int>> pq;

void dfs(int x){
    int tt = q[x];
    for(int y : son[x]){
        dfs(y);
        tt += qSon[y];
    }
    qSon[x] = tt;
    pq.insert(make_pair(tt, x));
}

void diss(int x, int gg){
    if(ji[x]) return;
    if(x == gg) return;
    ji[x] = true;
    cnt --;
    pq.erase({qSon[x], x});
    totVal -= q[x];
    for(int y : son[x]){
        diss(y, gg);
    }
}

pair<int, int> getIdx(){
    int admire = (totVal+1) / 2;
    pair<int, int> x1 = {LONG_LONG_MAX, LONG_LONG_MAX}, x2 = {LONG_LONG_MAX, LONG_LONG_MAX};
    auto t1 = pq.lower_bound({admire, 0});
    if(t1 != pq.end()) x1 = *t1;
    t1--;
    if(t1 != pq.end()) {
        t1 = pq.lower_bound({(*t1).first, 0});
        x2 = *t1;
    }

    if(make_pair(abs(x1.first-admire), x1.second) < make_pair(abs(x2.first-admire), x2.second)){
        return x1;
    }
    else{
        return x2;
    }
}

void solve()
{
    bool _fir = true;
    dfs(1);
    while(cnt != 1){
        auto tmp = getIdx();
        if(ji[tmp.second]) continue;
        if(_fir){
            _fir = false;
        }
        else{
            putchar(' ');
        }
        printf("%lld", tmp.second);
        if(inSub[tmp.second]){ // 接受
            diss(root, tmp.second);
            root = tmp.second;
        }
        else{ // 拒绝
            {
                int t = fa[tmp.second];
                while(1){
                    if(t == 1) break;
                    pq.erase({qSon[t], t});
                    qSon[t] -= qSon[tmp.second];
                    pq.insert({qSon[t], t});
                    t = fa[t];
                }
                diss(tmp.second, -1);
            }
        }
    }
}

signed main()
{
    int n, m;
    scanf("%lld%lld", &n, &m);
    int _totVal = 0;
    for(int i = 1; i <= n; i++){
        scanf("%lld", q + i);
        _totVal += q[i];
    }
    for(int i = 2; i <= n; i++){
        scanf("%lld", fa + i);
        son[fa[i]].push_back(i);
    }
    while(m --){
        pq.clear();
        for(int i = 1; i <= n; i++){
            inSub[i] = ji[i] = false;
            totVal = _totVal;
        }
        int tar;
        root = 1, cnt = n;
        scanf("%lld", &tar);
        {
            int t = tar;
            while(1){
                inSub[t] = true;
                if(t == 1) break;
                t = fa[t];
            }
        }
        solve();
        puts("");
    }
    return 0;
}