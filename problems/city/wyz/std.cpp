#include <bits/stdc++.h>

using namespace std;

const int N=3003;

const int mod=59393;
int cost[N];
int dp[N],from[N];

int n;


int main(){
	int k,a[12];
	scanf("%d%d",&n,&k);
	for (int j=0;j<=k;++j) scanf("%d",&a[j]);
	for (int i=1;i<n;++i){
		int x=1;
		for (int j=0;j<=k;++j){
			cost[i]+=a[j]*x;
			x=1LL*x*i%mod;
		}
		cost[i]%=mod;
	}
	if (n==2){
		printf("1 %d\n",2*cost[1]);
		printf("1 1");
	}
	dp[0]=cost[1]*n;
	for (int i=1;i<=n-2;++i){
		dp[i]=-1;
		for (int j=2;j<=i+1;++j)
			if (dp[i]<=dp[i-j+1]-cost[1]+cost[j]){
				from[i]=i-j+1;
				dp[i]=dp[i-j+1]-cost[1]+cost[j];
			}
	}
	printf("%d %d\n",n-1,dp[n-2]);
	int p=n,q=1;
	for (int i=n-2;i>0;i=from[i],--p){
		int cnt=i-from[i];
		if (p<n) printf("%d %d\n",p+1,p),--cnt;
		while (cnt--) printf("%d %d\n",q++,p);
	}
	assert(p==q);
	printf("%d %d\n",p,p+1);
	return 0;
}
