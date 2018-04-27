#include <bits/stdc++.h>
#define N 520
char a[N][N],s[500010],b[N][N];
int n,m,sx,sy,range[N][2],lista[N][N],suma[N][N],listb[N][N],cntb[N];
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
    sx=maxx-minx+1,sy=maxy-miny+1;
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
    for(int i=0;i<sx;++i)
        for(int j=0;j<sy;++j)
            if(b[i][j])
            {
                // printf("work %d %d\n",i,j);
                for(int k=j-1;k>=0&&listb[i][k]==0;--k)
                    listb[i][k]=j;
            }
    return;
    for(int i=0;i<sx;++i,puts(""))
        for(int j=0;j<sy;++j)
            printf("%d",b[i][j]);
}
bool check(int px,int py)
{
    // printf("check %d %d\n",px,py);
    for(int i=0;i<sx;++i)
    {
        int k,j=range[i][0];
        if(b[i][j]&&a[px+i][py+j])
            return 0;
        if(suma[i+px][py+range[i][1]]-suma[i+px][py+range[i][0]-1]<=cntb[i])
            for(;j<=range[i][1];)
            {
                k=lista[px+i][py+j];
                j=k-py;
                if(k==0||j>range[i][1])break;
                if(b[i][j])return 0;
                    // return!printf("err %d %d\n",px+i,py+j);
            }
        else
            for(;j<=range[i][1];)
            {
                j=listb[i][j];
                if(j==0||j>range[i][1])break;
                if(a[i+px][j+py])return 0;
            }
    }
    return 1;
}
int main(){
    scanf("%d%d%*d\n",&n,&m);
    for(int i=1;i<=n;++i)
    {
        a[i][0]=1;lista[i][0]=1;
        gets(a[i]+1);
        for(int j=1;a[i][j];++j)
        {
            a[i][j]-='0';
            suma[i][j]=suma[i][j-1]+a[i][j];
            if(a[i][j])
            {
                // printf("work %d %d\n",i,j);
                for(int k=j-1;k>0&&lista[i][k]==0;--k)
                    lista[i][k]=j;
            }
        }
    }
    // for(int i=1;i<=n;++i,puts(""))
    //     for(int j=1;j<=m;++j)
    //         printf("%d ",lista[i][j]);
    process();
    int ans=0;
    for(int i=1;i<=n-sx+1;++i)
        for(int j=1;j<=m-sy+1;++j)
            if(check(i,j))
                ++ans;
    printf("%d\n",ans);
}
