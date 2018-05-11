#include <cstring>
#include <cstdio>
#define MOD 2148473648LL
long long cnt[10];
long long g[10];
void dfs(int idx,long long c,int free)
{
	if(idx==5)
	{
		cnt[free]=(cnt[free]+c)%MOD;
		return;
	}
	if(g[idx]==1)
	{
		dfs(idx+1,c,free);
		return;
	}
	dfs(idx+1,c*2%MOD,free-1);
	dfs(idx+1,c*(g[idx]-2)%MOD,free-2);
}
int main()
{
	int T;
	memset(cnt,0,sizeof(cnt));
	for(scanf("%d",&T);T;--T)
	{
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=4;++i)
			scanf("%lld",g+i);
		dfs(1,1,8);
		for(int i=0;i<=8;++i){
			printf("%lld",cnt[i]);
			if (i<8) putchar(' ');
		}
		puts("");
	}
	return 0;
}
