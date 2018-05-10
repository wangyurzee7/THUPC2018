#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define ll long long
#define fi first
#define se second
#define eps (1e-7)

using namespace std;

#define VALI
typedef ll i64;
typedef __int128_t i128;
typedef pair<int,int> pii;

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
inline void print(i128 x){
	if (x==0){
		putchar('0');
		puts("");
		return;
	}
	char buffer[66];
	int i=64;
	for (;x!=0;--i){
		buffer[i]=x%10+48;
		x/=10;
	}
	buffer[65]=0;puts(buffer+i+1);
}
template<typename T>
void Max(T &x,T y){if (y>x) x=y;}

template<typename T>
void Min(T &x,T y){if (y<x) x=y;}

template<typename t=int,typename T=i64,typename F=double>
struct Point{
public:
	t x,y;
	int id;
	Point():x(0),y(0){}
	Point(t _x,t _y,int _id=0):x(_x),y(_y),id(_id){}
	bool operator ==(const Point &p) const{
		return fabs(x-p.x)<eps&&fabs(y-p.y)<eps;
	}
	bool operator <(const Point &p) const{
		if (fabs(x-p.x)<eps) return y+eps<p.y;
		return x<p.x;
	}
	Point operator +(const Point &p) const{
		return Point(x+p.x,y+p.y);
	}
	Point operator -(const Point &p) const{
		return Point(x-p.x,y-p.y);
	}
	Point operator *(const t &k) const{
		return Point(x*k,y*k);
	}
	Point operator /(const t &k) const{
		return Point(x/k,y/k);
	}
	T operator *(const Point &p) const{
		return (T)x*p.y-(T)y*p.x;
	}
};


typedef Point<> point;

inline int sgn(i64 x){
	return x>-eps?x>=eps:-1;
}
inline i64 dot(const point &u,const point &v){
	return 1LL*u.x*v.x+1LL*u.y*v.y;
}
inline point rotate(const point &p){return point(-p.y,p.x);}


const int N=8;
const int M=670;
const int maxQ=670;

struct Query{
	int c[N];
	i128 ans;
} query[maxQ];
int Q;

point p[N][M];
int n,m;

void input(){
	n=read();m=read();Q=read();
	for (int i=0;i<n;++i)for (int j=0;j<m;++j) p[i][j].x=read();
	for (int i=0;i<n;++i)for (int j=0;j<m;++j) p[i][j].y=read();
	for (int i=0;i<n;++i)for (int j=0;j<m;++j) p[i][j].id=j;
	for (int i=0;i<Q;++i)for (int j=0;j<n;++j) query[i].c[j]=read();
	#ifdef VALI
	assert(1<=n&&n<=6);
	assert(1<=m&&m<=666);
	assert(1<=Q&&Q<=666);
	for (int i=0;i<n;++i)for (int j=0;j<m;++j){
		assert(abs(p[i][j].x)<(1e9)+eps);
		assert(abs(p[i][j].y)<(1e9)+eps);
	}
	for (int i=0;i<Q;++i)for (int j=0;j<n;++j)
		assert(0<=query[i].c[j]&&query[i].c[j]<=m);
	#endif
}

i64 _kx,_ky;

inline i64 dot(const point &u,const i64 &x,const i64 &y){
	return u.x*x+u.y*y;
}

bool cmp(const point &u,const point &v){
	return dot(u,_kx,_ky)>dot(v,_kx,_ky);
}

struct Record{
	point p;
	int belong;
	int u,v;
	Record(){}
	Record(point _p,int _belong,int _u,int _v):p(_p),belong(_belong),u(_u),v(_v){}
};

vector<Record> order;//u>v => v>u

int comp(const Record &u,const Record &v){
	int tmpu=sgn(u.p.y),tmpv=sgn(v.p.y);
	if (tmpu==0) tmpu+=1+sgn(u.p.x);
	if (tmpv==0) tmpv+=1+sgn(v.p.x);
	if (tmpu==tmpv){
		int tmp=sgn(u.p*v.p);
		if (tmp!=0) return tmp>0?1:-1;
		// else if (u.belong!=v.belong) return u.belong<v.belong?1:-1;
		else return 0;
	}
	else return tmpu>tmpv?1:-1;
}

// #define WYZSB

