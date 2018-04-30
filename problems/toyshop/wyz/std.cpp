#include <bits/stdc++.h>
#define ll long long

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	bool flag=0;
	while (ch<'0'||ch>'9'){
		flag=ch=='-';
		ch=getchar();
	}
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return flag?-ret:ret;
}

//#define DEBUG

const int N=30004;
const int M=64;

int m;

struct SegmentTree{
	struct STnode{
		int l,r;
		int mx[M];
		int weightTag;
		int valueTag;
	} t[N*4];
	void PushUp(int x){
		for (int i=1;i<=m;++i) t[x].mx[i]=max(t[x<<1].mx[i],t[x<<1^1].mx[i]);
	}
	void addValue(int x,int dlt){
		t[x].valueTag+=dlt;
		for (int i=1;i<=m;++i) t[x].mx[i]+=t[x].valueTag;
	}
	void addWeight(int x,int b){
		t[x].weightTag+=b;
		if (t[x].weightTag>=m) t[x].weightTag-=m;
		for (int i=(m-b)>>1;i;--i) swap(t[x].mx[i],t[x].mx[m-b-i+1]);
		// [1,m-b]
		for (int i=b>>1;i;--i) swap(t[x].mx[m-i+1],t[x].mx[m-b+i]);
		// [m-b+1,m]
		for (int i=m>>1;i;--i) swap(t[x].mx[i],t[x].mx[m-i+1]);
		// [1,m]
	}
	void PushDown(int x){
		if (t[x].l==t[x].r) return;
		if (t[x].valueTag){
			addValue(x<<1,t[x].valueTag);
			addValue(x<<1^1,t[x].valueTag);
			t[x].valueTag=0;
		}
		if (t[x].weightTag){
			addWeight(x<<1,t[x].weightTag);
			addWeight(x<<1^1,t[x].weightTag);
			t[x].weightTag=0;
		}
	}
	void build(int x,int l,int r,int *w,int *v){
		t[x].l=l;t[x].r=r;
		t[x].weightTag=0;
		t[x].valueTag=0;
		if (l==r){
			memset(t[x].mx,0,sizeof(t[x].mx));
			t[x].mx[w[l]]=v[l];
			#ifdef DEBUG
			printf("%d [%d,%d]  -> ",x,l,r);
			for (int i=1;i<=m;++i) printf("%d ",t[x].mx[i]);
			puts("");
			#endif
			return;
		}
		int mid=(l+r)/2;
		build(x<<1,l,mid,w,v);
		build(x<<1^1,mid+1,r,w,v);
		PushUp(x);
		#ifdef DEBUG
		printf("%d [%d,%d]  -> ",x,l,r);
		for (int i=1;i<=m;++i) printf("%d ",t[x].mx[i]);
		puts("");
		#endif
	}
	void modifyValue(int x,int l,int r,int dlt){
		PushDown(x);
		if (l<=t[x].l&&t[x].r<=r){addValue(x,dlt);return;}
		int mid=(t[x].l+t[x].r)>>1;
		if (l<=mid) modifyValue(x<<1,l,r,dlt);
		if (r>mid) modifyValue(x<<1^1,l,r,dlt);
		PushUp(x);
	}
	void modifyWeight(int x,int l,int r,int b){
		PushDown(x);
		if (l<=t[x].l&&t[x].r<=r){addWeight(x,b);return;}
		int mid=(t[x].l+t[x].r)>>1;
		if (l<=mid) modifyWeight(x<<1,l,r,b);
		if (r>mid) modifyWeight(x<<1^1,l,r,b);
		PushUp(x);
	}
	void query(int x,int l,int r,int *res){
		PushDown(x);
		if (l<=t[x].l&&t[x].r<=r){
			for (int i=1;i<=m;++i)
				res[i]=max(res[i],t[x].mx[i]);
			return;
		}
		int mid=(t[x].l+t[x].r)>>1;
		if (r>mid) query(x<<1^1,l,r,res);
		if (l<=mid) query(x<<1,l,r,res);
	}
} st;


int n,w[N],v[N];


int value[M];
int dp[M];

int main(){
	n=read();m=read();
	for (int i=1;i<=n;++i) w[i]=read();
	for (int i=1;i<=n;++i) v[i]=read();
	st.build(1,1,n,w,v);
	for (int Q=read();Q;Q--){
		int op=read(),l=read(),r=read();
		if (op==1) st.modifyWeight(1,l,r,read());
		else if (op==2) st.modifyValue(1,l,r,read());
		else if (op==3){
			memset(value,0,sizeof(value));
			st.query(1,l,r,value);
			#ifdef DEBUG
			for (int i=1;i<=m;++i) printf("%d ",value[i]);
			puts("");
			#endif
			
			memset(dp,0,sizeof(dp));
			for (int i=1;i<=m;++i)
				for (int j=i;j<=m;++j)
					dp[j]=max(dp[j],dp[j-i]+value[i]);
			
			ll ans0=0;
			int ans1=0;
			for (int j=1;j<=m;++j){
				ans0+=dp[j];
				ans1^=dp[j];
			}
			printf("%lld %d\n",ans0,ans1);
		}
	}
	return 0;
}
