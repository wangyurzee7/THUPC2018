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

	const int maxn(3000);
	const int maxk(10);
	const int maxa(50);
	
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testdata \"%s\"...",argv[1]);
	}
	
	int n=inf.readInt(1,maxn,"n");
	inf.readSpace();
	int k=inf.readInt(1,maxk,"k");
	readEOLN();

	for (int i=0;i<=k;++i){
		inf.readInt(0,maxa,format("a[%d]",i));
		if (i==k) readEOLN();
		else inf.readSpace();
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}
