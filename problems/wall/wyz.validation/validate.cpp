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

inline double cross(double x0,double x1,double x2,double y0,double y1,double y2){
	return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}
inline int sgn(double x){
	return (x<-eps)?-1:(x>eps);
}
inline bool intersection(double x0,double y0,double x1,double y1,double x2,double y2,double x3,double y3){
	return sgn(cross(x0,x1,x2,y0,y1,y2))*sgn(cross(x0,x1,x3,y0,y1,y3))==-1&&sgn(cross(x2,x3,x0,y2,y3,y0))*sgn(cross(x2,x3,x1,y2,y3,y1))==-1;
}

int K[maxn];

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

	int sumk=0;
	for (int i=1;i<=n;++i){
		int k=K[i]=inf.readInt(3,maxk,format("k[%d]",i));
		inf.readSpace();
		sumk+=k;
		inf.readInt(1,2,format("r[%d]",i));
		for (int j=0;j<k;++j){
			inf.readSpace();
			X[i][j]=inf.readDouble(-mx+eps,mx-eps);
			inf.readSpace();
			Y[i][j]=inf.readDouble(-mx+eps,mx-eps);
		}
		X[i][k]=X[i][0];X[i][k+1]=X[i][1];
		Y[i][k]=Y[i][0];Y[i][k+1]=Y[i][1];
		for (int j=0;j<k;++j){
			double tmp=cross(X[i][j],X[i][j+1],X[i][j+2],Y[i][j],Y[i][j+1],Y[i][j+2]);
			ensuref(tmp>0,"Convex#%d, point#%d BOOMED!!!",i,j);
			if (tmp<eps) printf("[ WARNING!!! ] Convex#%d, point#%d is dangerous!",i,j);
		}
		readEOLN();
	}
	ensuref(sumk<=maxSumk,"sumk=%d > maxSumk=%d",sumk,maxSumk);
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
	
	for (int i=1;i<=n;++i)for (int j=i+1;j<=n;++j)
		for (int k=0;k<K[i];++k)for (int l=0;l<K[j];++l)
			ensuref(!intersection(X[i][k],Y[i][k],X[i][k+1],Y[i][k+1],X[j][l],Y[j][l],X[j][l+1],Y[j][l+1]),"Found intersection(segment[%d,%d]&segment[%d,%d])",i,k,j,l);
	
	puts("  OK!!");

	return 0;
}

