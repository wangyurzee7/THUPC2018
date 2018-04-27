#include <bits/stdc++.h>
int a[2222][2222],b[40];
int main(int argc,char**argv)
{
    srand((unsigned long long)new char);
    int n=atoi(argv[1]),m=atoi(argv[2]),k=atoi(argv[3]),rate=atoi(argv[4]);
    for(int i=0;i<=n+1;++i)
        for(int j=0;j<=m+1;++j)
            a[i][j]=1;
    int len=rate;k=len*3;
    printf("%d %d %d\n",n,m,k);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            a[i][j]=(i%2<1)&&(j%2<1);
            // a[i][j]=rand()%100000<rate;
    for(int i=1;i<=n;++i,puts(""))
        for(int j=1;j<=m;++j)
            printf("%d",a[i][j]);
    for(int i=0;i<len;++i)putchar('s');
    for(int i=0;i<len;++i)putchar('d');
    for(int i=0;i<len;++i)putchar('w');
        return!puts("");
    int x,y;
    while(1)
    {
        x=rand()%n+1;
        y=rand()%m+1;
        if(a[x][y]==0&&!(a[x-1][y]&&a[x][y-1]&&a[x+1][y]&&a[x][y+1]))
            if(x<rate&&y<rate)
            break;
    }
    int minx=x,maxx=x,miny=y,maxy=y;
    for(int dir;k--;)
    {
        b[0]=a[x-1][y]==0;
        b[1]=a[x+1][y]==0&&x<rate;
        b[2]=a[x][y-1]==0;
        b[3]=a[x][y+1]==0&&y<rate;
        //cnt=b[0]+b[1]+b[2]+b[3];
        while(1)
        {
            dir=rand()&3;
            if(b[dir])break;
        }
        putchar("wsad"[dir]);
        if(dir<2)x+=dir==0?-1:1;
        else y+=dir==2?-1:1;
        if(x<minx)minx=x;
        if(maxx<x)maxx=x;
        if(y<miny)miny=y;
        if(maxy<y)maxy=y;
    }
    puts("");
    fprintf(stderr,"%d %d\n",maxx-minx+1,maxy-miny+1);
}
