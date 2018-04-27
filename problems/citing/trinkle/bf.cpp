#include <bits/stdc++.h>
char a[2222][2222],s[5000010],b[2222][2222];
int n,m,sx,sy,K;
void process(){
    gets(s);
    assert(strlen(s)==K);
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
    return;
    for(int i=0;i<sx;++i,puts(""))
        for(int j=0;j<sy;++j)
            printf("%d",b[i][j]);
}
bool check(int px,int py)
{
    //printf("check %d %d\n",px,py);
    for(int i=0;i<sx;++i)
        for(int j=0;j<sy;++j)
            if(b[i][j]&&a[px+i][py+j])
                return 0;
//                return!printf("err %d %d\n",px+i,py+j);
    return 1;
}
int main(){
    scanf("%d%d%d\n",&n,&m,&K);
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
