#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, X, Y;
    cin >> n >> X >> Y;
    vector<pair<int, int> >a;
    for(int i =1 ; i <= n; i++){
        int u, v;
        cin >> u >> v;
        a.push_back({(u-X)*(u-X) + (v-Y)*(v-Y), i});
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < min((int)a.size(), 3); i++){
        cout << a[i].second << "\n";
    }
    return 0;
}