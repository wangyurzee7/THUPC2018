#include <bits/stdc++.h>
#define N 1555
char a[N][N],s[5000010],b[N][N];
int n,m,K,sx,sy,range[N][2];
long long blocka[N][50],blockb[N][50];
#define xorr(a,i,j) (a[i][(j)>>6]^=1ll<<((j)&63))
//assert l/64==r/64
#define sel(a,i,l,r) ((a[i][(l)>>6]>>((l)&63))&((1ll<<((r)-(l)+1))-1))
void process(){
    gets(s);
    assert(K==strlen(s));
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
    sx=maxx-minx+1,sy=maxy-miny+1;
    for(int i=0;i<sx;++i)
    {
        range[i][0]=1<<30,range[i][1]=-1<<30;
        for(int j=0;j<sy;++j)
            if(b[i][j])
            {
                xorr(blockb,i,j);
                if(j<range[i][0])range[i][0]=j;
                range[i][1]=j;
            }
    }
    return;
    for(int i=0;i<sx;++i,puts(""))
        for(int j=0;j<sy;++j)
            printf("%d",b[i][j]);
}
template<class T>void print(T a)
{
    for(int i=1;i<=n;++i,puts(""))
        for(int j=0;j<=m+1;++j)
            printf("%d ",a[i][j]);
        puts("");
}
bool check(int px,int py)
{
    for(int i=0;i<sx;++i)
    {
        int k=py,ifs=64-(py&63),fc=((k>>6)+1)<<6;
        for(int j=0;j<=range[i][1]/64;++j,k+=64,fc+=64)
            if(blockb[i][j])
            {
                long long tmp=k&63?(sel(blocka,i+px,k,fc-1)|(sel(blocka,i+px,fc,k+63)<<ifs)):blocka[i+px][k>>6];
                if(tmp&blockb[i][j])return 0;
            }
    }
    return 1;
}
int main(){
    scanf("%d%d%d\n",&n,&m,&K);
    for(int i=1;i<=n;++i)
    {
        a[i][0]=1;
        xorr(blocka,i,0);
        gets(a[i]+1);
        for(int j=1;a[i][j];++j)
        {
            a[i][j]-='0';
            if(a[i][j])
                xorr(blocka,i,j);
        }
        xorr(blocka,i,m+1);
        a[i][m+1]=1;
    }
    process();
    int ans=0;
    for(int i=1;i<=n-sx+1;++i)
        for(int j=1;j<=m-sy+1;++j)
            if(check(i,j))
                ++ans;
    printf("%d\n",ans);
}
