#include <bits/stdc++.h>

using namespace std;

const int N=1000006;

struct Hash{
	int base,P;
	int bin[N],hash[N];
	Hash(){}
	void prepare(int _base,int _P,char *s){
		base=_base;
		P=_P;
		int n=strlen(s+1);
		bin[0]=1;hash[0]=0;
		for (int i=1;i<=n;++i){
			hash[i]=(1LL*hash[i-1]*base%P+s[i])%P;
			bin[i]=1LL*bin[i-1]*base%P;
		}
	}
	int get_hash(int l,int r){
		return (hash[r]-1LL*hash[l-1]*bin[r-l+1]%P+P)%P;
	}
} h,r;


char st[N];
int n;

const int _base=233;
const int _P=998244353;

void work(){
	scanf("%s",st+1);
	n=strlen(st+1);
	h.prepare(_base,_P,st);
	for (int i=n>>1;i;--i) swap(st[i],st[n-i+1]);
	r.prepare(_base,_P,st);
	for (int i=1;i<n;++i){
		int len=i;
		if (i+len-1>n) len=n+1-i;
		// printf("[debug]%d %d   %d %d\n",i,i+len-1,n-len+1,n);
		if (h.get_hash(i,i+len-1)==r.get_hash(n-i+1,n-i+len)){
			// printf("[[%d] %d %d     %d %d ]",i,i+len,n,2,n-i-len+2);
			if (h.get_hash(i+len,n)==h.get_hash(2,n-i-len+2))
				if (i>1||h.get_hash(1,n-1)==h.get_hash(2,n)) printf("%d ",i);
		}
	}
	printf("%d\n",n);
}

int main(){
	int T;
	scanf("%d",&T);
	while (T--) work();
	return 0;
}
