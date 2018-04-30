#include <bits/stdc++.h>
#define ll long long

using namespace std;
inline int read(){
	int ret;
	scanf("%d",&ret);
	return ret;
}


const int N=30004;
const int M=64;

int m;



int n,w[N],v[N];


int value[M];
int dp[M];

int main(){
	n=read();m=read();
	for (int i=1;i<=n;++i) w[i]=read();
	for (int i=1;i<=n;++i) v[i]=read();
	for (int Q=read();Q;Q--){
		int op=read(),l=read(),r=read();
		if (op==1){
			int d=read();
			for (int i=l;i<=r;++i)
				if ((w[i]+=d)>m) w[i]-=m;
		}
		else if (op==2){
			int b=read();
			for (int i=l;i<=r;++i)
				v[i]+=b;
		}
		else if (op==3){
			memset(value,0,sizeof(value));
			for (int i=l;i<=r;++i)
				value[w[i]]=max(value[w[i]],v[i]);
			#ifdef DEBUG
			for (int i=1;i<=m;++i) printf("%d ",value[i]);
			puts("");
			#endif
			
			memset(dp,0,sizeof(dp));
			for (int i=1;i<=m;++i)
				for (int j=i;j<=m;++j)
					dp[j]=max(dp[j],dp[j-i]+value[i]);
			
			ll ans0=0;
			int ans1=0;
			for (int j=1;j<=m;++j){
				ans0+=dp[j];
				ans1^=dp[j];
			}
			printf("%lld %d\n",ans0,ans1);
		}
	}
	return 0;
}
