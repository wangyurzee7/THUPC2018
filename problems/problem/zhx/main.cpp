#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>

using namespace std;

const int maxn=110;
const int maxk=210;
const int maxr=1010;
const long double eps=1e-8;

int n,m,k,R,h;

int map[maxn][maxn];

int x[maxk],y[maxk];

int a[maxk],b[maxk],c[maxk],d[maxk];

int f[maxk],z[maxk],r[maxk],s[maxk];

int v[maxk],o[maxk],l[maxk];

int nown[maxk],nowm[maxk],skillable[maxk],bombed[maxk],dead[maxk];

int id[maxk];

int history[maxr][maxk][9];

int dx[4],dy[4];

int q[2][maxk];

int lastp;

int result[maxk];

bool use[maxk];

long double fac[1000010];

queue<int> enforce[maxk];

int get_num_of_skill(string s)
{
	if (s == "toolihai") return 1;
	if (s == "faceking") return 2;
	if (s == "onepunch") return 3;
	if (s == "rabiribi") return 4;
	if (s == "firework") return 5;
	if (s == "viuganda") return 6;
	if (s == "2dsaigao") return 7;
	if (s == "gugugugu") return 8;
	if (s == "backward") return 9;
	if (s == "hupraise") return 10;
	return -100;
}

int sign(long double l)
{
	if (fabsl(l)<=eps) return 0;
	if (l<0) return -1;
	else return 1;
}

int dis(int i,int j)
{
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

void init_one(int i)
{
	nown[i]=a[i];
	nowm[i]=b[i];
	skillable[i]=0;
	bombed[i]=0;
	while (enforce[i].size())
		enforce[i].pop();
	dead[i]=0;
}

void init()
{
	scanf("%d%d%d%d",&n,&m,&k,&R);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&map[i][j]);
	for (int i=1;i<=k;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
		scanf("%d%d",&f[i],&z[i]);
		scanf("%d",&r[i]);

		string name;
		cin>>name;
		s[i]=get_num_of_skill(name);

		if (s[i] == 1) {
		} else if (s[i] == 2){
		} else if (s[i] == 3) {
			scanf("%d%d",&v[i],&l[i]);
		} else if (s[i] == 4) {
			scanf("%d",&v[i]);
		} else if (s[i] == 5) {
			scanf("%d",&l[i]);
		} else if (s[i] == 6) {
		} else if (s[i] == 7) {
			scanf("%d%d%d",&o[i],&v[i],&l[i]);
		} else if (s[i] == 8) {
		} else if (s[i] == 9) {
			scanf("%d",&l[i]);
		} else if (s[i] == 10) {
		}
		else {
			//fprintf(stderr,"wang yu zhong tian xia wu di, yang jing qin ye ye sheng hui.\n");
		}

		init_one(i);
	}

	for (int i=0;i<=n+1;i++)
		map[i][0]=map[i][m+1]=1;
	for (int i=0;i<=m+1;i++)
		map[0][i]=map[n+1][i]=1;

	lastp = 0;
}

void respawn(int i)
{
	//fprintf(stderr,"%d respawns\n",i);
	init_one(i);
}

void recover() {
	//fprintf(stderr,"recover begin\n");
	for (int i=1;i<=k;i++)
	{
		if (dead[i]>0) 
		{
			dead[i]--;
			if (!dead[i]) respawn(i);
		}
		if (f[i]>0) f[i]--;
		if (skillable[i]>0) skillable[i]--;
		if (bombed[i]>0) bombed[i]--;
		while (enforce[i].size()>0) 
		{
			int fv = enforce[i].front();
			if (fv == h)
			{
				enforce[i].pop();
				nown[i] = max(nown[i]-v[i],0);
				nowm[i] = min(nowm[i],max(nown[i]-v[i],0));
				//fprintf(stderr,"%d enforce disappears, back to (%d,%d)\n",i,nown[i],nowm[i]);
			}
			else break;
		}
	}
}

void log()
{
	for (int i=1;i<=k;i++)
	{
		history[h][i][0] = h;
		history[h][i][1] = x[i];
		history[h][i][2] = y[i];
		history[h][i][3] = d[i];
		history[h][i][4] = nown[i];
		history[h][i][5] = nowm[i];
		history[h][i][6] = dead[i];
		history[h][i][7] = bombed[i];
		history[h][i][8] = skillable[i];
	}
}

