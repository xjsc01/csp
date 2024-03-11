#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
const int mod = 1e9 + 7;
struct node{
    int type;
    char op;
    int id;
    node(int type, char op, int id){
        this->type = type;
        this->op = op;
        this->id = id;
    }
    node *l, *r;
};
int desert;
int val[5000];
vector<node *>a;
int zhi(node *x){
    if(x->type == 0) return val[x->id];
    if(x->type == 2) return x->id;
    if(x->op == '+'){
        return ((zhi(x->l) + zhi(x->r) )%mod+mod)%mod;
    }
    else if(x->op == '-'){
        return ((zhi(x->l) - zhi(x->r) )%mod+mod)%mod;
    }
    else if(x->op == '*'){
        return ((zhi(x->l) * zhi(x->r) )%mod+mod)%mod;
    }
    assert(0);
}
int dao(node *x){
    if(x->type == 0) {
        if(x->id == desert) return 1;
        else return 0;
    }
    if(x->type == 2){
        return 0;
    }
    if(x->op == '+'){
        return ((dao(x->l) + dao(x->r) )%mod+mod)%mod;
    }
    else if(x->op == '-'){
        return ((dao(x->l) - dao(x->r) )%mod+mod)%mod;
    }
    else if(x->op == '*'){
        return ((dao(x->l) * zhi(x->r) + zhi(x->l) * dao(x->r))%mod+mod)%mod;
    }
    assert(0);
}

signed main()
{
    cin >> n >> m;
    getchar();
    string s;
    getline(cin, s);
    stringstream strin(s);
   
    while(strin >> s){
        if(s[0] == 'x'){
            a.push_back(new node(0, '?', atoi(s.c_str() + 1)));
            a.back()->l = NULL;
            a.back()->r = NULL;
        }
        else if((s[0]=='+' || s[0]=='-' || s[0]=='*') && s.size() == 1){
            node *tmp;
            tmp = new node(1, s[0], 0);
            tmp->r = a.back(), a.pop_back();
            tmp->l = a.back(), a.pop_back();
            a.push_back(tmp);
        }
        else{
            a.push_back(new node(2, '?', atoi(s.c_str())));
            a.back()->l = NULL;
            a.back()->r = NULL;
        }
    }

    node *root = a.back();

    for(int _ = 1; _ <= m; _++){
        scanf("%lld", &desert);
        for(int i = 1; i <= n; i++){
            scanf("%lld", val + i);
        }
        printf("%lld\n", dao(root));
    }


    return 0;
}