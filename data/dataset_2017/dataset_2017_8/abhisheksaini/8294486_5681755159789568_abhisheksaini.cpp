#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;
long long mod=1e9+7;
long long INF=1e7;
double EPS = 1e-12;
typedef long long int lld;
double tick(){static clock_t oldt;clock_t newt=clock();double diff=1.0*(newt-oldt)/CLOCKS_PER_SEC;oldt = newt;return diff;}
#define rep(i,a,n) for(long long int i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(long long int i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sc(a) scanf("%lld",&a)
#define sc2(a,b) scanf("%lld%lld",&a,&b)
#define sc3(a,b,c) scanf("%lld%lld%lld",&a,&b,&c)
#define scd(a) scanf("%d",&a)
#define scd2(a,b) scanf("%d%d",&a,&b)
#define scd3(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define scf(a) scanf("%lf",&a)
#define scf2(a,b) scanf("%lf%lf",&a,&b)
#define scf3(a,b,c) scanf("%lf%lf%lf",&a,&b,&c)
#define prL(a) printf("%lld\n",a)
#define prS(a) printf("%lld ",a)
#define prdL(a) printf("%d\n",a)
#define prdS(a) printf("%d ",a)
#define all(c) c.begin(), c.end()
#define sz(a) ((int)a.size())
#define Error(x) cout<< #x << " = " << (x) <<endl;
#define Error2(a,b) cout<<"( "<<#a<<" , "<<#b<<" ) = ( "<<(a)<<" , "<<(b)<<" )\n";
#define Error3(a,b,c) cout<<"("<<#a<<" , "<<#b<<" , "<<#c<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<")\n";
#define Error4(a,b,c,d) cout<<"("<<#a<<" , "<<#b<<" , "<<#c<<" , "<<#d<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<" , "<<(d)<<")\n";
#define errop(a) cout<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define mset(a, v) memset(a, v, sizeof(a))
#define popcount __builtin_popcountll

typedef pair<lld,lld> PA;

lld powP(lld a,lld b){
    if(b==0) return 1%mod;
    lld k;
    k=powP(a,b/2);
    k=k*k%mod;
    if(b%2==0) return k;
    else return a*k%mod;
}

bool bitSet(lld n,lld i){
    if((n&(1LL<<i))!=0) return true;
    else return false;
}

lld findGcd(lld a,lld b){
    if(a==0) return b;
    else return findGcd(b%a,a);
}

#define lim 700005
#define lim2 200003
#define qqqqqq 210
// inline lld sqr(lld x) { return x * x; }
// unordered_map<lld,lld>::iterator it;
// std::ios::sync_with_stdio(false);
// priority_queue<PA> Q;
// lld dp[1<<18];
// vector<lld> V[lim];
// string S[lim];
double A[lim],B[lim],C[lim],E[lim],S[lim];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;
double Dis[103][103],dp[103][103],Query[lim],From[103][103];

int main(){
    lld T,i,n,m,p,j,l,e,r,b,c,k,q,a,d,w,x,y,u,v,z,t,curr,prev,sum,ans,pos,val,countA,secondMin,indicator;
    sc(T);
    rep(testC,1,T){
        printf("Case #%lld: ",testC);
        sc2(n,q);
        rep(i,1,n) scf2(E[i],S[i]);
        rep(i,1,n){
            rep(j,1,n){
                scf(Dis[i][j]);
                if(Dis[i][j]==-1) Dis[i][j] = mod*1000000;
            }
            Dis[i][i] = 0;
        }
        rep(k,1,n) rep(i,1,n) rep(j,1,n) Dis[i][j] = min(Dis[i][j],Dis[i][k] + Dis[k][j]);
        while(q--){
            sc2(u,v);

        }
        rep(i,1,n) rep(j,i+1,n){
            double r = 0;
            rep(k,i,j-1) r += Dis[k][k+1];
            From[i][j] = r;
        }
        // if(testC!=57) continue;
        // rep(i,1,n) rep(j,i+1,n) if(Dis[i][j]!=From[i][j]){
        //     Error3(i,j,"fuck");
        //     Error2(Dis[i][j],From[i][j]);
        // }
        Query[n] = 0;
        repD(i,n-1,1){
            Query[i] = mod*1000000;
            rep(j,i+1,n) if(E[i]>=From[i][j]) Query[i] = min(Query[i],From[i][j]/S[i] + Query[j]);
        }
        printf("%lf\n",Query[1]);
    }
    return 0;
}