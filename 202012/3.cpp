#include <bits/stdc++.h>
using namespace std;
#define int __int128
#define N 3000000
#define DIR 1
#define TXT 2
struct {
    char type;
    string purePath;
    int size;
    int LD, RD;
    vector<string> path;
}in;
int fanhao = 0;
struct Node{
    map<string, int> son;
    int type;
    int size;
    int LD, RD;
    int sonSize, totSize;
}a[N];

void pre(){
    in.path.clear();
    static char tmp[10000];
    int idx = 0;
    for(int i = 1; i < in.purePath.size(); i++){
        if(in.purePath[i] != '/'){
            tmp[idx++] = in.purePath[i];
        }
        else{
            tmp[idx] = '\0';
            in.path.push_back(string(tmp));
            idx = 0;
        }
    }
    tmp[idx] = '\0';
    if(idx != 0)
        in.path.push_back(string(tmp));
    idx = 0;
}

inline bool isExist(map<string, int> &s, string &x){
    if(s.count(x)) return true;
    else return false;
}

pair<bool, int> CFunc(int pos, int zhizhen){
    auto &x = a[zhizhen];
    if(pos == (int)in.path.size()){// 到达需要操作的节点
        if(x.type == DIR) return {false, 0};
        int delta = in.size - x.size;
        x.size = in.size;
        return {true, delta};
    }
    else{
        if(pos == (int)in.path.size() - 1){
            if(     x.sonSize + in.size > x.LD && x.LD != 0
                ||  x.totSize + in.size > x.RD && x.RD != 0){
                return {false, 0};
            }
        }
        else{
            if(x.totSize + in.size > x.RD && x.RD != 0){
                return {false, 0};
            }
        }
        if(!isExist(x.son, in.path[pos])){
            x.son[in.path[pos]] = ++fanhao;
            if(pos == (int)in.path.size() - 1) a[fanhao].type = TXT;
            else a[fanhao].type = DIR;
        }
        if(a[x.son[in.path[pos]]].type == TXT && pos < (int)in.path.size() - 1) return {false, 0};
        if(a[x.son[in.path[pos]]].type == DIR && pos == (int)in.path.size() - 1) return {false, 0};
        auto ret = CFunc(pos+1, x.son[in.path[pos]]);
        if(ret.first == false) return {false, 0};
        else{
            if(pos == (int)in.path.size() - 1)
                x.sonSize += ret.second;
            x.totSize += ret.second;
            return {true, ret.second};
        }
    }
}

pair<bool, int> RFunc(int pos, int zhizhen){
    auto &x = a[zhizhen];
    if(pos == (int)in.path.size() - 1){// 文件名
        if(!isExist(x.son, in.path[pos])){
            return {false, 0};
        }
        int delta = 0;
        if(a[x.son[in.path[pos]]].type == DIR){
            x.totSize -= a[x.son[in.path[pos]]].totSize;
            delta = -a[x.son[in.path[pos]]].totSize;
            x.son.erase(in.path[pos]);
        }
        else{
            delta = -a[x.son[in.path[pos]]].size;
            x.sonSize += delta; 
            x.totSize += delta;
            x.son.erase(in.path[pos]);
        }
        return {true, delta};
    }
    else{
        if(!isExist(x.son, in.path[pos])){
            return {false, 0};
        }
        if(a[x.son[in.path[pos]]].type == TXT) return {false, 0};
        auto ret = RFunc(pos+1, x.son[in.path[pos]]);
        if(ret.first == false) return {false, 0};
        else{
            x.totSize += ret.second;
            return {true, ret.second};
        }
    }
}

bool QFunc(int pos, int zhizhen){
    auto &x = a[zhizhen];
    if(pos == (int)in.path.size()){ // 需要操作的文件
        if(x.type == TXT) return false;
        if(in.LD != 0 && in.LD < x.sonSize
        || in.RD != 0 && in.RD < x.totSize) return false;
        else{
            x.LD = in.LD;
            x.RD = in.RD;
            return true;
        }
    }
    else{
        if(!isExist(x.son, in.path[pos])){
            return false;
        }
        if(a[x.son[in.path[pos]]].type == TXT) return false;
        return QFunc(pos+1, x.son[in.path[pos]]);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    long long T;
    cin >> T;
    while(T--){// root节点为0号节点！
        cin >> in.type;
        if(in.type == 'C'){
            long long sz;
            cin >> in.purePath >> sz;
            in.size = sz;
            pre();
            if(CFunc(0, 0).first) cout << "Y\n";
            else cout << "N\n";
        }   
        else if(in.type == 'R'){
            cin >> in.purePath;
            pre();
            RFunc(0, 0);
            cout << "Y\n";
        }    
        else if(in.type == 'Q'){
            long long LD, RD;
            cin >> in.purePath >> LD >> RD;
            in.LD = LD, in.RD = RD;
            pre();
            if(QFunc(0, 0)) cout << "Y\n";
            else cout << "N\n";
        }
    }
    return 0;
}