void move() {
	//fprintf(stderr,"move begins\n");	
	for (int i=1;i<=k;i++)
		if (!bombed[i] && !dead[i])
		{
			int xx=x[i]+dx[d[i]];
			int yy=y[i]+dy[d[i]];
			if (map[xx][yy])
			{
				d[i]=d[i]^1;
				//fprintf(stderr,"%d turns at (%d,%d)\n",i,x[i],y[i]);
			}
			else
			{
				//fprintf(stderr,"%d moves from (%d,%d) to (%d,%d)\n",i,x[i],y[i],xx,yy);
				x[i]=xx;
				y[i]=yy;
			}
		}
}

bool dfs(int now)
{
	for (int i=1;i<=k;i++)
		if (c[i] && ((nown[i]^nown[now])%3==0) && !use[i])
		{
			use[i]=true;
			if (!result[i] || dfs(result[i]))
			{
				result[i]=now;
				return true;
			}
		}
	return false;
}

void matching()
{
	int ans=0;
	memset(result,0,sizeof(result));
	for (int i=1;i<=k;i++)
		if (!c[i])
		{
			memset(use,false,sizeof(use));
			if (dfs(i)) ans++;
		}
	printf("%d\n",ans);
}

bool check_in(int j,int i)
{
	int ndx = x[j]-x[i];
	int ndy = y[j]-y[i];
	if (d[i] == 0) ndx=-ndx;
	else if (d[i] == 2)
	{
		ndy = -ndy;
		swap(ndx,ndy);
	}
	else swap(ndx,ndy);
	return ndx >= 1 && ndx <= v[i] && ndy >= -ndx && ndy <= ndx;
}

void skill() {
	//fprintf(stderr,"skill begin\n");
	bool skip[2] = {false,false};
	for (int i=1;i<=k;i++)
		if (!f[i] && !skillable[i] && !skip[c[i]] && !dead[i])
		{
			//fprintf(stderr,"%d use skills %d\n",i,s[i]);
			f[i]=z[i];
			if (s[i] == 1) {
				lastp = i;
			} else if (s[i] == 2){
				for (int j=1;j<=k;j++)
					if (!dead[j])
					{
						if (d[j] == 0) d[j]=2;
						else if (d[j] == 1) d[j]=3;
						else if (d[j] == 2) d[j]=1;
						else d[j]=0;
					}
			} else if (s[i] == 3) {
				enforce[i].push(h+l[i]);
				nown[i] += v[i];
				//fprintf(stderr,"enforce to (%d,%d)\n",nown[i],nowm[i]);
			} else if (s[i] == 4) {
				for (int j=1;j<=k;j++)
					if (check_in(j,i))
					{
						//fprintf(stderr,"%d is knoced from (%d,%d) to",j,x[j],y[j]);
						x[j] += dx[d[i]];
						y[j] += dy[d[i]];
						while (map[x[j]][y[j]])
						{
							if (!x[j]) x[j]=n;
							else if (x[j]==n+1) x[j]=1;
							else if (!y[j]) y[j]=m;
							else if (y[j]==m+1) y[j]=1;
							else {
								x[j] += dx[d[i]];
								y[j] += dy[d[i]];
							}
						}
						//fprintf(stderr," (%d,%d)\n",x[j],y[j]);
					}
			} else if (s[i] == 5) {
				if (lastp) bombed[lastp] += l[i];
				else bombed[i] += l[i];
			} else if (s[i] == 6) {
				int maxp=0,minp=0;
				for (int j=1;j<=k;j++)
					if (dead[j])
					{
						int distance = dis(i,j);
						if (c[i] == c[j])
						{
							if (!maxp || distance>=dis(maxp,i)) maxp=j;
						}
						else
						{
							if (!minp || distance<=dis(minp,i)) minp=j;
						}
					}
				if (maxp) respawn(maxp);
				else if (minp) respawn(minp);
			} else if (s[i] == 7) {
				int nx = x[i];
				int ny = y[i];
				int ndx = dx[d[i]], ndy = dy[d[i]];
				if (d[i] == 0) ndy = 1;
				else if (d[i] == 1) ndy = -1;
				else if (d[i] == 2) ndx = -1;
				else ndx = 1;
				for (int j=1;j<=o[i];j++)
				{
					int nnx = nx + ndx;
					int nny = ny + ndy;
					if (map[nnx][nny])
					{
						ndx = ndy;
						ndy = -ndx;
						nnx = nnx + ndx;
						nny = nny + ndy;
						nnx = (nnx+nx) / 2;
						nny = (nny+ny) / 2;
						if (map[nnx][nny])
						{
							ndx = ndy;
							ndy = -ndx;
						}
						else
						{
							nx = nnx;
							ny = nny;
						}
					}
					else
					{
						nx = nnx;
						ny = nny;
					}
				}
				x[0]=nx;y[0]=ny;
				//fprintf(stderr,"bomed at (%d,%d)\n",x[0],y[0]);
				for (int j=1;j<=k;j++)
					if (dis(0,j)<=v[i]) 
					{
						skillable[j]+=l[i];
						//fprintf(stderr,"effect %d\n",j);
					}
			} else if (s[i] == 8) {
				skip[c[i]] = true;
			} else if (s[i] == 9) {
				int j = h-l[i];
				x[i]=history[j][i][1];
				y[i]=history[j][i][2];
				d[i]=history[j][i][3];
				nown[i]=history[j][i][4];
				nowm[i]=history[j][i][5];
				dead[i]=history[j][i][6];
				bombed[i]=history[j][i][7];
				skillable[i]=history[j][i][8];
				//fprintf(stderr,"%d jumps back to %d\n",i,j);
			} else if (s[i] == 10) {
				//fprintf(stderr,"matching begins\n");
				matching();
			}
			else {
				printf("wang yu zhong tian xia wu di, yang jing qin ye ye sheng hui.\n");
			}
		}
}

