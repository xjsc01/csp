#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
const int N=2e6+10;
int l[N],r[N],mx[N],mn[N],lz[N],s[N];
void pushup(int id)
{
	mx[id]=max(mx[id<<1],mx[id<<1|1]);
	mn[id]=min(mn[id<<1],mn[id<<1|1]);
	s[id]=s[id<<1]+s[id<<1|1];
}
void pushdown(int id)
{
	if(lz[id]!=0x3f3f3f3f)
	{
		s[id<<1]=r[id<<1]-l[id<<1]+1;
		s[id<<1|1]=r[id<<1|1]-l[id<<1|1]+1;
		mx[id<<1]=lz[id];
		mx[id<<1|1]=lz[id];
		mn[id<<1]=lz[id];
		mn[id<<1|1]=lz[id];
		lz[id<<1]=lz[id];
		lz[id<<1|1]=lz[id];
		lz[id]=0x3f3f3f3f;
	}
}
void build(int id,int L,int R)
{
	l[id]=L;r[id]=R;mn[id]=0x3f3f3f3f;mx[id]=-0x3f3f3f3f;lz[id]=0x3f3f3f3f;
	if(L>=R) return ;
	int mid=L+R>>1;
	build(id<<1,L,mid);
	build(id<<1|1,mid+1,R);
	pushup(id);
}
void update_interval(int id,int L,int R,int val)
{
	if(l[id]>=L&&r[id]<=R)
	{
		s[id]=r[id]-l[id]+1;
		mx[id]=val;
		mn[id]=val;
		lz[id]=val;
		return ;
	}
	pushdown(id);
	int mid=l[id]+r[id]>>1;
	if(mid>=L) update_interval(id<<1,L,R,val);
	if(mid+1<=R) update_interval(id<<1|1,L,R,val);
	pushup(id);
}
int query_mx(int id,int L,int R)
{
	if(l[id]>=L&&r[id]<=R) return mx[id];
	pushdown(id);
	int mid=l[id]+r[id]>>1;
	int ans=-0x3f3f3f3f;
	if(mid>=L) ans=query_mx(id<<1,L,R);
	if(mid+1<=R) ans=max(ans,query_mx(id<<1|1,L,R));
	return ans;
}
int query_mn(int id,int L,int R)
{
	if(l[id]>=L&&r[id]<=R) return mn[id];
	pushdown(id);
	int mid=l[id]+r[id]>>1;
	int ans=0x3f3f3f3f;
	if(mid>=L) ans=query_mn(id<<1,L,R);
	if(mid+1<=R) ans=min(ans,query_mn(id<<1|1,L,R));
	return ans;
}
int query_sum(int id,int L,int R)
{
	if(l[id]>=L&&r[id]<=R) return s[id];
	pushdown(id);
	int mid=l[id]+r[id]>>1;
	long long ans=0;
	if(mid>=L) ans+=query_sum(id<<1,L,R);
	if(mid+1<=R) ans+=query_sum(id<<1|1,L,R);
	return ans;
}
int n,q;
vector<string> alls;
string add(string s)
{
	int flag=1;
	string t=s;
	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[i]==':') continue;
		else if(s[i]=='f'&&flag)
			t[i]='0';
		else
		{
			if(s[i]=='9') t[i]='a';
			else t[i]=s[i]+1;
			break;
		}
	}
	return t;
}
int find(string s)
{
	return lower_bound(alls.begin(),alls.end(),s)-alls.begin()+1;
}
struct node{
	int op;
	int id;
	string l,r;
}p[N];
int main()
{
	cin>>n>>q;
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&p[i].op);
		if(p[i].op==1)
		{
			cin>>p[i].id>>p[i].l>>p[i].r;
			alls.push_back(p[i].l);
			alls.push_back(p[i].r);
			alls.push_back(add(p[i].r));
		}
		else if(p[i].op==2)
		{
			cin>>p[i].l;
			alls.push_back(p[i].l);
		}
		else
		{
			cin>>p[i].l>>p[i].r;
			alls.push_back(p[i].l);
			alls.push_back(p[i].r);
			alls.push_back(add(p[i].r));
		}
	}
	sort(alls.begin(),alls.end());
	alls.erase(unique(alls.begin(),alls.end()),alls.end());
	build(1,1,alls.size());
	for(int i=1;i<=q;i++)
	{
		if(p[i].op==1)
		{
			int ll=find(p[i].l),rr=find(p[i].r);
			if(query_mn(1,ll,rr)==0x3f3f3f3f)//该块土地全部未被分配 
			{
				puts("YES");
				update_interval(1,ll,rr,p[i].id);
			}
			else if(query_mn(1,ll,rr)==p[i].id&&query_mx(1,ll,rr)==p[i].id)//该块土地只分配给了一个人 
			{
				if(query_sum(1,ll,rr)==(rr-ll+1))//该块土地本来就已经全部分配给了p[i].id 
					puts("NO");
				else
				{
					puts("YES");
					update_interval(1,ll,rr,p[i].id);
				} 
			}
			else//该块土地已经分配给了除了p[i].id以外的人，所以无法再分配给p[i].id 
				puts("NO");
		}
		else if(p[i].op==2)
		{
			int ll=find(p[i].l);
			int t=query_mx(1,ll,ll);
			if(t!=-0x3f3f3f3f)
				printf("%d\n",t);
			else
				printf("0\n");
		}
		else
		{
			int ll=find(p[i].l),rr=find(p[i].r);
			int id=query_mn(1,ll,rr);
			if(id==query_mx(1,ll,rr)&&query_sum(1,ll,rr)==(rr-ll+1))//该块土地只分配给了一个人 
				printf("%d\n",id);
			else
				printf("0\n");
		}
	}
	return 0;
}
/*
32 1
1 1 0001:8000 0001:0fff
2 0001:a000
3 0001:c000 0001:ffff
1 2 0000:0000 000f:ffff
2 0000:1000
1 1 0001:8000 0001:8fff
1 2 0000:0000 0000:ffff
2 0000:1000
1 1 0002:8000 0002:ffff
3 0001:8000 0002:ffff
1 1 0001:c000 0003:ffff
3 0001:8000 0002:ffff
*/