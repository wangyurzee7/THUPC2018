#include<bits/stdc++.h>
#define mo 998244353
using namespace std;
long long fac[1010],nifac[1010],ni[1010];
long long f[1010][1010],g[1010];
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
	for (long long k=i-j+1;k<=i;k++) ans=ans*k%mo;
	return ans;
}
/*
product[1] = Series[1/(1 - x), {x, 0, n}];
product[k] = Series[product[k - 1]/(1 - x^k)^Coefficient[ product[k - 1], x^k], {x, 0, n}];
CoefficientList[product[n], x];
*/ 
int main()
{
	fac[0]=nifac[0]=1;
	for (int i=1;i<=1000;i++)
	{
		fac[i]=fac[i-1]*i%mo;
		nifac[i]=getmi(fac[i],mo-2);
	}
	for (int i=1;i<=1000;i++) ni[i]=nifac[i]*fac[i-1]%mo;
	//n=100
	//f[i][j]为子树大小最大为i的叶子数量一共为j的方案数 
	for (int i=0;i<=100;i++) f[1][i]=1;
	for (int i=2;i<=100;i++)
	{
		memset(g,0,sizeof(g));long long ls=1;
		for (int j=0;j<=100;j+=i) //g[j]=C(f[i-1][i]+j/i-1,j/i);
		{
			g[j]=ls;
			ls=ls*(f[i-1][i]+j/i)%mo;
			ls=ls*ni[j/i+1]%mo;
		}
		for (int j=0;j<=100;j++)
		for (int k=0;k<=100-j;k+=i)
			f[i][j+k]=(f[i][j+k]+f[i-1][j]*g[k])%mo;
	}
	
	for (int i=1;i<=10;i++) cerr<<i<<' '<<f[100][i]<<endl;
	
	//f[i][j]为叶子数为i子树大小最大为j的方案数 
	/*for (int j=0;j<=10;j++)
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
	for (int i=1;i<=10;i++) cerr<<i<<' '<<f[i][i]<<endl;*/
}
