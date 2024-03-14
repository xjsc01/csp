#include <bits/stdc++.h>
using namespace std;
map<int, int> person;
map<int, set<int> >placeToPerson;
map<int, pair<int, int> > placeTime;
map<int, vector<int>> timeToClear;
map<int, set<int> > timeOk;// 用户的7天时间已经到了
map<int, int> personCleanInTime;
int n;
int T;
void Clean(){
    for(int x : timeToClear[T]){
        if(placeTime[x].second < T) {
            for(int y : placeToPerson[x]){
                person[y]--;
                if(person[y] == 0){
                    person.erase(y);
                }
            }
            placeToPerson.erase(x);
            placeTime.erase(x);
        }
    }
    timeToClear.erase(T);
}

void addRisk(int p){
    if(placeTime[p].second >= T - 1){
        placeTime[p] = {placeTime[p].first, T + 6};
    }
    else{
        placeTime[p] = {T, T + 6};
    }
    timeToClear[T + 7].push_back(p);
}

void execPerson(int d, int u, int r){
    if(d < T - 6) return ;
    if(placeTime.find(r) == placeTime.end()){
        return ;
    }
    else{
        if(d >= placeTime[r].first && d <= placeTime[r].second){
            if(placeToPerson[r].find(u) == placeToPerson[r].end()){
                placeToPerson[r].insert(u);
                person[u] ++;
            }
            int o = personCleanInTime[u];
            personCleanInTime[u] = T + 7;
            timeOk[o].erase(u);
            timeOk[T + 7].insert(u);
        }
    }
}
void TimeOkClean(){

}
int main()
{
    scanf("%d", &n);
    for(T = 0 ; T < n; T++){
        int r, m;
        scanf("%d%d", &r, &m);
        for(int i = 1; i <= r; i++){
            int k;
            scanf("%d", &k);
            addRisk(k);
        }

        Clean();
        TimeOkClean();
        for(int i = 1; i <= m; i++){
            int d, u, r;
            scanf("%d%d%d", &d, &u, &r);
            execPerson(d, u, r);
        }
        printf("%d", T);
        for(auto k : person){
            printf(" %d", k.first);
        }
        puts("");
    }

    return 0;
}