#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include "testlib.h"

using namespace std;

int argc=4;
char *argv[4];

int n,m,k,ma[1510][1510],d[5000010],dx[4],dy[4];

int able[3010][3010],t;

int q[1500*500][2];

int base=1500;

int solve()
{
	int x=0,y=0;
	int minx=0,maxx=0,miny=0,maxy=0;
	able[x+base][y+base]=++t;
	for (int a=1;a<=k;a++)
	{
		x+=dx[d[a]];
		y+=dy[d[a]];
		able[x+base][y+base]=t;
		minx=min(minx,x);
		maxx=max(maxx,x);
		miny=min(miny,y);
		maxy=max(maxy,y);
	}
	int cnt=0;
	for (int a=1;a<=n;a++)
		for (int b=1;b<=m;b++)
			if (ma[a][b])
			{
				cnt++;
				q[cnt][0]=a;
				q[cnt][1]=b;
			}
	printf("%d\n",cnt);
	int res=0;
	for (int a=1-minx;a<=n-maxx;a++)
		for (int b=1-miny;b<=m-maxy;b++)
		{
			bool ablex=true;
			for (int c=1;c<=cnt && ablex;c++)
				if (able[q[c][0]-a+base][q[c][1]-b+base]==t) ablex=false;
			if (ablex) 
			{
				res++;
			}
		}
	return res;
}

void work()
{
	n=inf.readInt(2,1500);
	m=inf.readInt(2,1500);
	k=inf.readInt(1,5000000);
	for (int a=1;a<=n;a++)
	{
		string s = inf.readToken();
		if (s.size()!=m) quitf(_wa,"what ghost0?");
		for (int b=1;b<=m;b++)
			if (s[b-1]=='0') ma[a][b]=0;
			else if (s[b-1]=='1') ma[a][b]=1;
			else quitf(_wa,"what ghost1?");
	}
	for (int a=0;a<=n+1;a++)
		ma[a][0]=ma[a][m+1]=1;
	for (int a=0;a<=m+1;a++)
		ma[0][a]=ma[n+1][a]=1;
	string s = inf.readToken();
	if (s.size()!=k) quitf(_wa,"what ghost2?");
	for (int a=1;a<=k;a++)
	{
		if (s[a-1]=='w') d[a]=0;
		else if (s[a-1]=='s') d[a]=1;
		else if (s[a-1]=='a') d[a]=2;
		else if (s[a-1]=='d') d[a]=3;
		else quitf(_wa,"what ghost3?");
	}
	int ans=ouf.readInt(0,2147483647);

	int res=solve();
	
	if (ans!=res) quitf(_wa,"not ok %d %d",ans,res);
}

int main()
{
	dx[0]=-1;dx[1]=1;dy[2]=-1;dy[3]=1;
	for (int a=0;a<argc;a++)
		argv[a]=new char[100];
	for (int a=1;a<=21;a++)
	{
		printf("%d\n",a);
		sprintf(argv[0],"zhx.exe");
		sprintf(argv[1],"..\\data\\%d.in",a);
		sprintf(argv[2],"..\\data\\%d.ans",a);
		sprintf(argv[3],"..\\data\\%d.ans",a);
		registerTestlibCmd(argc, argv);
		work();
	}
	quitf(_ok,"OKOK");
	
	return 0;
}
