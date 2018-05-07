#include <bits/stdc++.h>
#define N 200010
int n,m,q,c[N],v[N],f[64],w[N];
int main()
{
    scanf("%d%d",&n,&m);
    assert(1<=n&&n<=200000);
    assert(1<=m&&m<=60);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",c+i);
        assert(1<=c[i]&&c[i]<=m);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",v+i);
        assert(1<=v[i]&&v[i]<=10000000);
    }
    scanf("%d",&q);
    assert(0<=q&&q<=30000);
    long long ans1,ans2;
    for(int op,l,r,x;q--;)
    {
        scanf("%d%d%d",&op,&l,&r);
        assert(l<=r);
        assert(1<=op&&op<=3);
        if(op==1||op==2)
            scanf("%d",&x);
        if(op==1)
        {
            assert(1<=x&&x<=m);
            for(int i=l;i<=r;++i)
            {
                c[i]+=x;
                if(c[i]>m)
                    c[i]-=m;
            }
        }
        else if(op==2)
        {
            assert(-1000<=x&&x<=1000);
            for(int i=l;i<=r;++i)
                v[i]+=x;
        }
        else
        {
            memset(f,0,sizeof(f));
            for(int i=l;i<=r;++i)
                for(int j=c[i];j<=m;++j)
                    f[j]=std::max(f[j],f[j-c[i]]+v[i]);
            // memset(w,0,sizeof(w));
            // for(int i=l;i<=r;++i)
            // {
            //     if(v[i]>w[i])
            //         w[i]=v[i];
            // }
            // for(int i=1;i<=m;++i)
            //     for(int j=i;j<=m;++j)
            //         f[j]=std::max(f[j],f[j-i]+w[i]);
            ans1=ans2=0;
            for(int i=1;i<=m;++i)
            {
                ans1+=f[i];
                ans2^=f[i];
            }
            printf("%lld %lld\n",ans1,ans2);
        }
    }
}
