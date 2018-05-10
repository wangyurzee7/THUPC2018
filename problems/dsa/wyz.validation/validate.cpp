#include <bits/stdc++.h>
#include "testlib.h"
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

void readEOLN(){
	char ch=inf.readChar();
	if (ch=='\n') return;
	ensuref(ch=='\r',"Expected EOLN!!!");
	inf.readEoln();
}

int main(int argc,char** argv){
	registerValidation();

	const int maxn(6);
	const int maxm(666);
	const int maxq(666);
	const int mx(1e9);
	
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testdata \"%s\"...",argv[1]);
	}
	
	int n=inf.readInt(1,maxn,"n");
	inf.readSpace();
	int m=inf.readInt(1,maxm,"m");
	inf.readSpace();
	int q=inf.readInt(1,maxq,"q");
	readEOLN();

	for (int k=0;k<2;++k)
	for (int i=1;i<=n;++i)for (int j=1;j<=m;++j){
		inf.readInt(-mx,mx,format("%c[%d][%d]",k?'x':'y',i,j));
		if (j==m) readEOLN();
		else inf.readSpace();
	}
	for (int i=1;i<=q;++i)for (int j=1;j<=n;++j){
		inf.readInt(0,m,format("c[%d][%d]",i,j));
		if (j==n) readEOLN();
		else inf.readSpace();
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}
