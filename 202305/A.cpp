#include <bits/stdc++.h>
using namespace std;
int n;
char a[128][128];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 8; j++){
            static char buf[16];
            scanf("%s", buf);
            strcat(a[i], buf);
        }
    }
    for(int i = 1; i <= n; i++){
        int ans = 1;
        for(int j = 1; j < i; j++){
            if(strcmp(a[i], a[j]) == 0) ans ++;
        }
        printf("%d\n", ans);
    }
    return 0;
}