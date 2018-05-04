#include<cstdio>
#include<cstdlib>
#include<cstring>
#include "testlib.h"
#include<set>

const int maxn=1010;

int argc=4;
char *argv[4];

int n,m,ma[10][10],map[2][10][10],ansv,t,cnt[1<<25];

char djm[100];

bool check()
{
	memset(map,0,sizeof(map));
	for (int a=1;a<=n;a++)
		for (int b=0;b<=m;b++)
			map[0][a][b]=ma[a][b];
	t++;
	while (true)
	{
		int nows=0;
		for (int a=1;a<=n;a++)
			for (int b=1;b<=m;b++)
				nows=(nows<<1)|map[0][a][b];
		if (nows==0) return false;
		if (cnt[nows]==t) return true;
		cnt[nows]=t;
		for (int a=1;a<=n;a++)
			for (int b=1;b<=m;b++)
			{
				int num=0;
				for (int c=-1;c<=1;c++)
					for (int d=-1;d<=1;d++)
						if (c!=0 || d!=0) num+=map[0][a+c][b+d];
				if (num==3 || (num==2 && map[0][a][b])) map[1][a][b]=1;
				else map[1][a][b]=0;
			}
		for (int a=1;a<=n;a++)
			for (int b=1;b<=m;b++)
				map[0][a][b]=map[1][a][b];
	}
	return false;
}

void dfs(int x,int y)
{
	if (x==n+1) {
		if (check()) ansv++;
		return;
	}
	if (y==m+1) {
		dfs(x+1,1);
		return;
	}
	ma[x][y]=1;
	dfs(x,y+1);
	ma[x][y]=0;
	dfs(x,y+1);
}

void work()
{
	int test=inf.readInt(1,30);
	for (int t=1;t<=test;t++)
	{
		n=inf.readInt(1,5);
		m=inf.readInt(1,5);
		ansv=0;
		dfs(1,1);
		int res=ouf.readInt(0,2147483647);
		if (ansv!=res) quitf(_wa,"%d %d %d %d %d\n",t,n,m,ansv,res);
		printf("%d %d\n",n,m);
	}
	quitf(_ok,"OKOK");
}

int main()
{
	for (int a=0;a<argc;a++)
		argv[a]=new char[100];
	sprintf(argv[0],"zhx.exe");
	sprintf(argv[1],"..\\data\\1.in");
	sprintf(argv[2],"..\\data\\1.ans");
	sprintf(argv[3],"..\\data\\1.ans");
	registerTestlibCmd(argc, argv);
	work();
}
