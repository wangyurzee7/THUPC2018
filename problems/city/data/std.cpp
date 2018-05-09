#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<queue>
#define MAXN 3005
#define MOD 59393
#define LL long long
using namespace std;
int n,k,a[15],ans;
int dp[MAXN][MAXN];
pair<int,int>pre[MAXN][MAXN];
pair<int,int>final;
int id,pru[MAXN];
deque<int>g;
char in[10],out[10];
int calc(int d)
{
	int ans=0,x=1;
	for (int i=0;i<=k;i++,x*=d,x%=MOD)
		ans+=a[i]*x,ans%=MOD;
	return ans%MOD;
}
int main()
{
	for (int T=1;T<=100;T++)
	{
		sprintf(in,"%d.in",T);
		sprintf(out,"%d.out",T);
		freopen(in,"r",stdin);
		freopen(out,"w",stdout);
		scanf("%d%d",&n,&k);
		for (int i=0;i<=k;i++)
			scanf("%d",&a[i]);
		memset(dp,0,sizeof(dp));
		ans=0;id=1;
		dp[0][0]=n*calc(1);
		for (int i=1;i<=n-2;i++)
		{
			for (int j=0;j<i;j++)
			{
				if (dp[i-1][j]>dp[i][1])
				{
					dp[i][1]=dp[i-1][j];
					pre[i][1]=make_pair(i-1,j);
				}
			}
			dp[i][1]+=calc(2)-calc(1);
			for (int j=2;j<=i;j++)
				if (dp[i-1][j-1]+calc(j+1)-calc(j)>dp[i][j])
				{
					dp[i][j]=dp[i-1][j-1]+calc(j+1)-calc(j);
					pre[i][j]=make_pair(i-1,j-1);
				}
		}
		for (int i=0;i<=n-2;i++)
			if (dp[n-2][i]>ans)
			{
				ans=dp[n-2][i];
				final=make_pair(n-2,i);
			}
		printf("%d %d\n",n-1,ans);
		for (int i=1;i<=n-2;i++)
		{
			pru[n-i-1]=id;
			if (final.second==1)id++;
			final=pre[final.first][final.second];
		}
		g.clear();
		for (int i=id;i<=n;i++)
			g.push_back(i);
		for (int i=1;i<=n-2;i++)
		{
			printf("%d %d\n",pru[i],g.front());
			g.pop_front();
			if (pru[i+1]!=pru[i])g.push_front(pru[i]);
		}
		printf("%d %d\n",g.front(),g.back());
	}
	return 0;
}

