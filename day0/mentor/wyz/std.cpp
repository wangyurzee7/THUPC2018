#include <bits/stdc++.h>
#define N 1004
#define M 5050004
#define pb push_back
#define mp make_pair

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return ret;
}

void work(){
	int n=read(),m=read();
	for (int i=1;i<=n;++i){
		printf("%d",i);
		if (i==n) puts("");
		else putchar(' ');
	}
	for (int i=1;i<=m;++i){
		printf("%d",read());
		if (i==m) puts("");
		else putchar(' ');
	}
	for (int i=1;i<=n;++i)for (int j=1;j<=m;++j) read();
	for (int i=1;i<=n;++i) read();
}

int main(){
	for (int T=read(),C=read();T;T--) work();
	return 0;
}