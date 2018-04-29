#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define percent(x) if(rand()%100<x)


using namespace std;

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

const int maxn=1e6;

char st[maxn+5];

void gen(int type){
	printf("%d\n",5);
	if (type==0){
		for (int i=1;i<=5;++i){
			for (int j=0;j<i;++j) st[j]=rand()%26+'a';
			int n=maxn-rand()%2*rand()%7;
			for (int j=0;j<n;++j) putchar(st[j%i]);
			puts("");
		}
	}
	else if (type==1){
		for (int i=6;i<=10;++i){
			for (int j=0;j<i;++j) st[j]=rand()%3+'a';
			int n=maxn-rand()%2*rand()%7;
			for (int j=0;j<n;++j) putchar(st[j%i]);
			puts("");
		}
	}
	else if (type==2){
		int n=maxn;
		const int t[6]={0,int(sqrt(n)),int(sqrt(n)),int(n/log(n)*log(2)),n/3,n-233};
		for (int k=1;k<=5;++k){
			int i=t[k];
			if (k==1) for (int j=0;j<i;++j) st[j]=rand()%26+'a';
			else for (int j=0;j<i;++j) st[j]=(j<i-1)?'a':'b';
			n=maxn-rand()%2*rand()%7;
			for (int j=0;j<n;++j) putchar(st[j%i]);
			puts("");
		}
	}
}
int main(int argc,char **argv){
	unsigned int seed=argc>1?atoi(argv[1]):time(0);
	srand(seed);
	freopen("seed.txt","w",stdout);
	printf("%u\n",seed);
	fclose(stdout);
	const int start=2;
	const int cas=3;
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
