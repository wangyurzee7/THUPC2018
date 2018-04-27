#include <bits/stdc++.h>
#define N 520
char a[N][N],s[500010],b[N][N];
int n,m,sx,sy,range[N][2];
long long aa[N][10],b[N][10];
void process(){
    gets(s);
    int x=0,y=0,minx=0,miny=0,maxx=0,maxy=0;
    for(int i=0;s[i];++i)
    {
        if(s[i]=='w')--x;
        else if(s[i]=='s')++x;
        else if(s[i]=='a')--y;
        else ++y;
        if(x<minx)minx=x;
        if(maxx<x)maxx=x;
        if(y<miny)miny=y;
        if(maxy<y)maxy=y;
    }
    x=-minx,y=-miny;b[x][y]=1;
    for(int i=0;s[i];++i)
    {
        if(s[i]=='w')--x;
        else if(s[i]=='s')++x;
        else if(s[i]=='a')--y;
        else ++y;
        b[x][y]=1;
    }
    sx=maxx-minx+1;sy=maxy-miny+1;
    for(int i=0;i<sx;++i)
    {
    	range[i][0]=1<<30,range[i][1]=-1<<30;
    	for(int j=0;j<sy;++j)
    		if(b[i][j])
    		{
    			if(j<range[i][0])range[i][0]=j;
    			range[i][1]=j;
    		}
    }
}
bool check(int px,int py)
{

}
int main(){
    scanf("%d%d%*d\n",&n,&m);
    for(int i=1;i<=n;++i)
    {
        gets(a[i]+1);
        for(int j=1;a[i][j];++j)a[i][j]-='0';
    }
    process();
    int ans=0;
    for(int i=1;i<=n-sx+1;++i)
        for(int j=1;j<=m-sy+1;++j)
            if(check(i,j))
                ++ans;
    printf("%d\n",ans);
}
