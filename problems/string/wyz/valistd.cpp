#include <bits/stdc++.h>

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	assert(isdigit(ch));
	while (isdigit(ch)){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	assert(ch=='\n');
	return ret;
}

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

const int _base=2333;
const int _P=1000000009;
int sumn;
void work(){
	char ch=getchar();
	n=0;
	while (islower(ch)){
		st[++n]=ch;
		ch=getchar();
	}
	assert(ch=='\n');
	sumn+=n;
	assert(n<=(1e6));
	st[n+1]=0;
	h.prepare(_base,_P,st);
	for (int i=n>>1;i;--i) swap(st[i],st[n-i+1]);
	r.prepare(_base,_P,st);
	for (int i=2;i<n;++i){
		int len=i;
		if (i+len-1>n) len=n+1-i;
		if (h.get_hash(i,i+len-1)==r.get_hash(n-i+1,n-i+len)){
			if (h.get_hash(i+len,n)==h.get_hash(2,n-i-len+2))
				printf("%d ",i);
		}
	}
	printf("%d\n",n);
}

int main(){
	sumn=0;
	int T=read();
	while (T--) work();
	assert(sumn<=(5e6));
	char ch;assert(scanf("%c",&ch)==EOF);
	return 0;
}
