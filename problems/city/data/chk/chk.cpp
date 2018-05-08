#include<cstdio>
#define MAXN 3005
#define MOD 59393
using namespace std;
int n,k,a[15];
int std_n,std_val;
double ans_n,ans_val,ans_u,ans_v;
int u,v,fa[MAXN],indgr[MAXN];
int ans;
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
	fscanf(fans,"%lf%lf",&ans_n,&ans_val);
	if ((ans_n!=(int)ans_n)||(ans_val!=(int)ans_val))
	{
		fprintf(fr,"0\nWrong Answer.\n");
		return 0;
	}
	if ((std_n!=ans_n)||(std_val!=ans_val))
	{
		fprintf(fr,"0\nWrong Answer.\n");
		return 0;
	}
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=1;i<n;i++)
	{
		fscanf(fans,"%lf%lf",&ans_u,&ans_v);
		if ((ans_u!=(int)ans_u)||ans_v!=(int)ans_v)
		{
			fprintf(fr,"0\nWrong Answer.\n");
			return 0;
		}
		u=(int)ans_u;v=(int)ans_v;
		if ((u==v)||(u>n)||(v>n)||(u<1)||(v<1))
		{
			fprintf(fr,"0\nWrong Answer.\n");
			return 0;
		}
		indgr[u]++;indgr[v]++;
		if (find(u)==find(v))
		{
			fprintf(fr,"0\nWrong Answer.\n");
			return 0;
		}
		fa[find(u)]=find(v);
	}
	for (int i=1;i<=n;i++)
		ans+=calc(indgr[i]);
	if (ans!=std_val)
	{
		fprintf(fr,"0\nWrong Answer.\n");
		return 0;
	}
	fprintf(fr,"%d\nAccepted.\n",(int)S);
	return 0;
}