void init(){
	_kx=1;
	_ky=0;
	for (int i=0;i<n;++i)
		sort(p[i],p[i]+m,cmp);
	order.clear();
	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j)for (int k=0;k<m;++k){
			if (p[i][j].x==p[i][k].x&&p[i][j].y==p[i][k].y) continue;
			order.pb(Record(rotate(p[i][j]-p[i][k]),i,p[i][j].id,p[i][k].id));
		}
	sort(order.begin(),order.end(),[](const Record &u,const Record &v){
		if (u.p.x==0&&u.p.y==0) return false;
		if (v.p.x==0&&v.p.y==0) return true;
		int tmp=comp(u,v);
		if (tmp!=0) return tmp>0;
		return u.belong<v.belong;
	});
	#ifdef WYZSB
	for (auto rec:order) printf("(%d,%d) [%d] %d %d\n",rec.p.x,rec.p.y,rec.belong,rec.u,rec.v);
	#endif
}

ll sx[maxQ][N],sy[maxQ][N];
ll ssx[maxQ],ssy[maxQ];

void update(int id,int i){
	ssx[id]-=sx[id][i];
	ssy[id]-=sy[id][i];
	sx[id][i]=sy[id][i]=0;
	for (int j=0;j<query[id].c[i];++j){
		#ifdef DEBUG
		printf("(%d, %d)   ",p[i][j].x,p[i][j].y);
		#endif
		sx[id][i]+=p[i][j].x;
		sy[id][i]+=p[i][j].y;
	}
	ssx[id]+=sx[id][i];
	ssy[id]+=sy[id][i];
}

i128 calc(int id){
	#ifdef DEBUG
	printf("%d : (%lld, %lld)\n",id,ssx[id],ssy[id]);
	#endif
	return (i128)ssx[id]*ssx[id]+(i128)ssy[id]*ssy[id];
}

void debug(int code=0){	
	#ifndef WYZSB
	return;
	#endif
	for (int i=0;i<n;++i,puts(""))for (int j=0;j<m;++j) printf("%d ",p[i][j].id);
	puts("=====");
}

point lastp[N];


void work(){
	for (int i=0;i<Q;++i){
		for (int j=0;j<n;++j)
			update(i,j);
		query[i].ans=calc(i);
	}
	debug();
	int l=m,r=-1;
	for (int i=0;i<n;++i) lastp[i]=point(1,0);
	int cnt=0;
	int WYZCNT=0;
	for (auto it=order.begin();it!=order.end();++it){
		int bl=it->belong,u=it->u,v=it->v;
		for (int j=0;j<m;++j)
			if (p[bl][j].id==u||p[bl][j].id==v){
				Min(l,j);
				Max(r,j);
			}
		++cnt;
		if ((it+1)!=order.end()&&(it->belong==(it+1)->belong&&comp(*it,*(it+1))==0))
			continue;
		
		point p2(1,0);
		for (auto it2=it+1;it2!=order.end();++it2)
			if ((it2->p.x!=0||it2->p.y!=0)&&comp(*it,*it2)){
				p2=it2->p;
				break;
			}
		if (sgn((it->p)*p2)>0){
			_kx=(ll)(it->p).x+p2.x;
			_ky=(ll)(it->p).y+p2.y;
		}
		else{
			_kx=rotate(it->p).x;
			_ky=rotate(it->p).y;
		}
		
		// if (sgn(lastp[bl]*(it->p))>0) _k=(it->p)+lastp[bl];
		// else _k=rotate(lastp[bl]);
		// lastp[bl]=it->p;
		sort(p[bl],p[bl]+m,cmp);
		/* for (int j=0;;++j){
			assert(j<m-1);
			if (p[bl][j].id==u){
				l=min(l,j);
				r=j+1;
				swap(p[bl][j],p[bl][j+1]);
			}
			if (p[bl][j].id==v) break;
		}
		if (l>r) continue; */
		#ifdef WYZSB
		printf("[_k=(%d, %d) ]\n",_k.x,_k.y);
		#endif
		debug();
		// assert(r-l+1<=2*cnt);
		for (int i=0;i<Q;++i){
			if (r<=query[i].c[bl]-1||l>query[i].c[bl]-1) continue;
			++WYZCNT;
			update(i,bl);
			Max(query[i].ans,calc(i));
		}
		l=m;
		r=-1;
		cnt=0;
	}
	cerr<<"WYZCNT : "<<WYZCNT<<endl;
}

void output(){
	for (int i=0;i<Q;++i) print(query[i].ans);
}


int main(){
	input();
	init();
	work();
	output();
	return 0;
}