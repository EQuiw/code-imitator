#include<cstdio>
#include<map>
using namespace std;
typedef long long lld;

lld solve(lld n, lld m)
{
    map<lld, lld> M;
    
    for(M[n]=1; !M.empty(); M.erase(--M.end()))
    {
        lld c=M.rbegin()->second;
        lld d=M.rbegin()->first-1;
        m-=c;
        
        if( m<=0 )
            return d;
        
        if( d>1 )
            M[d>>1]+=c;
        
        if( c>0 )
            M[d-(d>>1)]+=c;
    }
    
    return -1;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        lld n, k;
        scanf("%lld%lld", &n, &k);
        lld ans=solve(n, k);
        printf("Case #%d: %lld %lld\n", cases, ans-(ans>>1), ans>>1);
    }
}
