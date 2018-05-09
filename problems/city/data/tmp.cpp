#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
char file[10];
int main()
{
	for (int i=1;i<=100;i++)
	{
		sprintf(file,"%d.score",i);
		freopen(file,"w",stdout);
		printf("1\n");
	}
	return 0;
}

