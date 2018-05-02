#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=25010;
int T,n,p,g[N],h[N],inv[N];
int inc(int x,int y){x+=y;return x>=p?x-p:x;}
int mul(int x,int y){return (ll)x*y%p;}
int main()
{
	scanf("%d%d",&T,&p);
	n=23333;
	inv[1]=1;
	for (int i=2;i<=n;i++) inv[i]=mul(p-p/i,inv[p%i]);
	for (int i=0;i<=n;i++) g[i]=1;
	for (int i=2;i<=n;i++){
		int lim=n/i,F=g[i];
		for (int k=h[0]=1;k<=lim;k++) h[k]=mul(h[k-1],mul(inv[k],F+k-1));
		for (int k=n;k>=i;k--){
			ull calc=g[k];int times=0;
			for (int l=1,pos=k-i;pos>=0;l++,pos-=i){
				calc+=(ull)g[pos]*h[l];
				if (++times==16) times=0,calc%=p;
			}
			g[k]=calc%p;
		}
		/*for (int k=n;k>=0;k--)
		for (int l=1;l<=lim;l++)
			g[k+l*i]=inc(g[k+l*i],mul(g[k],h[l]));*/
	}
	while (T--){
		scanf("%d",&n);
		printf("%d\n",g[n]);
	}
	return 0;
}
