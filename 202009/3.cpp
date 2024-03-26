#include <bits/stdc++.h>
using namespace std;
int m, n;
#define NOT 0
#define AND 1
#define OR 2
#define XOR 3
#define NAND 4
#define NOR 5

vector<int> son[3000];
int inDeg[3000];
class Node
{
public:
    string type;
    vector<int> val;

    inline int getVal()
    {
        if (type == "NOT")
        {
            return !val[0];
        }
        else if (type == "AND")
        {
            int t = 1;
            for (int x : val)
                t = t & x;
            return t;
        }
        else if (type == "OR")
        {
            int t = 0;
            for (int x : val)
                t = t | x;
            return t;
        }
        else if (type == "XOR")
        {
            int t = 0;
            for (int x : val)
                t = t ^ x;
            return t;
        }
        else if (type == "NAND")
        {
            int t = 1;
            for (int x : val)
                t = t & x;
            return !t;
        }
        else
        { // NOR
            int t = 0;
            for (int x : val)
                t = t | x;
            return !t;
        }
    }
} node[3000];
vector<int> topu;
vector<vector<int>> in;
void init()
{
    for (int i = 1; i <= n + m + 10; i++)
    {
        inDeg[i] = 0;
        son[i].clear();
        node[i].val.clear();
    }
    // in.clear();
    topu.clear();
}
bool getTopu()
{
    vector<int> st;
    for (int i = 1; i <= n; i++)
    {
        if (inDeg[i] == 0){
            st.push_back(i);
            topu.push_back(i);
        }
    }
    while (st.size())
    {
        int x = st.back();
        st.pop_back();
        for (int y : son[x])
        {
            inDeg[y]--;
            if (inDeg[y] == 0)
            {
                topu.push_back(y);
                st.push_back(y);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (inDeg[i] > 0)
            return false;
    }
    return true;
}
int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        init();
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= n; i++)
        {
            static char buf[16];
            scanf("%s", buf);
            string str = string(buf);
            node[i].type = str;
            int num;
            scanf("%d", &num);
            for (int j = 1; j <= num; j++)
            {
                scanf("%s", buf);
                if (buf[0] == 'I')
                {
                    son[atoi(buf + 1) + n].push_back(i);
                    inDeg[i]++;
                }
                else
                { //'O'
                    son[atoi(buf + 1)].push_back(i);
                    inDeg[i]++;
                }
            }
        }
        for (int i = 1; i <= m; i++)
        {
            int x = i + n;
            for (int y : son[x])
            {
                inDeg[y]--;
            }
        }
        bool ok = getTopu();
        int s;
        scanf("%d", &s);
        in.resize(s);
        for (int i = 0; i < s; i++)
        {
            vector<int> tmp(m);
            for (int i = 0; i < m; i++)
            {
                scanf("%d", &tmp[i]);
            }
            in[i].swap(tmp);
        }
        for (int i = 0; i < s; i++)
        {
            static int que[520];
            int num;
            scanf("%d", &num);
            for (int i = 0; i < num; i++)
            {
                scanf("%d", que + i);
            }
            if (!ok)
            {
                if (i == 0)
                    puts("LOOP");
                continue;
            }
            for (int j = 1; j <= n + m + 5; j++)
            {
                node[j].val.clear();
            }
            for (int j = 0; j < m; j++)
            {
                int x = j + 1 + n;
                for (int y : son[x])
                {
                    node[y].val.push_back(in[i][j]);
                }
            }
            for (int x : topu)
            {
                int nowVal = node[x].getVal();
                for (int y : son[x])
                {
                    node[y].val.push_back(nowVal);
                }
            }
            for (int j = 0; j < num; j++)
            {
                if (j != 0)
                    putchar(' ');
                printf("%d", node[que[j]].getVal());
            }
            putchar('\n');
        }
    }
    return 0;
}