bool cmp(int i,int j)
{
	if (x[i]==x[j]) return y[i]<y[j];
	else return x[i]<x[j];
}

void change(int i,int j)
{
	nown[j]=max(nown[j]-nown[i],0);
	nowm[j]=max(nowm[j]-nown[i],0);
}

void die(int i)
{
	dead[i]=r[i];
}

long double combinational(int i)
{
	return fac[nown[i]]-fac[nowm[i]]-fac[nown[i]-nowm[i]];
}

bool cmp2(int i,int j)
{
	return sign(combinational(i)-combinational(j))<0;
}

void fight() {
	//fprintf(stderr,"fight begins\n");
	for (int i=1;i<=k;i++)
		id[i] = i;
	sort(id+1,id+k+1,cmp);
	for (int i=1;i<=k;)
	{
		int j=i;
		while (j<=k && x[id[j]]==x[id[i]] && y[id[j]]==y[id[i]])
			j++;
		bool exists[2] = {false,false};
		for (int t=i;t<j;t++)
			if (!dead[id[t]]) exists[c[id[t]]] = true;
		if (exists[0] && exists[1])
		{
			int cnt[2] = {0,0};
			for (int t=i;t<j;t++)
				if (!dead[id[t]])
				{
					cnt[c[id[t]]]++;
					q[c[id[t]]][cnt[c[id[t]]]]=id[t];
				}
			sort(q[0]+1,q[0]+cnt[0]+1,cmp2);
			sort(q[1]+1,q[1]+cnt[1]+1,cmp2);
			//fprintf(stderr,"One fight begins\n");
			//fprintf(stderr,"Team 0");
			//for (int t=1;t<=cnt[0];t++)
				//fprintf(stderr," %d",q[0][t]);
			//fprintf(stderr,"\n");
			//fprintf(stderr,"Team 1");
			//for (int t=1;t<=cnt[1];t++)
				//fprintf(stderr," %d",q[1][t]);
			//fprintf(stderr,"\n");
			int p1=cnt[0],p2=cnt[1];
			while (p1!=0 && p2!=0)
			{
				int id1=q[0][p1];
				int id2=q[1][p2];
				if (cmp2(id1,id2))
				{
					p1--;
					change(id1,id2);
					die(id1);
				}
				else
				{
					if (cmp2(id2,id1))
					{
						p2--;
						change(id2,id1);
						die(id2);
					}
					else
					{
						p1--;
						p2--;
						die(id2);
						die(id1);
					}
				}
			}
			//fprintf(stderr,"fight res %d %d\n",p1,p2);
		}
		i=j;
	}
}

void gg_check()
{
	for (int i=1;i<=k;i++)
		if (x[i]<1 || x[i]>n || y[i]<1 || y[i]>m)
		{
			printf("%d\n",h);
			exit(0);
		}
}

void simulate()
{
	for (int now_round=1;now_round<=R;now_round++)
	{
		//fprintf(stderr,"%d ronud begins\n",now_round);
		h = now_round;

		recover();
		log();
		move();
		skill();
		fight();
		//gg_check();
	}
	for (int i=1;i<=k;i++)
		printf("%d %d\n",x[i],y[i]);
}

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	dx[0]=-1;dx[1]=1;dy[2]=-1;dy[3]=1;
	for (int a=1;a<=1000000;a++)
		fac[a]=fac[a-1]+logl(a);
	int T;
	scanf("%d",&T);
	for (int test=1;test<=T;test++)
	{
		//printf("%d\n",test);
		//fprintf(stderr,"%d game begins\n",test);
		init();
		simulate();
		//fprintf(stderr,"\n\n");
	}

	return 0;
}
