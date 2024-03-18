#include <bits/stdc++.h>
using namespace std;
#define BIG 1
#define SMA 2
#define NUM 3
#define int long long

long long w;
const int MOD = 929;// 高精度存不下，需要进行取余！
inline int myMod(int x){
    return (x%MOD+MOD)%MOD;
}
class data{
    private:
    int getMode(char x){
        if(x >= 'a' && x <= 'z') return SMA;
        else if(x >= 'A' && x <= 'Z') return BIG;
        else if(x >= '0' && x <= '9') return NUM;
        //else raise("Mode Error");
    }
    void setMode(int m1){
        if(m1 == mod) return ;
        if(m1 == SMA){
            v1.push_back(27);
        }
        else if(m1 == NUM){
            v1.push_back(28);
        }
        else{// BIG
            if(mod == NUM){
                v1.push_back(28);
            }
            else{
                v1.push_back(28);
                v1.push_back(28);
            }   
        }
        mod = m1;
    }
    void perse(char x){
        char ans;
        if(mod == NUM) ans =  x - '0';
        else if(mod == BIG) ans =  x - 'A';
        else ans = x - 'a';
        v1.push_back(ans);
    }
    public:
    string in;
    vector<int> v1;
    vector<int> v2;
    int mod = BIG;
    data(string & x){
        in = x;
    }
    void do1(){
        for(char x : in){
            setMode(getMode(x));
            perse(x);
        }
    }
    void do2(){
        if(v1.size() & 1){
            v1.push_back(29);
        }
        for(int i = 0; i < v1.size(); i += 2){
            v2.push_back(30*v1[i] + v1[i + 1]);
        }
    }
};
class poly{
    vector<int> tmp;
    vector<int> val;
    public:
    poly(vector<int>& v){
        val = v;
    }
    void mul(const poly& zz){
        const vector<int> &p = zz.val;
        tmp.clear();
        tmp.resize(p.size() + val.size(), 0);
        for(int i = 0; i < val.size(); i++){
            for(int j = 0; j < p.size(); j++){
                tmp[i + j] += val[i] * p[j];
                tmp[i+j] = tmp[i+j]%MOD;//------------
            }
        }
        while(tmp.back() == 0){
            tmp.pop_back();
        }
        tmp.swap(val);
    }

    vector<int> getRemaind(const poly& zz){
        const vector<int> &p = zz.val;
        tmp = val;
        for(int i = (int)tmp.size() - 1; i >= (int)p.size() - 1; i--){
            int rat = tmp[i];
            for(int j = i, k = (int)p.size() - 1; k >= 0; k--, j--){
                tmp[j] -= p[k]*rat;
                tmp[j] = tmp[j]%MOD;//--------------
            }
        }
        tmp.resize((int)p.size() - 1);
        return tmp;
    }
};
class ck{// 生成长度，数据，校验值
    public:
    int n, k;
    int s;
    vector<int> d;
    vector<int> ckVal;
    ck(int s, const vector<int> &d){
        this->s = s;
        this->d.push_back(0);
        for(int x : d){
            this->d.push_back(x);
        }
        k = pow(2, s + 1);//!!!!!!!!!!!!!!!
        if(s == -1) k = 0;
        while ((this->d.size() + k) % w != 0)
        {
            this->d.push_back(900);
        }
        n = this->d.size();
        this->d[0] = n;
    }
    void doCkVal(){
        poly *p, *q;
        {
            vector<int> t;
            t.push_back(-3);
            t.push_back(1);
            p = new poly(t);
        }
        for(int i = 2; i <= k; i++){
            vector<int> t;
            t.push_back(-(int)pow(3, i));//!!!!!!!!!!!
            t.push_back(1);
            p->mul(t);
        }
        {
            vector<int> t;
            for(int x : d){
                t.push_back(x);
            }
            reverse(t.begin(), t.end());
            q = new poly(t);
        }
        {
            vector<int> t(k + 1);
            t[k] = 1;
            q->mul(t);
        }
        ckVal = q->getRemaind(*p);
    }
    
};

signed main()
{
    ios::sync_with_stdio(false);
    long long s;
    cin >> w >> s;
    string str;
    cin >> str;
    // if(s > 2){
    //     cout << "SB";
    //     return 0;
    // }
    data *d = new data(str);
    d->do1();
    d->do2();
    ck *c = new ck(s, d->v2);
    if(s != -1){
        c->doCkVal();
    }

    for(long long x : c->d){
        cout << x << "\n";
    }
    
    if(s != -1)
        for(int i = c->ckVal.size() - 1; i >= 0; i--){
            int x = c->ckVal[i];
            cout << (long long)(((-x)%MOD+MOD)%MOD) << "\n";
        }
    return 0;
}