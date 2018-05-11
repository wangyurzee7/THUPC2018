#include <bits/stdc++.h>
#define ll long long

using namespace std;
const ll P=2148473648;

void work(){
	int n[4];
	ll a,b,c,d;
	for (int i=0;i<4;++i) scanf("%d",&n[i]);
	sort(n,n+4,greater<int>());
	a=n[0];b=n[1];c=n[2];d=n[3];
	ll ans[9];
	memset(ans,0,sizeof(ans));
	if (a==1){
		ans[8]=1;
	}
	else if (b==1){
		ans[7]=2;
		ans[6]=a-2;
	}
	else if (c==1){
		ans[6]=4;
		ans[5]=2*(a-2+b-2);
		ans[4]=(a-2)*(b-2);
	}
	else if (d==1){
		ans[5]=8;
		ans[4]=4*(a-2+b-2+c-2);
		ans[3]=2*((a-2)*(b-2)+(a-2)*(c-2)+(b-2)*(c-2));
		ans[2]=(a-2)*(b-2)*(c-2);
	}
	else{
		ans[4]=16;
		ans[3]=8*(a-2+b-2+c-2+d-2);
		ans[2]=4*((a-2)*(b-2)+(a-2)*(c-2)+(a-2)*(d-2)+(b-2)*(c-2)+(b-2)*(d-2)+(c-2)*(d-2));
		ans[1]=2*((a-2)*(b-2)*(c-2)+(a-2)*(b-2)*(d-2)+(a-2)*(c-2)*(d-2)+(b-2)*(c-2)*(d-2));
		ans[0]=(a-2)*(b-2)*(c-2)%P*(d-2);
	}
	for (int i=0;i<=8;++i){
		printf("%d",int(ans[i]%P));
		if (i==8) puts("");
		else putchar(' ');
	}
}

int main(){
	int T;
	scanf("%d",&T);
	while (T--) work();
	return 0;
}
