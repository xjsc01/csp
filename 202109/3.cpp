#include <bits/stdc++.h>
using namespace std;
const int N = 3e3;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    static unsigned long nxt = 1;
    nxt = nxt * 1103515245 + 12345;
    return((unsigned)(nxt/65536) % 32768);
}
class Sjy;
class Mcy;
class Tuchu;
double deltaT;
int nowTnum;
Sjy* sjy[N];
Mcy* mcy[N];
vector<Tuchu>tc[N];
class Tuchu{
    public:
    int s, t;
    double w, D;
    Tuchu(int s, int t, double w, double D){
        this->s = s;
        this->t = t;
        this->w = w;
        this->D = D;
    }
};



class Sjy{
    int id;
    vector<double> I;
    public:
    double u, v, a, b, c, d;
    int mcNum = 0;
    Sjy(int id, double u, double v, double a, double b, double c, double d, int Tnum){
        this->id = id;
        this->u = u;
        this->v = v;
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        I.resize(Tnum + 2);
    }
    void addI(double d, int Tnum){
        if(Tnum > I.size() - 1){
            return ;
        }
        I[Tnum] += d;
    }
    void trans(){
        double nu, nv;
        nv = v + deltaT*(0.04 * v*v + 5*v + 140 - u) + I[nowTnum];
        nu = u + deltaT*a*(b*v - u);
        v = nv, u = nu;
        if(nv >= 30){
            mcNum ++;
            v = c;
            u = u + d;
            for(int i = 0; i < tc[id].size(); i++){
                // tc[id][i].run();
                auto &tmp = tc[id][i];
                sjy[tmp.t]->addI(tmp.w, nowTnum + tmp.D);
            }
        }
        // printf("T:%d (%lf)\n", nowTnum, v);
    }
};
class Mcy{
    int id;
    public:
    int r;
    void run(){
        int ret = myrand();
        if(ret < r){
            for(int i = 0; i < tc[id].size(); i++){
                auto &tmp = tc[id][i];
                sjy[tmp.t]->addI(tmp.w, nowTnum + tmp.D);
            }
        }
    }
    Mcy(int id, int r){
        this->id = id;
        this->r = r;
    }
};


int main()
{
    int N, S, P, T;
    scanf("%d%d%d%d", &N, &S, &P, &T);
    scanf("%lf", &deltaT);
    int totTNum = T;
    for(int i = 0; i < N;){
        int nn;
        scanf("%d", &nn);
        double u, v, a, b, c, d;
        scanf("%lf%lf%lf%lf%lf%lf", &v, &u, &a, &b, &c, &d);
        for(int j = 1; j <= nn; j++){
            sjy[i] = new Sjy(i, u, v, a, b, c, d, totTNum);
            i++;
        }
    }
    for(int i = N; i < N+P; i++){
        double r;
        scanf("%lf", &r);
        mcy[i] = new Mcy(i, r);
    }
    for(int i = 1; i <= S; i++){
        int u, v;
        double w, d;
        scanf("%d%d%lf%lf", &u, &v, &w, &d);
        tc[u].push_back(Tuchu(u, v, w, d));
    }
    for(nowTnum = 1; nowTnum <= totTNum; nowTnum ++){
        for(int i = N; i <= N+P-1; i++){
            mcy[i]->run();
        }
        for(int i = 0; i <= N-1; i++){
            sjy[i]->trans();
        }
    }
    double vmax, vmin;
    int cmax, cmin;
    vmin = vmax = sjy[0]->v;
    cmax = cmin = sjy[0]->mcNum;
    for(int i = 0; i <= N - 1; i++){
        vmin = min(vmin, sjy[i]->v);
        vmax = max(vmax, sjy[i]->v);
        cmax = max(cmax, sjy[i]->mcNum);
        cmin = min(cmin, sjy[i]->mcNum);
    }
    printf("%.3lf %.3lf\n%d %d\n", vmin, vmax, cmin, cmax);
    return 0;
}