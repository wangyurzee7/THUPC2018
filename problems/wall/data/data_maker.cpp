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
	printf("4 1 -198000.00 -198000.00 198000.00 -198000.00 198000.00 198000.00 -198000.00 198000.00\n");
	printf("4 2 -199000.00 -199000.00 199000.00 -199000.00 199000.00 199000.00 -199000.00 199000.00\n");
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
	reg(e,0,0,197500,e,1);
	for (int i=-100000;i<=100000;i+=10)
	{
		int d=rand()%8+3;
		reg(d,i,i,10,d,1);
	}
	int sum=0;
	for (int i=1;i<=num;i++)
	{
		sum+=Poly[i].size();
		if (sum>99992)
		{
			num=i;
			break;
		}
	}
	printf("%d 100000\n",num+2);
	for (int i=1;i<=num;i++)
	{
		printf("%d %d ",Poly[i].size(),rand()%2+1);
		for (int j=0;j<Poly[i].size();j++)
			printf("%.2lf %.2lf ",Poly[i][j].x,Poly[i][j].y);
		printf("\n");
	}
	printf("4 1 -198000.00 -198000.00 198000.00 -198000.00 198000.00 198000.00 -198000.00 198000.00\n");
	printf("4 2 -199000.00 -199000.00 199000.00 -199000.00 199000.00 199000.00 -199000.00 199000.00\n");
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
		sprintf(file,"%d.in",T);
		freopen(file,"w",stdout);
		switch(T)
		{
			case 1:reg(3,0,0,197500,100000,0);break;
			case 2:reg(7,0,0,197500,100000,0);break;
			case 3:reg(23,0,0,197500,100000,0);break;
			case 4:reg(67,0,0,197500,100000,0);break;
			case 5:reg(97,0,0,197500,100000,0);break;
			case 6:mum(69);break;
			case 7:mum(79);break;
			case 8:mum(89);break;
			case 9:mum(99);break;
			case 10:mum(100);break;
			default:break;
		}
	}
	return 0;
}

