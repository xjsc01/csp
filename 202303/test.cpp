#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int n, m, k;
int t[N], c[N];

bool ck(int mid){
    int all = 0;
    for(int i = 1; i <= n; i++){
        all += max(0, (t[i] - mid) * c[i]);
    }
    if(all <= m) return true;
    else return false;
}
int main()
{
    printf("%d", isdigit('4'));
    return 0;
}