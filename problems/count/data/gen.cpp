#include<bits/stdc++.h>
#define ll long long 
using namespace std;

namespace MillerRabin{

const int times=20;

ll Random(ll n){
	return ((double)rand()/RAND_MAX*n+0.5);
}

ll fast_mul(ll x,ll y,ll P){
	ll ret=0;
	while (y){
		if (y&1) ret=(ret+x)%P;
		x=(x+x)%P;
		y>>=1;
	}
	return ret;
}

ll fast_pow(ll x,ll y,ll P){
	ll ret=1;
	while (y){
		if (y&1) ret=fast_mul(ret,x,P);
		x=fast_mul(x,x,P);
		y>>=1;
	}
	return ret;
}

bool witness(ll a,ll n)
{
	ll tem=n-1;
	int j=0;
	while (tem%2==0){
		tem/=2;
		j++;
	}
	ll x=fast_pow(a,tem,n);
	if(x==1||x==n-1) return 1;
	while (j--){
		x=fast_mul(x,x,n);
		if(x==n-1) return 1;
	}
	return 0;
}

bool miller_rabin(ll n){
	if(n==2) return 1;
	if(n<2||n%2==0) return 0;
	for(int t=1;t<=times;++t){
		ll a=Random(n-2)+1;
		if(!witness(a,n)) return 0;
	}
	return 1;
}

inline bool isPrime(ll x){return miller_rabin(x);}

};

int a[2333];
const int maxn=23333;

void gen(){
	int t=233-rand()%2*rand()%6;
	int P=rand()&((1<<30)-1)|(1<<29);
	while (!MillerRabin::isPrime(P)) P=rand()&((1<<30)-1)|(1<<29);
	assert(MillerRabin::isPrime(P));
	assert(P<(1<<30));
	printf("%d %d\n",t,P);
	for (int i=1;i<=50;i++) a[i]=i;
	for (int i=51;i<=100;i++) a[i]=rand()%1000+1;
	for (int i=101;i<t;i++) a[i]=rand()%maxn+1;
	a[t]=maxn-rand()%2*rand()%66;
	for (int i=1;i<=t;i++) swap(a[i],a[rand()%i+1]);
	for (int i=1;i<=t;i++) printf("%d\n",a[i]);
}

int main()
{
	unsigned int seed=time(NULL);
	srand(seed);
	const int cas=10;
	for (int t=0;t<cas;++t){
		char fname[23];
		sprintf(fname,"%d.in",t+1);
		freopen(fname,"w",stdout);
		gen();
		fclose(stdout);
	}
	return 0;
}

