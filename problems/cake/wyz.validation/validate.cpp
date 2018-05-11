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

	const int maxT(10000);
	const int mx(1e6);
	
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testdata \"%s\"...",argv[1]);
	}
	
	int T=inf.readInt(1,maxT,"n");
	readEOLN();

	for (int i=1;i<=T;++i){
		inf.readInt(1,mx,format("a[%d]",i));inf.readSpace();
		inf.readInt(1,mx,format("b[%d]",i));inf.readSpace();
		inf.readInt(1,mx,format("c[%d]",i));inf.readSpace();
		inf.readInt(1,mx,format("d[%d]",i));
		readEOLN();
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}
