#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 6e5;
int a[N];
int ca[N];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", a + i);
    }
    {
        int i = 2, j = 1;
        for(; i <= n; i++){
            if(a[i] != a[j]){
                a[++j] = a[i];
            }
        }
        n = j;
    }
    int ori = 0;
    for(int i = 1, last = 0; i <= n; i++){
        if(last == 0 && a[i]){
            ori++;
            last = 1;
        } 
        else if(last == 1 && a[i] == 0){
            last = 0;
        }
    }
    for(int i = 1; i <= n; i++){
        if(a[i] == 0) continue;
        if(i == 1 || i == n
        || a[i-1] == 0 || a[i+1] == 0
        || a[i] > a[i-1] && a[i] > a[i+1]){
            ca[a[i]+1]--;
        }
        else if(a[i] < a[i+1] && a[i] < a[i-1]){
            ca[a[i]+1]++;
        }
    }   
    for(int i = 1; i <= (int)2e4; i++) ca[i] = ca[i-1] + ca[i];
    int maxv = 0;
    for(int i = 1; i <= (int)2e4; i++) maxv = max(ca[i], maxv);
    printf("%d\n", ori + maxv);
    return 0;
}