#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<vector>
#define MAXN 30005
using namespace std;
const double eps=1e-8;
const double pi=acos(-1.0);
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y)
	{x=_x;y=_y;}
	void random()
	{
		x=((rand()*rand()+rand())%200001-100000)+double(rand()%10000)/10000.0;
		y=((rand()*rand()+rand())%200001-100000)+double(rand()%10000)/10000.0;
	}
};
typedef Point Vector;
Vector operator-(Point A,Point B)
{return Vector(A.x-B.x,A.y-B.y);}
bool operator<(Point A,Point B)
{return (A.y==B.y)?(A.x<B.x):(A.y<B.y);}
int dcmp(double x)
{return fabs(x)<eps?0:(x>0?1:-1);}
double Cross(Vector A,Vector B)
{return A.x*B.y-A.y*B.x;}
int n,m,tmp;
Point p[MAXN],ch[MAXN];
void Convex()
{
	sort(p+1,p+n+1);m=0;
	for (int i=1;i<=n;i++)
	{
		while (m>1&&dcmp(Cross(ch[m]-ch[m-1],p[i]-ch[m-1]))<=0)m--;
		ch[++m]=p[i];
	}tmp=m;
	for (int i=n;i>=1;i--)
	{
		while (m>tmp&&dcmp(Cross(ch[m]-ch[m-1],p[i]-ch[m-1]))<=0)m--;
		ch[++m]=p[i];
	}m--;
}
char file[10];
int num;
vector<Point>Poly[MAXN];
void chain(int lim)
{
	int num=0,sum=0;
	vector<Point>Poly[MAXN];
	Poly[0].clear();
	while (true)
	{
		num++;
		Poly[num].clear();
		n=rand()%91+10;
		for (int i=1;i<=n;i++)
		{
			p[i].random();
			bool flag=1;
			for (int j=0;j+1<Poly[num-1].size();j++)
				if (dcmp(Cross(p[i]-Poly[num-1][j],Poly[num-1][j+1]-Poly[num-1][j]))>0)flag=0;
			if (!flag)i--;
		}
		Convex();
		for (int i=1;i<=m;i++)
			Poly[num].push_back(ch[i]);
		if (sum+Poly[num].size()>lim)
		{
			num--;
			break;
		}
		sum+=Poly[num].size();
	}
	printf("%d 100000\n",num+2);
	for (int i=1;i<=num;i++)
	{
		printf("%d %d ",Poly[i].size(),rand()%2+1);
		for (int j=0;j<Poly[i].size();j++)
			printf("%.2lf %.2lf ",Poly[i][j].x,Poly[i][j].y);
		printf("\n");
	}
	printf("4 1 -125000.00 -125000.00 125000.00 -125000.00 125000.00 125000.00 -125000.00 125000.00\n");
	printf("4 2 -175000.00 -175000.00 175000.00 -175000.00 175000.00 175000.00 -175000.00 175000.00\n");
	for (int i=1;i<=100000;i++)
	{
		int op=rand()%2+1;
		if (op==1)
		{
			printf("%d %d\n",op,rand()%num+1);
			continue;
		}
		Point P;P.random();
		while (true)
		{
			bool flag=1;
			for (int j=0;j+1<Poly[1].size();j++)
				if (dcmp(Cross(P-Poly[1][j],Poly[1][j+1]-Poly[1][j]))>0)flag=0;
			if (flag==1)break;
			P.random();
		}
		printf("%d %d %.2lf %.2lf\n",op,rand()%2+1,P.x,P.y);
	}
}
void reg(int e,double x,double y,double r,int sum,bool flag)
{
	if (!flag)num=0;
	for (int i=1;(e*i<=sum)&&(r>1);i++)
	{
		num++;Poly[num].clear();
		for (int j=0;j<e;j++)
			Poly[num].push_back(Point(x+r*cos(2*pi*double(j)/double(e)+0.01),y+r*sin(2*pi*double(j)/double(e)+0.01)));
		double a=r*2*sin(pi/e);
		r=a/2/tan(pi/e);
		r-=1;
	}
	if (flag)return;
	printf("%d 100000\n",num+2);
	for (int i=1;i<=num;i++)
	{
		printf("%d %d ",Poly[i].size(),rand()%2+1);
		for (int j=0;j<Poly[i].size();j++)
			printf("%.2lf %.2lf ",Poly[i][j].x,Poly[i][j].y);
		printf("\n");
	}
	printf("4 1 -125000.00 -125000.00 125000.00 -125000.00 125000.00 125000.00 -125000.00 125000.00\n");
	printf("4 2 -175000.00 -175000.00 175000.00 -175000.00 175000.00 175000.00 -175000.00 175000.00\n");
	for (int i=1;i<=100000;i++)
	{
		int op=rand()%2+1;
		if (op==1)
		{
			printf("%d %d\n",op,rand()%num+1);
			continue;
		}
		Point P;P.random();
		while (true)
		{
			bool flag=1;
			for (int j=0;j+1<Poly[1].size();j++)
				if (dcmp(Cross(P-Poly[1][j],Poly[1][j+1]-Poly[1][j]))>0)flag=0;
			if (flag==1)break;
			P.random();
		}
		printf("%d %d %.2lf %.2lf\n",op,rand()%2+1,P.x,P.y);
	}
}
void multi_reg(int n)
{
	num=0;
	for (int i=1;i<=n;i++)
		reg(rand()%91+10,0,double(i-1)*100000/double(n),double(i-1)*100000/double(n),100000/n,1);
	printf("%d 100000\n",num+2);
	for (int i=1;i<=num;i++)
	{
		printf("%d %d ",Poly[i].size(),rand()%2+1);
		for (int j=0;j<Poly[i].size();j++)
			printf("%.2lf %.2lf ",Poly[i][j].x,Poly[i][j].y);
		printf("\n");
	}
	printf("4 1 -125000.00 -125000.00 125000.00 -125000.00 125000.00 125000.00 -125000.00 125000.00\n");
	printf("4 2 -175000.00 -175000.00 175000.00 -175000.00 175000.00 175000.00 -175000.00 175000.00\n");
	for (int i=1;i<=100000;i++)
	{
		int op=rand()%2+1;
		if (op==1)
		{
			printf("%d %d\n",op,rand()%num+1);
			continue;
		}
		Point P;P.random();
		while (true)
		{
			bool flag=1;
			for (int j=0;j+1<Poly[1].size();j++)
				if (dcmp(Cross(P-Poly[1][j],Poly[1][j+1]-Poly[1][j]))>0)flag=0;
			if (flag==1)break;
			P.random();
		}
		printf("%d %d %.2lf %.2lf\n",op,rand()%2+1,P.x,P.y);
	}
}
void mum(int e)
{
	num=0;
	reg(e,0,0,100000,e,1);
	for (int i=-50000;i<=50000;i+=10)
		reg(rand()%7+3,i,i,9,9,1);
	printf("%d 100000\n",num+2);
	for (int i=1;i<=num;i++)
	{
		printf("%d %d ",Poly[i].size(),rand()%2+1);
		for (int j=0;j<Poly[i].size();j++)
			printf("%.2lf %.2lf ",Poly[i][j].x,Poly[i][j].y);
		printf("\n");
	}
	printf("4 1 -125000.00 -125000.00 125000.00 -125000.00 125000.00 125000.00 -125000.00 125000.00\n");
	printf("4 2 -175000.00 -175000.00 175000.00 -175000.00 175000.00 175000.00 -175000.00 175000.00\n");
	for (int i=1;i<=100000;i++)
	{
		int op=rand()%2+1;
		if (op==1)
		{
			printf("%d %d\n",op,rand()%num+1);
			continue;
		}
		Point P;P.random();
		while (true)
		{
			bool flag=1;
			for (int j=0;j+1<Poly[1].size();j++)
				if (dcmp(Cross(P-Poly[1][j],Poly[1][j+1]-Poly[1][j]))>0)flag=0;
			if (flag==1)break;
			P.random();
		}
		printf("%d %d %.2lf %.2lf\n",op,rand()%2+1,P.x,P.y);
	}
}
int main()
{
	srand(time(NULL));
	for (int T=1;T<=10;T++)
	{ 
		if (T<8)continue; 
		sprintf(file,"%d.in",T);
		freopen(file,"w",stdout);
		switch(T)
		{
			case 1:chain(50);break;
			case 2:chain(50);break;
			case 3:chain(50);break;
			case 4:reg(97,0,0,100000,100000,0);break;
			case 5:reg(93,0,0,100000,100000,0);break;
			case 6:multi_reg(4);break;
			case 7:multi_reg(8);break;
			case 8:mum(98);break;
			case 9:mum(99);break;
			case 10:mum(100);break;
			default:break;
		}
	}
	return 0;
}

