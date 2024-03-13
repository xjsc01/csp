#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int> >mp;
const double PI = acos(-1);
int Q[128][128], M[128][128];
double N[128][128];
int out[128][128];
void pre()
{
    for(int sum = 0; sum <= 49; sum++){
        if(sum & 1 == 1){
            for(int x = 0; x <= sum; x++){
                int y = sum - x;
                if(x < 0 || x > 7 || y < 0 || y > 7) continue;
                mp.push_back({x, sum - x});
            }
        }
        else{
            for(int x = sum; x >= 0; x--){
                int y = sum - x;
                if(x < 0 || x > 7 || y < 0 || y > 7) continue;
                mp.push_back({x, sum - x});
            }
        }
    }
}
void Print(int O[128][128]){
    for(int i = 0; i < 8; i++)  {
        for(int j = 0; j < 8; j++){
            if(j != 0)
                printf(" ");
            printf("%d", O[i][j]);
        }
        printf("\n");
    }
}
inline double alpha(int x){
    if(x == 0) return sqrt(0.5);
    else return 1;
}
int main()
{
    int n, T;
    pre();
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){
            scanf("%d", &Q[i][j]);
        }
    scanf("%d%d", &n, &T);
    for(int i = 0; i < n; i++){
        int x, y;
        x = mp[i].first;
        y = mp[i].second;
        scanf("%d", &M[x][y]);
    }
    if(T == 0){
        Print(M);
        return 0;
    }
    for(int i = 0; i < 8; i++)  {
        for(int j = 0; j < 8; j++){
            M[i][j] *= Q[i][j];
        }
    }
    if(T == 1){
        Print(M);
        return 0;
    }
    for(int i = 0; i < 8; i++)  {
        for(int j = 0; j < 8; j++){
            double sum = 0;
            for(int x = 0; x < 8; x++){
                for(int y = 0; y < 8; y++){
                    sum += alpha(x)*alpha(y)*(double)M[x][y]
                    *cos(PI/8.0*(i + 0.5)*x)
                    *cos(PI/8.0*(j + 0.5)*y);
                }
            }
            N[i][j] = (1.0 / 4.0) * sum;
        }
    }
    for(int i = 0; i < 8; i++)  {
        for(int j = 0; j < 8; j++){
            out[i][j] = round(N[i][j] + 128);
            out[i][j] = max(0, out[i][j]);
            out[i][j] = min(255, out[i][j]);
            // 别忘了这个是饱和溢出的。
        }
    }
    Print(out);
    return 0;
}
// for(auto x : mp){
//     printf("(%d, %d)  ", x.first, x.second);
// }