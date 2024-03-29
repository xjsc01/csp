#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Node
{
    int type;
    array<array<int, 2>, 2> arr;
} in[120000];
int n, m;
const int MOD = 998244353;
inline void mul(array<array<int, 2>, 2> &x, array<array<int, 2>, 2> &y)
{
    array<array<int, 2>, 2> tmp;
    tmp[0][0] = tmp[0][1] = tmp[1][0] = tmp[1][1] = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                tmp[i][j] = (tmp[i][j] + x[i][k] * y[k][j] % MOD + MOD) % MOD;
            }
        }

    x.swap(tmp);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> in[i].type;
        if (in[i].type <= 2)
        {
            for (int x = 0; x < 2; x++)
            {
                for (int y = 0; y < 2; y++)
                {
                    cin >> in[i].arr[x][y];
                }
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        int mod;
        cin >> mod;
        if (mod == 1)
        {
            int idx;
            cin >> idx;
            cin >> in[idx].type;
            if (in[idx].type <= 2)
            {
                for (int x = 0; x < 2; x++)
                {
                    for (int y = 0; y < 2; y++)
                    {
                        cin >> in[idx].arr[x][y];
                    }
                }
            }
        }
        else
        { // mod == 2
            array<array<int, 2>, 2> ans;
            ans[0][0] = 1;
            ans[0][1] = 0;
            ans[1][0] = 0;
            ans[1][1] = 1;
            int l, r;
            cin >> l >> r;
            deque<array<array<int, 2>, 2>> que;
            vector<int> last;
            que.clear(), last.clear();
            for (int j = l; j <= r; j++)
            {
                if (in[j].type == 1)
                {
                    que.push_front(in[j].arr);
                    last.push_back(1);
                }
                else if (in[j].type == 2)
                {
                    que.push_back(in[j].arr);
                    last.push_back(2);
                }
                else
                {
                    if (!last.empty())
                    {
                        if (last.back() == 1)
                        {
                            que.pop_front();
                        }
                        else
                        {
                            que.pop_back();
                        }
                        last.pop_back();
                    }
                }
            }
            for (auto &x : que)
            {
                mul(ans, x);
            }
            cout << ans[0][0] << " " << ans[0][1] << " " << ans[1][0] << " " << ans[1][1] << "\n";
        }
    }
    return 0;
}