# include <iostream>
# include <cstring>
# include <algorithm>
# include <string>

# define ll long long

using namespace std;
int w,s,n,k;
string word;
ll d [10005], g[10005], r[10005];
ll b[2] = {-9,1};
ll dd[10005];
int dcnt;

int shift[4][4] = {
    {0,0,0,0},
    {0,0,27,28},
    {0,-1,0,28},
    {0,28,27,0}
};

int level(char c) {
    if (c>='A'&&c<='Z') return 1;
    else if (c>='a'&&c<='z') return 2;
    else return 3;
}

int tonum(char c) {
    if (c>='A'&&c<='Z') return c-'A';
    else if (c>='a'&&c<='z') return c-'a';
    else return c-'0';
}

void cald() {
    int pre = 1;
    int len = word.length();
    for (int i=0;i<len;i++) {
        int le = level(word[i]);
        if (le!=pre) {
            int tmp = shift[pre][le];
            if (tmp==-1) d[dcnt++] = 28, d[dcnt++]=28;
            else d[dcnt++] = tmp;
            pre = le;
        }
        d[dcnt++] = tonum(word[i]);
    }
    if (dcnt&1) d[dcnt++] = 29;
    for (int i=0;i<dcnt;i+=2) d[i/2] = d[i]*30+d[i+1];
    dcnt /= 2;
}

void calg() {
    memset(d,0,sizeof d);
    d[0] = -3, d[1]=1;
    int hp = 1;
    while (hp<k) {
        memset(g, 0, sizeof g);
        for (int i=hp;i>=0;i--) for (int j=1;j>=0;j--) {
            g[i+j] += (d[i]*b[j])%929;
            g[i+j] %= 929;
        }
        hp++;
        b[0] *= 3;
        b[0] %= 929;
        memcpy(d,g,sizeof g);
    }
}

void calq() {
    // d[n+k-1] = q[n-1]*g[k]
    // d[n+k-2] = q[n-1]*g[k-1]+q[n-2]*g[k];
    // d[n+k-3] = q[n-1]*g[k-2]+q[n-2]*g[k-1]+q[n-3]*g[k];

    // q[n-1] = d[n+k-1]/g[k];
    // q[n-2] = (d[n+k-2]-q[n-1]*g[k-1])/g[k];
    // q[n-3] = (d[n+k-3]-q[n-1]*g[k-2]-q[n-2]*g[k-1])/g[k];

    // q[n-1] = d[n-1]/g[k];
    // q[n-2] = (d[n-2]-q[n-1]*g[k-1])/g[k];
    // q[n-3] = (d[n-3]-q[n-1]*g[k-2]-q[n-2]*g[k-1])/g[k];

    // d[n-1] = d[n-1]/g[k];
    // d[n-2] = (d[n-2]-d[n-1]*g[k-1])/g[k];
    // d[n-3] = (d[n-3]-d[n-1]*g[k-2]-d[n-2]*g[k-1])/g[k];
    for (int i=n-1;i>=0;i--) {
        for (int j=n-1;j>i;j--) dd[i] -= (dd[j]*g[i+k-j])%929;
        dd[i] %= 929;
    }
}

void cals() {
    k = s==-1?0:1;
    for (int i=s;i>=0;i--) k<<=1;
    int tmp = dcnt+1+k;
    while (tmp%w) dd[n++] = 900, tmp++;
    for (int i=dcnt-1;i>=0;i--) dd[n++] = d[i];
    tmp = n+1;
    dd[n++] = tmp;
}

int main() {
    cin>>w>>s;
    cin>>word;
    cald();
    cals();
    for (int i=n-1;i>=0;i--) printf("%lld\n", dd[i]);
    if (s!=-1) {
        calg();
        calq();
        for (int i=k-1;i>=0;i--) {
            for (int j=0;j<=i;j++) {
                r[i] += (g[j]*dd[i-j])%929;
                r[i] = (r[i]%929+929)%929;
            }
            printf("%lld\n", (r[i]%929+929)%929);
        }
    }
    return 0;
}