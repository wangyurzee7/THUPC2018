#include<bits/stdc++.h>
#define mo 998244353
using namespace std;
long long fac[1010],nifac[1010],f[1010][1010];
long long getmi(long long a,long long x)
{
	long long ans=1;
	while (x)
	{
		if (x&1) ans=ans*a%mo;
		a=a*a%mo;
		x>>=1;
	}
	return ans;
}
long long calc(int i,int j)
{
	long long ans=nifac[j];
	for (long long k=f[i][i];k<=f[i][i]+j-1;k++) ans=ans*k%mo;
	return ans;
}
int main()
{
	fac[0]=nifac[0]=1;
	for (int i=1;i<=1000;i++)
	{
		fac[i]=fac[i-1]*i%mo;
		nifac[i]=getmi(fac[i],mo-2);
	}
	
	for (int i=1;i<=10;i++)
	for (int j=0;j<=10;j++)
	{
		if (j==0) {f[i][j]=0;continue;}
		if ((i==1)&&(j==1)) {f[i][j]=1;continue;}
		if (j>=i) {f[i][j]=f[i][j-1];continue;}
		f[i][j]=f[i][j-1];
		for (int k=1;k*j<=i;k++)
		{
			if (k*j==i) f[i][j]=(f[i][j]+(k!=1)*calc(j,k))%mo;
			else f[i][j]=(f[i][j]+(f[i-k*j][j-1]*(1+((i-k*j)<j))-((i-k*j==1)&&(j-1)))*calc(j,k))%mo;
		}
	}
	//cerr<<f[3][2]<<endl;
	for (int i=1;i<=10;i++) cerr<<i<<' '<<f[i][i]<<endl;
}
