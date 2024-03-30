/**
 * @brief  作者：Suzuki.
 * 链接：https://www.acwing.com/solution/content/235187/
 * 来源：AcWing
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */

#pragma GCC optimize(3,"Ofast","inline")
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
/*
    3     2     1
     \    |    /
      \   |   /
       \  |  /
        \ | /
_________\|/_________0
*/
using namespace std;
int n,m,p,q,k;
long long ans;
int pos[100005][2];
int cos[8]={1,1,0,-1,-1,-1,0,1};
int sin[8]={0,1,1,1,0,-1,-1,-1};
vector<int> changes;//需要变换的员工的id
unordered_map<int,map<int,int>> dirs[4];
void addPos(int x,int y,int id)
{
    dirs[0][y]  [x]=id;
    dirs[1][y-x][x]=id; 
    dirs[2][x]  [y]=id;
    dirs[3][y+x][x]=id; 
    return;
}
void deletePos(int x,int y)
{
    dirs[0][y]  .erase(x);
    dirs[1][y-x].erase(x);
    dirs[2][x]  .erase(y);
    dirs[3][y+x].erase(x);
    return;
}
pair<int,int> nextPos(int x,int y,int u,int v,int t)
{
    int dx=x-u,dy=y-v;
    int new_dx=dx*cos[t]-dy*sin[t],new_dy=dx*sin[t]+dy*cos[t];
    //非90度整数倍方向旋转非90度整数倍角单独修正 
    if(t%2&&dx&&dy) new_dx/=2,new_dy/=2;
    return make_pair(u+new_dx,v+new_dy);
}
//检查一个新找到的员工能不能更新k 
void checkDirectionUpdate(map<int,int>::iterator it,int pos_val)
{
    if(abs(it->first-pos_val)==k)
    {
        changes.push_back(it->second);
    }
    else if(abs(it->first-pos_val)<k)
    {
        changes.clear();
        k=abs(it->first-pos_val);
        changes.push_back(it->second);
    }
    return;
}
//检查四个方向上能不能找到员工
void checkDirection(int dir_id,int locator,int pos_val)
{
    if(dirs[dir_id].find(locator)!=dirs[dir_id].end())
    {
        auto it=dirs[dir_id][locator].upper_bound(pos_val);
        if(it!=dirs[dir_id][locator].end())
        {
            checkDirectionUpdate(it,pos_val);
        }
        it=dirs[dir_id][locator].lower_bound(pos_val);
        if(it!=dirs[dir_id][locator].begin())
        {
            it--;
            checkDirectionUpdate(it,pos_val);
        }
    }
    return;
}
void work(int u,int v,int t) 
{
    k=2147483647;
    changes.clear();
    checkDirection(0,v  ,u);
    checkDirection(1,v-u,u);
    checkDirection(2,u  ,v);
    checkDirection(3,v+u,u);
    //k不能大于到(u,v)到边界的位置 
    if(k<=min(min(u-1,n-u),min(v-1,m-v)))
    {
        for(auto id:changes)
        {
            int old_x=pos[id][0],old_y=pos[id][1];
            deletePos(old_x,old_y);
        }
        for(auto id:changes)
        {
            int old_x=pos[id][0],old_y=pos[id][1];
            int new_x,new_y;
            tie(new_x,new_y)=nextPos(old_x,old_y,u,v,t);
            pos[id][0]=new_x,pos[id][1]=new_y;
            addPos(new_x,new_y,id);
        }
    }
    return;
}
int main()
{
    cin>>n>>m>>p>>q;
    for(int id=0;id<p;id++)
    {
        int x,y;
        cin>>x>>y;
        pos[id][0]=x,pos[id][1]=y;
        addPos(x,y,id);
    }
    for(int i=0;i<q;i++)
    {
        int u,v,t;
        cin>>u>>v>>t;
        work(u,v,t);
    }
    for(int id=0;id<p;id++)
    {
        ans^=(long long)(id+1)*pos[id][0]+pos[id][1];
    }
    cout<<ans<<endl;
    return 0;
}
/*
in:
3 3 9 1
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
2 2 1

out:
20
*/

