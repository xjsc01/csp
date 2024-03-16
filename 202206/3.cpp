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


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++){
        static string name;
        cin >> name;
        static int nv;
        static array< set<string>, 3 >tt;
        tt[0].clear(), tt[1].clear(), tt[2].clear();
        for(int k = 0; k < 3; k++){
            cin >> nv;
            for(int i = 0; i < nv; i++){
                string tmps;
                cin >> tmps;
                tt[k].insert(tmps);
            }
        }
        role[name] = tt;
    }
    for(int i = 1; i <= m; i++){
        static string name;
        cin >> name;
        static int num;
        cin >> num;
        for(int j = 0; j < num; j++){
            static char ch;
            static string uname;
            cin >> ch >> uname;
            userToRole[{ch, uname}].insert(name);
        }
    }
    for(int _ = 1; _ <= q; _++){
        static string uname ;
        cin >> uname;
        static int num;
        cin >> num;
        static set<string> gname;
        gname.clear();
        for(int i = 0; i < num; i++){
            static string na;
            cin >> na;
            gname.insert(na);
        }
        static string s[3];
        for(int k = 0; k < 3; k++){
            cin >> s[k];
        }
        static set<string> legalRole;
        legalRole.clear();
        for(const auto &tmp : role){
            if(!has(tmp.second[0], s[0]) && !has(tmp.second[0], string("*"))) continue;
            if(!has(tmp.second[1], s[1]) && !has(tmp.second[1], string("*"))) continue;
            if(!has(tmp.second[2], s[2]) && tmp.second[2].size()) continue;
            legalRole.insert(tmp.first);
        }

        bool ok = false;
        for(const string& t1 : userToRole[{'u', uname}]){
            if(has(legalRole, t1)){
                ok = true;
                goto L1;
            }
        }
        for(const string & t1 : gname){
            for(const string & t2 : userToRole[{'g', t1}]){
                if(has(legalRole, t2)){
                    ok = true;
                    goto L1;
                }
            }
        }

        L1:
        if(ok) cout << "1\n";
        else cout << "0\n";
    }
    return 0;
}