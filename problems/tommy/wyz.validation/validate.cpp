#include <bits/stdc++.h>
#include "testlib.h"
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

const int maxn(234567);

struct UnionSet{
	int *f;
	void makeSet(int x){f[x]=x;}
	void init(int n){f=new int[n+1];for (int i=1;i<=n;++i) makeSet(i);}
	int find(int x){return f[x]=f[x]==x?x:find(f[x]);}
	bool Union(int x,int y){
		if (find(x)!=find(y))
			f[f[x]]=f[y];
		else return 0;
		return 1;
	}
} us;

void readEOLN(){
	char ch=inf.readChar();
	if (ch=='\n') return;
	ensuref(ch=='\r',"Expected EOLN!!!");
	inf.readEoln();
}

int main(int argc,char** argv){
	registerValidation();

	
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testdata \"%s\"...",argv[1]);
	}
	
	int n=inf.readInt(1,maxn,"n");
	inf.readSpace();
	int a=inf.readInt(1,maxn,"a");
	inf.readSpace();
	int b=inf.readInt(1,maxn,"b");
	readEOLN();
	// ensuref(a!=b,"a=b!!!");// That's wrong!

	us.init(n);
	for (int i=1;i<n;++i){
		int u=inf.readInt(1,n,format("u[%d]",i));
		inf.readSpace();
		int v=inf.readInt(1,n,format("v[%d]",i));
		readEOLN();
		ensuref(us.Union(u,v),"Circle Found");
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}
