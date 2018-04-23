#include <cstring>
#include <cstdio>
int g[100000][7][7];
int dx[10]={-1,-1,-1, 0, 0, 1, 1, 1};
int dy[10]={-1, 0, 1,-1, 1,-1, 0, 1};
long long ans;
int n=5,m=5;
bool checksame(int v1,int v2)
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(g[v1][i][j]!=g[v2][i][j])
				return false;
	return true;
}
bool checkempty(int v1)
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(g[v1][i][j])
				return false;
	return true;
}
int calc()
{
	int i,j,k,s;
	for(i=1;i<=10000;++i)
	{
		memset(g[i],0,sizeof(g[i]));
		for(j=1;j<=n;++j)
			for(k=1;k<=m;++k)
				for(s=0;s<8;++s)
					g[i][j][k]+=g[i-1][j+dx[s]][k+dy[s]];
		for(j=1;j<=n;++j)
			for(k=1;k<=m;++k)
				g[i][j][k]=(g[i][j][k]==3||(g[i][j][k]==2&&g[i-1][j][k]));
		if(checkempty(i))
		{
			//printf("%d\n",i);
			return false;
		}
		for(j=i-1;j;--j)
			if(checksame(i,j))
				return true;
	}
	printf("!!!");
}
void dfs(int x,int y)
{
	static long long w=0;
	if(x==n+1)
	{
		/*w+=1;
		if(w%1000000==0)
			printf("%lld\n",w);*/
		if(calc())
		{
			ans+=1;/*
			for(int i=1;i<=n;++i)
			{
				for(int j=1;j<=m;++j)
					if(g[0][i][j])
						printf("X");
					else
						printf(" ");
				puts("");
			}
			puts("---");*/
		}
		return;
	}
	g[0][x][y]=0;
	if(y==m)
		dfs(x+1,1);
	else
		dfs(x,y+1);
	g[0][x][y]=1;
	if(y==m)
		dfs(x+1,1);
	else
		dfs(x,y+1);
}
void solve(int x,int y)
{
	ans=0;
	memset(g,0,sizeof(g));
	dfs(1,1);
	printf("%lld ",ans);
}
int main()
{
	int i,j;
	for(i=1;i<=5;++i)
	{
		for(j=1;j<=5;++j)
		{
			n=i;
			m=j;
			solve(i,j);
		}
		puts("");
	}
	return 0;
}
