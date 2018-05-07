#include <bits/stdc++.h>
#define N 200010
char B[1<<23],*S=B;int F(){for(;*S<'-';++S);int b=*S=='-'?S++,1:0,x;for(x=*S++-'0';*S>='0';x=(x<<3)+(x<<1)+*S++-'0');return b?-x:x;}
int n,m,q,c[N],v[N],f[64],w[64];
int main(){
    fread(B,1,1<<23,stdin),n=F(),m=F();
    for(int i=1;i<=n;++i)c[i]=F();
    for(int i=1;i<=n;++i)v[i]=F();
    for(int q=F(),op,r,x;q--;){
        if((op=F())==1)
            for(int i=F(),r=F(),x=F();i<=r;++i)
                (c[i]+=x)>m?c[i]-=m:1;
        else if(op==2)
            for(int i=F(),r=F(),x=F();i<=r;++i)v[i]+=x;
        else{
            memset(f,0,sizeof f),memset(w,0,sizeof w);
            for(int i=F(),r=F();i<=r;++i)v[i]>w[c[i]]?w[c[i]]=v[i]:1;
            for(int i=1;i<=m;++i)
                for(int j=i;j<=m;++j)
                    f[j]<f[j-i]+w[i]?f[j]=f[j-i]+w[i]:1;
            long long ans1=0;int ans2=0;
            for(int i=1;i<=m;++i)ans1+=f[i],ans2^=f[i];
            printf("%lld %d\n",ans1,ans2);
        }
    }
}
