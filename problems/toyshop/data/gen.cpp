#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define percent(x) (rand()%100<x)


using namespace std;

#ifndef SMALL
const int maxn=200000;
const int maxQ=30000;
const int maxm=60;
const int maxv=1e7;
const int maxb=1e3;
#endif


#ifdef SMALL
const int maxn=10;
const int maxQ=10;
const int maxm=7;
const int maxv=100;
const int maxb=10;
#endif


void unqPick(int *a,int l,int r){
	for (int i=l;i<=r;++i) a[i-l]=i;
	for (int k=0;k<7;++k) random_shuffle(a,a+(r-l+1));
}
void unqPick(int *a,int n){
	unqPick(a,1,n);
}
ull randULL(){return ((ull)rand()<<30)^((ull)rand()<<50)^rand();}
ll Rand(ll mod){return (unsigned long long)rand()*rand()*rand()*rand()%mod;}
const int base=2;
int Rand_log(int ub){return pow(base,1.0*rand()/RAND_MAX*(log(ub)/log(base)));}

const int N=200005;

int n,m,Q;
int v[N],w[N];

void gen(int index){
	int p_mdf=60,p_op1=50,type=0;
	if (index<12){
		if ((index&3)==0) p_op1=2;
		if ((index&3)==1) p_op1=98;
		if ((index&3)==2) type=1;
		if ((index>>2)==0) p_mdf=1;
		if ((index>>2)==1) p_mdf=99;
	}
	else if (index==12) p_mdf=0,type=1;
	else p_mdf=60,type=2;
	n=maxn;
	Q=maxQ;
	m=maxm;
	for (int i=1;i<=n;++i) w[i]=rand()%m+1;
	for (int i=1;i<=n;++i) v[i]=rand()%(maxv-rand()%(maxv/10))*w[i]/m;
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;++i){
		printf("%d",w[i]);
		if (i==n) puts("");
		else putchar(' ');
	}
	for (int i=1;i<=n;++i){
		printf("%d",v[i]);
		if (i==n) puts("");
		else putchar(' ');
	}
	printf("%d\n",Q);
	
	for (int i=1;i<=Q;++i){
		int op,l,r,len,tmp;
		if (type==1) len=rand()%n+1;
		else if (type==2) len=n-rand()%(n/10);
		else len=Rand_log(n);
		if (percent(p_mdf)){
			if (percent(p_op1)) op=1;
			else op=2;
		}
		else op=3;
		l=rand()%(n-len+1)+1;
		r=l+len-1;
		if (op==1) tmp=rand()%m+1;
		if (op==2) tmp=rand()%(2*maxb+1)-maxb;
		printf("%d %d %d",op,l,r);
		if (op!=3) printf(" %d",tmp);
		puts("");
	}
}
int main(int argc,char **argv){
	unsigned int seed=argc>1?atoi(argv[1]):time(0);
	srand(seed);
	freopen("seed.txt","w",stdout);
	printf("%u\n",seed);
	fclose(stdout);
	const int start=2;
	const int cas=14;
	for (int t=0;t<cas;++t){
		char fname[23];
		int index=t+start;
		sprintf(fname,"%d.in",index);
		freopen(fname,"w",stdout);
		gen(t);
		fclose(stdout);
	}
	return 0;
}
