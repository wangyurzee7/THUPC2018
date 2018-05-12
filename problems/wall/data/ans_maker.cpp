#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<vector>
#include<queue>
#define MAXN 30005
using namespace std;
const double eps=1e-8;
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y)
	{x=_x;y=_y;}
};
typedef Point Vector;
Vector operator-(Point A,Point B)
{return Vector(A.x-B.x,A.y-B.y);}
double operator*(Vector U,Vector V)
{return U.x*V.y-U.y*V.x;}
struct Polygon
{
	int k,r;
	Point P[105];
	double S;
	void init()
	{
		S=0.0;
		for (int i=2;i<k;i++)
			S+=(P[i]-P[1])*(P[i+1]-P[1]);
		S/=2.0;
	}
}poly[MAXN];
int dcmp(double x)
{
	if (fabs(x)<eps)return 0;
	return (x>0)?1:-1;
}
bool inner(Point P,int id)
{
	if (id==0)return 1;
	for (int i=1;i<poly[id].k;i++)
		if (dcmp((P-poly[id].P[i])*(poly[id].P[i+1]-poly[id].P[i]))>0)return 0;
	return 1;
}
int n,m,cnt,id,tmp,op,u;
vector<int>inc[MAXN];
int indgr[MAXN],fa[MAXN];
vector<int>g[MAXN];
double S[MAXN];
Point P;
bool vis[MAXN];
queue<int>q;
double ans;
void bfs(int u,int R)
{
	R=3-R;
	vis[u]=1;q.push(u);
	while (!q.empty())
	{
		u=q.front();q.pop();
		ans+=S[u];
		for (int i=0;i<g[u].size();i++)
			if ((!vis[g[u][i]])&&poly[g[u][i]].r==R)
			{
				vis[g[u][i]]=1;
				q.push(g[u][i]);
			}
		if ((!vis[fa[u]])&&poly[u].r==R)
		{
			vis[fa[u]]=1;
			q.push(fa[u]);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&poly[i].k,&poly[i].r);
		for (int j=1;j<=poly[i].k;j++)
			scanf("%lf%lf",&poly[i].P[j].x,&poly[i].P[j].y);
		poly[i].init();
	}
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			if (inner(poly[j].P[1],i))
			{
				inc[i].push_back(j);
				indgr[j]++;
			}
			if (inner(poly[i].P[1],j))
			{
				inc[j].push_back(i);
				indgr[i]++;
			}
		}
	memset(fa,-1,sizeof(fa));
	while (cnt<n)
	{
		for (int i=1;i<=n;i++)
			if (indgr[i]==0&&fa[i]==-1)
			{cnt++;id=i;break;}
		for (int i=0;i<inc[id].size();i++)
			indgr[inc[id][i]]--;
		tmp=0;
		while (true)
		{
			bool flag=0;
			for (int i=0;i<g[tmp].size();i++)
				if (inner(poly[id].P[1],g[tmp][i]))
				{
					tmp=g[tmp][i];
					flag=1;
					break;
				}
			if (!flag)break;
		}
		g[tmp].push_back(id);
		fa[id]=tmp;
	}
	for (int i=1;i<=n;i++)
	{
		S[i]=poly[i].S;
		for (int j=0;j<g[i].size();j++)
			S[i]-=poly[g[i][j]].S;
	}
	while (m--)
	{
		scanf("%d%d",&op,&u);
		if (op==1)poly[u].r=3-poly[u].r;
		else
		{
			scanf("%lf%lf",&P.x,&P.y);
			tmp=0;
			while (true)
			{
				bool flag=0;
				for (int i=0;i<g[tmp].size();i++)
					if (inner(P,g[tmp][i]))
					{
						tmp=g[tmp][i];
						flag=1;
						break;
					}
				if (!flag)break;
			}
			memset(vis,0,sizeof(vis));
			ans=0.0;bfs(tmp,u);
			printf("%.4lf\n",ans);
		}
	}
	return 0;
}

