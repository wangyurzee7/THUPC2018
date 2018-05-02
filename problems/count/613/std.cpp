#include<bits/stdc++.h>
using namespace std;
// 	1, 1, 2, 5, 12, 33, 90, 261, 766, 2312, 7068, 21965, 68954, 218751
int a[30010],p[30010],q[30010],r[30010];

int mo;
int getmi(int a,int x)
{
	int ans=1;
	while (x)
	{
		if (x&1) ans=(long long)ans*a%mo;
		a=(long long)a*a%mo;
		x>>=1;
	}
	return ans;
}

const int maxn=23333;

int main()
{
	int t;scanf("%d%d",&t,&mo);
	a[1]=1;a[2]=1;a[3]=2;
	p[1]=1;p[2]=3;p[3]=7;
	for (int i=1;i<=3;i++)
	for (int j=i+i;j<=maxn;j+=i) q[j]=(q[j]+(long long)i*a[i])%mo;
	for (int i=4;i<=maxn;i++)
	{
		__int128 ls=0;int j;
		for (j=1;j<i-4;j+=4) ls+=(long long)p[j]*a[i-j]+(long long)p[j+1]*a[i-j-1]+(long long)p[j+2]*a[i-j-2]+(long long)p[j+3]*a[i-j-3];
		for (;j<i;j++) ls+=(long long)p[j]*a[i-j];
		r[i]=(ls*2-p[i-1]+q[i]+mo)%mo;
		a[i]=(long long)r[i]*getmi(i,mo-2)%mo;
		p[i]=(q[i]+r[i])%mo;
		for (int j=i+i;j<=maxn;j+=i) q[j]=(q[j]+(long long)i*a[i])%mo;
	}
	for (int i=2;i<=maxn;i++) a[i]=a[i]*2%mo;
	while (t--)
	{
		int n;scanf("%d",&n);
		printf("%d\n",a[n]);
	}
	return 0;
}
