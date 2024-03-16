#include <bits/stdc++.h>
using namespace std;
set<pair<int, int>> st;
int n, L, S;
const int N = 60;
int a[N][N];
vector<pair<int, int>> in;

inline bool same(pair<int, int> b, pair<int, int>x){
    if(st.find({b.first, b.second}) != st.end()){
        return a[x.first][x.second] == 1;
    }
    else{
        return !a[x.first][x.second];
    }
}

bool ck(int u, int v){
    for(int x = 0; x <= S; x++){
        for(int y = 0; y <= S; y++){
            if(!same({u+x, v+y}, {x, y}))
                return false;
        }
    }
    return true;
}

int main(){
    scanf("%d%d%d", &n, &L, &S);
    for(int i = 1; i <= n; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        st.insert({x, y});
        in.push_back({x, y});
    }
    for(int i = S ; i >= 0; i--){
        for(int j = 0; j <= S; j++){
            scanf("%d", &a[i][j]);
        }
    }
    int ans = 0;
    for(auto tmp : in){
        if(tmp.first < 0 || tmp.first > L-S
        || tmp.second < 0 || tmp.second > L-S)
        continue;
        if(ck(tmp.first, tmp.second)){
            ans ++;
        }
    }
    printf("%d\n", ans);
    return 0;
}