#include <bits/stdc++.h>
using namespace std;
int n, m, q;

map<string, array< set<string>, 3 > > role;
map<pair<char, string>, set<string> >userToRole;
char buf[256];

inline bool has(const set<string> &st,const  string &s){
    if(st.find(s) == st.end()) return false;
    else return true;
}

inline void setUnion(set<string> &s, set<string> & t){
    for(const string & u : t){
        s.insert(u);
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= n; i++){
        scanf("%s", buf);
        string name = string(buf);
        int nv, no, nn;
        set<string> s[3];
        array< set<string>, 3 >tt;
        for(int k = 0; k < 3; k++){
            scanf("%d", &nv);
            for(int i = 0; i < nv; i++){
                scanf("%s", buf);
                string tmps = string(buf);
                s[k].insert(tmps);
            }
            tt[k] = s[k];
        }
        role[name] = tt;
    }
    for(int i = 1; i <= m; i++){
        scanf("%s", buf);
        string name = string(buf);
        int num;
        scanf("%d", &num);
        for(int j = 0; j < num; j++){
            char ch;
            string uname;
            scanf("%s", buf);
            ch = buf[0];
            scanf("%s", buf);
            uname = string(buf);
            userToRole[{ch, uname}].insert(name);
        }
    }
    for(int _ = 1; _ <= q; _++){
        scanf("%s", buf);
        string uname = string(buf);
        int num;
        scanf("%d", &num);
        set<string> gname;
        for(int i = 0; i < num; i++){
            scanf("%s", buf);
            string na = string(buf);
            gname.insert(na);
        }
        string s[3];
        for(int k = 0; k < 3; k++){
            scanf("%s", buf);
            string tmps = string(buf);
            s[k] = tmps;
        }
        set<string> legalRole;
        for(auto tmp : role){
            if(!has(tmp.second[0], s[0]) && !has(tmp.second[0], string("*"))) continue;
            if(!has(tmp.second[1], s[1]) && !has(tmp.second[1], string("*"))) continue;
            if(!has(tmp.second[2], s[2]) && tmp.second[2].size()) continue;
            legalRole.insert(tmp.first);
        }
        set<string> hasRole;
        setUnion(hasRole, userToRole[{'u', uname}]);
        for(const string & x : gname){
            setUnion(hasRole, userToRole[{'g', x}]);
        }
        bool ok = false;
        for(const string &x : hasRole){
            if(has(legalRole, x)) {
                ok = true;
                break;
            }
        }
        if(ok) puts("1");
        else puts("0");
    }
    return 0;
}