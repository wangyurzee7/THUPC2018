#include <bits/stdc++.h>
#define N 200010
char B[1<<23],*S=B;int F(){for(;*S<'-';++S);int b=*S=='-'?S++,1:0,x;for(x=*S++-'0';*S>='0';x=(x<<3)+(x<<1)+*S++-'0');return b?-x:x;}
int n,m,q,c[N],v[N],f[62],w[124],bc[N],bv[N];
#define K 9
int main(){
    fread(B,1,1<<23,stdin),n=F(),m=F();
    for(int i=1;i<=n;++i)c[i]=F();
    for(int i=1;i<=n;++i)v[i]=F();
    for(int q=F(),op,r,x;q--;){
        if((op=F())==1)
        {
            int l=F(),r=F(),x=F(),bl=l>>K,br=r>>K;
            for(int i=l;i<=r&&(i>>K)==bl;++i)
                c[i]+=x,c[i]>=m?c[i]-=m:1;
            if(bl!=br)
            {
                for(int i=r;i>=l&&(i>>K)==br;--i)
                    c[i]+=x,c[i]>=m?c[i]-=m:1;
                for(int i=bl+1;i<br;++i)
                    bc[i]+=x,bc[i]>=m?bc[i]-=m:1;
            }
            // for(int i=l;i<=r;++i)
            //     (c[i]+=x)>m?c[i]-=m:1;
        }
        else if(op==2)
        {
            int l=F(),r=F(),x=F(),bl=l>>K,br=r>>K;
            for(int i=l;i<=r&&(i>>K)==bl;++i)
                v[i]+=x;
            if(bl!=br)
            {
                for(int i=r;i>=l&&(i>>K)==br;--i)
                    v[i]+=x;
                for(int i=bl+1;i<br;++i)
                    bv[i]+=x;
            }
            // for(int i=F(),r=F(),x=F();i<=r;++i)v[i]+=x;
        }
        else{
            memset(f,0,sizeof f),memset(w,0,sizeof w);
            for(register int i=F(),r=F(),xc;i<=r;++i)
                xc=c[i]+bc[i>>K],v[i]+bv[i>>K]>w[xc]?w[xc]=v[i]+bv[i>>K]:1;
            for(int i=m;i<=m+m;++i)
                w[i%m]<w[i]?w[i%m]=w[i]:1;
            w[m]=w[0],w[0]=0;            
            for(int i=1;i<=m;++i)
                for(int j=i;j<=m;++j)
                    f[j]<f[j-i]+w[i]?f[j]=f[j-i]+w[i]:1;
            long long ans1=0;int ans2=0;
            for(int i=1;i<=m;++i)ans1+=f[i],ans2^=f[i];
            printf("%lld %d\n",ans1,ans2);
        }
    }
}