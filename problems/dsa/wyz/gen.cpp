#include <bits/stdc++.h>

using namespace std;

int main(int argc,char** argv){
	if (argc<=1){
		cerr<<"Too Few Arguments!!!"<<endl;
		return 0;
	}
	unsigned int seed=atoi(argv[1]);
	int n=argc>2?atoi(argv[2]):3;
	int m=argc>3?atoi(argv[3]):5;
	int q=argc>4?atoi(argv[4]):10;
	int mod=argc>5?atoi(argv[5]):6;
	srand(seed);
	printf("%d %d %d\n",n,m,q);
	for (int i=1;i<=2*n;++i,puts(""))
		for (int j=1;j<=m;++j) printf("%d ",rand()%(mod*2+1)-mod);
	for (int i=1;i<=q;++i,puts(""))
		for (int j=1;j<=n;++j) printf("%d ",rand()%(m+1));
	return 0;
}
