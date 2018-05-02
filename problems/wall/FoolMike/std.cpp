#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
const int N=2e5+10;
int n,m,fa[N],tp[N],op[N],qv[N],qt[N],nxt[N],pre[N];
double val[N];
struct point{
	double x,y;
	point(double x=0,double y=0):x(x),y(y){}
	point operator + (const point &a)const{return point(x+a.x,y+a.y);}
	point operator - (const point &a)const{return point(x-a.x,y-a.y);}
	double operator * (const point &a)const{return x*a.y-y*a.x;}
}pt[N];
double curx;
struct scan{
	int id;//from which convex hall
	bool tp;//insert:1, erase:0
	double x,k,b;
	bool operator < (const scan &a)const{return x<a.x;}
};
vector<scan> A;
struct query{
	int id;
	double x,y;
	bool operator < (const query &a)const{return x<a.x;}
};
vector<query> B;
struct LCT{
	int fa[N],son[N][2];
	double vs[N],vv[N];
	bool rev[N];
	#define lc(x) son[x][0]
	#define rc(x) son[x][1]
	void up(int x){
		vs[x]=vs[lc(x)]+vv[x]+vs[rc(x)];
	}
	void flip(int x){
		rev[x]^=1;
		swap(lc(x),rc(x));
	}
	void down(int x){
		if (x&&rev[x]){
			if (lc(x)) flip(lc(x));
			if (rc(x)) flip(rc(x));
			rev[x]=0;
		}
	}
	void rot(int x){
		int y=fa[x],z=fa[y];
		bool b=(x==rc(y));
		fa[son[y][b]=son[x][!b]]=y;
		fa[son[x][!b]=y]=x;
		fa[x]=z;
		if (y==lc(z)) lc(z)=x;else
		if (y==rc(z)) rc(z)=x;
		up(y);up(x);
	}
	bool isroot(int x){
		return x!=lc(fa[x])&&x!=rc(fa[x]);
	}
	void splay(int x){
		for (;!isroot(x);rot(x)){
			int y=fa[x],z=fa[y];
			down(z);down(y);down(x);
			if (!isroot(y)) rot((x==lc(y))==(y==lc(z))?y:x);
		}
	}
	void access(int x){
		for (int y=0;x;y=x,x=fa[x]){
			splay(x);
			vv[x]+=vs[rc(x)];
			rc(x)=y;
			vv[x]-=vs[y];
		}
	}
	void makeroot(int x){
		access(x);
		splay(x);
		flip(x);
	}
	void link(int x,int y){
		makeroot(x);
		access(y);
		splay(y);
		fa[x]=y;
		vv[y]+=vs[x];
		up(y);
	}
	void cut(int x,int y){
		makeroot(y);
		access(x);
		splay(x);
		vv[x]-=vs[y];
		fa[y]=lc(x)=0;
		up(x);
	}
	void init(int type){
		for (int i=1;i<=n;i++)
			vv[i]=vs[i]=val[i];
		for (int i=1;i<=n;i++)
			if (tp[i]==type&&::fa[i]) link(i,::fa[i]);
	}
	double query(int x){
		access(x);
		splay(x);
		return vs[x];
	}
}T1,T2;
void calcseg(point a,point b,double &K,double &B){
	K=(a.y-b.y)/(a.x-b.x);
	B=a.y-a.x*K;
}
void read(){
	scanf("%d%d",&n,&m);
	for (int I=1;I<=n;I++){
		int k;
		scanf("%d%d",&k,&tp[I]);
		for (int i=1;i<=k;i++) scanf("%lf%lf",&pt[i].x,&pt[i].y);
		for (int i=3;i<=k;i++) val[I]+=(pt[2]-pt[1])*(pt[i]-pt[i-1])*0.5;
		int l=1,r=1;
		for (int i=1;i<=k;i++){
			if (pt[i].x<pt[l].x) l=i;
			if (pt[i].x>pt[r].x) r=i;
		}
		for (int i=1;i<k;i++) nxt[i]=i+1,pre[i+1]=i;
		nxt[k]=1;pre[1]=k;
		double K,B;
		for (int i=l;i!=r;i=nxt[i]){
			calcseg(pt[i],pt[nxt[i]],K,B);
			A.push_back((scan){I,true,pt[i].x,K,B-eps});
			A.push_back((scan){I,false,pt[nxt[i]].x,K,B-eps});
		}
		for (int i=l;i!=r;i=pre[i]){
			calcseg(pt[i],pt[pre[i]],K,B);
			A.push_back((scan){I,true,pt[i].x,K,B+eps});
			A.push_back((scan){I,false,pt[pre[i]].x,K,B+eps});
		}
	}
	for (int i=1;i<=m;i++){
		scanf("%d",&op[i]);
		if (op[i]==1) scanf("%d",&qv[i]);
		else{
			double x,y;
			scanf("%d%lf%lf",&qt[i],&x,&y);
			B.push_back((query){i,x,y});
		}
	}
}
struct segment{
	int id;
	double k,b;
	segment(int id=-1,double k=0,double b=0):id(id),k(k),b(b){}
	double cury()const{return curx*k+b;}
	bool operator < (const segment &a)const{return cury()<a.cury();}
	bool operator > (const segment &a)const{return cury()>a.cury();}
	bool operator == (const segment &a)const{return id==a.id&&k==a.k&&b==a.b;}
}curseg[N][2];
bool inrange(int id,double cury){
	double l=curseg[id][0].cury(),r=curseg[id][1].cury();
	if (l>r) swap(l,r);
	return l<cury&&cury<r;
}
vector<int> son[N];
void dfs(int x){
	for (int v:son[x]) val[x]-=val[v],dfs(v);
}
void init(){
	sort(A.begin(),A.end());
	sort(B.begin(),B.end());
	set<segment> S;
	auto Ai=A.begin();
	auto Bi=B.begin();
	for (;Ai!=A.end();++Ai){
		for (;Bi!=B.end()&&Bi->x<Ai->x;++Bi){
			curx=Bi->x;
			auto Si=S.insert(segment(-1,0,Bi->y)).first,L=Si,R=Si;
			--L;++R;
			int L_id=L->id,R_id=R->id;
			if (inrange(L_id,Bi->y)) qv[Bi->id]=L_id;
			if (inrange(R_id,Bi->y)) qv[Bi->id]=R_id;
			S.erase(Si);
		}
		curx=Ai->x;
		int id=Ai->id;
		segment cur(Ai->id,Ai->k,Ai->b);
		if (Ai->tp){
			auto Si=S.insert(cur).first,L=Si,R=Si;
			int L_id=0,R_id=0;
			if (Si!=S.begin()) --L,L_id=L->id;
			if (++R!=S.end()) R_id=R->id;
			if (L_id>0&&inrange(L_id,cur.cury())) fa[id]=L_id;
			if (R_id>0&&inrange(R_id,cur.cury())) fa[id]=R_id;
			if (curseg[id][0].id==-1) curseg[id][0]=cur;else curseg[id][1]=cur;
		}
		else{
			S.erase(cur);
			if (curseg[id][0]==cur) curseg[id][0].id=-1;else curseg[id][1].id=-1; 
		}
	}
	for (int i=1;i<=n;i++) son[fa[i]].push_back(i);
	dfs(0);
	T1.init(1);
	T2.init(2);
}
void work(){
	for (int i=1;i<=m;i++)
	if (op[i]==1){
		int v=qv[i];
		if (tp[v]==1)
			T1.link(v,fa[v]),T2.cut(v,fa[v]);
		else
			T1.cut(v,fa[v]),T2.link(v,fa[v]);
		tp[v]=3-tp[v];
	}
	else printf("%.10lf\n",(qt[i]==1?T2:T1).query(qv[i]));
}
int main()
{
	read();
	init();
	work();
	return 0;
}

