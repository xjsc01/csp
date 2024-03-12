#include <bits/stdc++.h>
using namespace std;
// int a[2600][600];
map<int, int>a[2600];
int id[2600];
int n, m;
char buf[2600];
int nxt[2600];
// #define AND 2
// #define OR 3
// #define IS 1
// #define ISN 4
typedef struct Node{
    char mod;
    int x, y;
    Node *l, *r;
    Node(int mod, int x, int y){
        this->mod = mod;
        this->x = x;
        this->y = y;
    }
}node;

int read(int pos, int &val){
    int ret = 0;
    int cnt = 0;
    while (isdigit(buf[pos]))
    {
        ret = ret * 10 + (buf[pos] - '0');
        cnt ++;
        pos ++;
    }
    val = ret;
    return cnt;
}

node* perse(int stat){
    if(isdigit(buf[stat])){
        int val1;
        int cnt1 = read(stat, val1);
        char op = buf[stat + cnt1];
        int val2;
        int cnt2 = read(stat + 1 + cnt1, val2);
        node *ret = new node(op, val1, val2);
        ret->l = NULL, ret->r = NULL;
        return ret;
    }
    else{
        node *ret = new node(buf[stat], 0, 0);
        node *t1, *t2;
        t1 = perse(stat+2);
        t2 = perse(nxt[stat+1] + 2);
        ret->l = t1;
        ret->r = t2;
        return ret;
    }
}

bool solve(node * x, int idx){
    if(x->mod == '&' || x->mod == '|'){
        if(x->mod == '&'){
            int tt = solve(x->l, idx);
            if(!tt) return false;
            return solve(x->r, idx);
        }
        else{
            int tt = solve(x->l, idx);
            if(tt) return true;
            return solve(x->r, idx);
        }
    }
    else{
        if(x->mod == ':'){
            return (a[idx][x->x] == x->y);
        }
        else{ // ~
            return (a[idx][x->x] != 0 && a[idx][x->x] != x->y);
        }
    }
}

void getNxt(){
    int allLen = strlen(buf + 1);
    for(int i = 1; i <= allLen; i++) nxt[i] = 0;
    vector<int> st;
    for(int i = 1; i <= allLen; i++){
        if(buf[i] == '('){
            st.push_back(i);
        }
        else if(buf[i] == ')'){
            int t = st.back();
            st.pop_back();
            nxt[t] = i;
        }
    }
}



int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", id + i);
        int k = 0;
        scanf("%d", &k);
        for(int j = 1; j <= k; j++){
            int x, y;
            scanf("%d%d", &x, &y);
            a[i][x] = y;
        }
    }
    scanf("%d", &m);

    for(int i = 1; i <= m; i++){
        vector<int> ans;
        scanf("%s", buf + 1);
        getNxt();
        node *root = perse(1);
        for(int idx = 1; idx <= n; idx++){
            if(solve(root, idx)) ans.push_back(id[idx]);
        }
        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); i++){
            if(i != 0) printf(" ");
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}

//&(|(1:2)(2:3))(|(1:2)(2:3))