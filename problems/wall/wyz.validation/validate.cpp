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

#define eps (1e-3)

const int maxn(3e4);
const int maxm(1e5);
const int maxk(100);
const int maxSumk(1e5);
const double mx(1e5);

double X[maxn+5][maxk+5],Y[maxn+5][maxk+5];

int main(int argc,char** argv){
	registerValidation();

	
	
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testdata \"%s\"...",argv[1]);
	}
	
	int n=inf.readInt(1,maxn,"n");
	inf.readSpace();
	int m=inf.readInt(1,maxm,"m");
	readEOLN();

	
	for (int i=1;i<=n;++i){
		int k=inf.readInt(1,maxk,format("k[%d]",i));
		inf.readSpace();
		inf.readInt(1,2,format("r[%d]",i));
		for (int j=1;j<=k;++j){
			inf.readSpace();
			X[i][j]=inf.readDouble(-mx+eps,mx-eps);
			inf.readSpace();
			Y[i][j]=inf.readDouble(-mx+eps,mx-eps);
		}
		readEOLN();
	}
	for (int i=1;i<=m;++i){
		int op=inf.readInt(1,2,format("op[%d]",i));
		inf.readSpace();
		if (op==1){
			inf.readInt(1,n,format("u[%d]",i));
		}
		else{
			inf.readInt(1,2,format("v[%d]",i));
			inf.readSpace();
			double x,y;
			x=inf.readDouble(-mx+eps,mx-eps);
			inf.readSpace();
			y=inf.readDouble(-mx+eps,mx-eps);
		}
		// puts("qwq");
		readEOLN();
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}
