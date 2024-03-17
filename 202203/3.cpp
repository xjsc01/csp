#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m;
class{
    public:
    vector<int> jdId;
}kyq[N];
class{
    public:
    int kyqId;
    int jdId;
    int exeNum;
}jd[N];
inline bool mycmp(int x, int y){
    if(jd[x].exeNum < jd[y].exeNum) return true;
    else if(jd[x].exeNum > jd[y].exeNum) return false;
    else{
        return x < y;
    }
}

class App{
    public:
    set<int> kyqId;
    set<int> jdId;
};
map<int, App> app;

class task{
    static set<int>legalId;
    static set<int> tmpId;
    static vector<int> legalAns;
    public:
    int a, na, pa, paa, paar;
    inline void Union(){
        set<int> tt;
        for(int x : legalId){
            if(tmpId.find(x) != tmpId.end()){
                tt.insert(x);
            }
        }
        tt.swap(legalId);
    }
    int getNodeId(){
        int ret = 0;
        legalId.clear();
        tmpId.clear();
        if(na){
            for(int x : kyq[na].jdId){
                legalId.insert(x);
            }
        }
        else{
            for(int i = 1; i <= n; i++){
                legalId.insert(i);
            }
        }
        if(pa){
            tmpId.clear();
            for(int x : app[pa].kyqId){
                for(int y : kyq[x].jdId){
                    tmpId.insert(y);
                }
            }   
            Union();
        }
        if(paar == 0){
            legalAns.clear();
            for(int x : legalId){
                legalAns.push_back(x);
            }
            sort(legalAns.begin(), legalAns.end(), mycmp);
            if(legalAns.size()) ret = legalAns.front();
        }
        if(paa){
            for(int x : app[paa].jdId){
                legalId.erase(x);
            }
        }
        {
            legalAns.clear();
            for(int x : legalId){
                legalAns.push_back(x);
            }
            sort(legalAns.begin(), legalAns.end(), mycmp);
            if(legalAns.size()) ret = legalAns.front();
        }
        return ret;
    }
}ta;
set<int> task::legalId;
set<int> task::tmpId;
vector<int> task::legalAns;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        int t;
        scanf("%d", &t);
        jd[i].exeNum = 0, jd[i].jdId = i, jd[i].kyqId = t;
        kyq[t].jdId.push_back(i);
    }
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int f;
        scanf("%d", &f);
        scanf("%d%d%d%d%d", &ta.a, &ta.na, &ta.pa, &ta.paa, &ta.paar);
        while(f--){
            int ret = ta.getNodeId();
            // 更新相关对象
            jd[ret].exeNum ++;
            app[ta.a].jdId.insert(ret);
            app[ta.a].kyqId.insert(jd[ret].kyqId);
            printf("%d", ret);
            if(f) putchar(' ');
        }
        putchar('\n');
    }
    return 0;    
}