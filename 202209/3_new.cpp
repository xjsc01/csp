#include <bits/stdc++.h>
using namespace std;
map<int, pair<int, int>> placeTime;
map<int, map<int, int>> PerPlaTim;  // Person->Place->Time(The person time is beyond 7)
vector<pair<int, int>> check[5000]; // In this time, we shuold check if person-time is 失效

int n;
int T;
void addRisk(int p)
{
    if (placeTime[p].second >= T - 1)
    {
        placeTime[p] = {placeTime[p].first, T + 6};
    }
    else
    {
        placeTime[p] = {T, T + 6};
    }
}

void execPerson(int d, int u, int r)
{
    if (d < T - 6)
        return; // 已经超过7天，不追究
    if (d < placeTime[r].first)
        return;              // 此人到访之后，中间间隔过，所以不追究
    PerPlaTim[u][r] = d + 6; // 人自己的结束日期
        check[d + 7].push_back({u, r});
        check[placeTime[r].second + 1].push_back({u, r});
}
void ck()
{
    for (auto tmp : check[T])
    {
        if (PerPlaTim[tmp.first][tmp.second] < T || placeTime[tmp.second].second < T)
        {
            PerPlaTim[tmp.first].erase(tmp.second);
            if (PerPlaTim[tmp.first].empty())
            {
                PerPlaTim.erase(tmp.first);
            }
        }
    }
}
int main()
{
    scanf("%d", &n);
    for (T = 0; T < n; T++)
    {

        int r, m;
        scanf("%d%d", &r, &m);
        for (int i = 1; i <= r; i++)
        {
            int k;
            scanf("%d", &k);
            addRisk(k);
        }
        ck();
        for (int i = 1; i <= m; i++)
        {
            int d, u, r;
            scanf("%d%d%d", &d, &u, &r);
            execPerson(d, u, r);
        }

        printf("%d", T);
        for (auto k : PerPlaTim)
        {
            printf(" %d", k.first);
        }
        puts("");
    }
    // for(int i = 0; i < n; i++){
    //     printf("%d\n", i);
    // }
    return 0;
}