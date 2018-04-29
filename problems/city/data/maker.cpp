#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<ctime>
using namespace std;
int n,k;
char file[10];
int main()
{
	srand(time(NULL));
	for (int T=1;T<=100;T++)
	{
		sprintf(file,"%d.in",T);
		freopen(file,"w",stdout);
		n=150*((T-1)/5)+rand()%150+1;k=rand()%10+1;
		printf("%d %d\n",n,k);
		for (int i=0;i<=k;i++)
			printf("%d ",(i==k)?(rand()%51):(rand()%50+1));
		printf("\n");
	}
	return 0;
}

