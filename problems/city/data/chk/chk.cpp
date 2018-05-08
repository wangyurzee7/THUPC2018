#include<cstdio>
#include"testlib.h"
#define MAXN 3005
#define MOD 59393
using namespace std;
int n,k,a[15];
int std_n,std_val;
int ans_n,ans_val;
int u,v,fa[MAXN],indgr[MAXN];
int sum;
double S;
int find(int u)
{
	if (fa[u]!=u)fa[u]=find(fa[u]);
	return fa[u];
}
int calc(int d)
{
	int ans=0,x=1;
	for (int i=0;i<=k;i++,x*=d,x%=MOD)
		ans+=a[i]*x,ans%=MOD;
	return ans%MOD;
}
int main(int argc,char*argv[])
{
	FILE *fi,*fans,*fstd,*fscore,*fr;
	fi=fopen(argv[1],"r");
	fans=fopen(argv[2],"r");
	fstd=fopen(argv[3],"r");
	fscore=fopen(argv[4],"r");
	fr=fopen(argv[5],"w");
	fscanf(fscore,"%lf",&S);
	fscanf(fi,"%d%d",&n,&k);
	for (int i=0;i<=k;i++)
		fscanf(fi,"%d",&a[i]);
	fscanf(fstd,"%d%d",&std_n,&std_val);
	for (int i=1;i<n;i++)
		fscanf(fstd,"%d%d",&u,&v);
	registerTestlibCmd(4,argv);
	ans_n=ouf.readInt();
	ans_val=ouf.readInt();
	if ((std_n!=ans_n)||(std_val!=ans_val))
	{
		fprintf(fr,"0\nWrong Answer.\n");
		quitf(_ok,"No Problem.");
	}
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=1;i<n;i++)
	{
		u=ouf.readInt();
		v=ouf.readInt();
		if ((u==v)||(u>n)||(v>n)||(u<1)||(v<1))
		{
			fprintf(fr,"0\nWrong Answer.\n");
			quitf(_ok,"No Problem.");
		}
		indgr[u]++;indgr[v]++;
		if (find(u)==find(v))
		{
			fprintf(fr,"0\nWrong Answer.\n");
			quitf(_ok,"No Problem.");
		}
		fa[find(u)]=find(v);
	}
	for (int i=1;i<=n;i++)
		sum+=calc(indgr[i]);
	if (sum!=std_val)
	{
		fprintf(fr,"0\nWrong Answer.\n");
		quitf(_ok,"No Problem.");
	}
	else
	{
		fprintf(fr,"%d\nAccepted.\n",(int)S);
		quitf(_ok,"No Problem.");
	}
	return 0;
}

