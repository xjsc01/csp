#include <bits/stdc++.h>
using namespace std;
int n, m, p, q;
const int N = 1e3 + 20;
class Pos{
    public :
    int x, y;
    Pos(int _x, int _y): x(_x), y(_y){}
    Pos(): x(0), y(0){}
    inline Pos operator +(const Pos &o2) const{
        return Pos(x + o2.x, y + o2.y);
    }
    inline bool inRange(){
        if(x > n || x < 1 || y > m || y < 1){
            return false;
        }
        return true;
    }
    inline Pos mul(int o) const{
        return Pos(x * o, y * o);
    }
    inline int getOxr(int i){
        return i*x + y;
    }
};

// map<pair<int, int>, int> mpId;
Pos d[8];
int yg[N][N];

int ans = 0;

void pre(){
    d[0] = Pos(1, 0);
    d[1] = Pos(1, 1);
    d[2] = Pos(0, 1);
    d[3] = Pos(-1, 1);
    d[4] = Pos(-1, 0);
    d[5] = Pos(-1, -1);
    d[6] = Pos(0, -1);
    d[7] = Pos(1, -1);
}

int main()
{
    pre();
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    // cin >> n >> m >> p >> q;
    scanf("%d%d%d%d", &n, &m, &p, &q);
    if(n > 3e4) return 0;
    for(int i = 1; i <= p; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        yg[x][y] = i;
        // ans ^= Pos(x, y).getOxr(i);
    }
    // for(auto ff : mpId){
    //     cout << ff.first.first << ", " << ff.first.second << "  " << ff.second <<"\n" ;
    // }
        //     for(int i = 1; i <= n; i++){
        //     for(int j = 1; j <= m; j++){
        //         printf("%d ", yg[i][j]);
        //     }
        //     puts("");
        // }
    for(int _ = 1; _ <= q; _++){
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);
        Pos yinyang = Pos(u, v);
        static vector<int> minDis;
        minDis.clear();
        for(int i = 0; i < 8; i++){
            int k = 1;
            for(auto dest = d[i].mul(k)+yinyang; dest.inRange();)
            {
                if(yg[dest.x][dest.y]){
                    if(dest.x != yinyang.x)
                        {minDis.push_back(abs(dest.x - yinyang.x));}
                    else{
                        minDis.push_back(abs(dest.y - yinyang.y));
                    }
                }
                k++;
                dest = d[i].mul(k)+yinyang;
            }
        }
        int minv = minDis[0];
        for(int rr : minDis) minv = min(minv, rr);
        bool ok = true;
        for(int i = 0; i < 8; i++){
            if(!(yinyang+d[i].mul(minv)).inRange()) ok = false;
        }
        if(ok){
            // xuanzhuan();
            static vector<pair<Pos, int> > opList;
            opList.clear();
            for(int i = 0; i < 8; i++){
                auto dest = d[i].mul(minv) + yinyang;
                if(yg[dest.x][dest.y]){
                    opList.push_back({yinyang+d[(i+t)%8].mul(minv), yg[dest.x][dest.y]});
                    // ans ^= dest.getOxr(mpId[{dest.x, dest.y}]);
                    // mpId[{dest.x, dest.y}] = 0;
                    yg[dest.x][dest.y] = 0;
                }
            }
            for(auto hh : opList){
                // yg[hh.first.x][hh.first.y] = 1;
                // mpId[{hh.first.x, hh.first.y}] = hh.second;
                // ans ^= Pos(hh.first.x, hh.first.y).getOxr(hh.second);
                yg[hh.first.x][hh.first.y] = hh.second;
            }
        }

    }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(yg[i][j])
                ans ^= yg[i][j] * i + j;
            }
        }
        printf("%d\n", ans);
    return 0;
}