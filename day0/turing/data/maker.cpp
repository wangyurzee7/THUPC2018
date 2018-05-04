#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<ctime>
using namespace std;
int fin;
char file[10];
int main()
{
	srand(time(NULL));
	for (int T=1;T<=4;T++)
	{
		sprintf(file,"%d.in",T);
		freopen(file,"w",stdout);
		for (int i=1;i<=4;i++)
			printf("%d",rand()%90000+10000);
		fin=rand()%90000+10000;
		while (fin%4!=T%4)fin=rand()%90000+10000;
			printf("%d\n",fin);
	}
	return 0;
}

