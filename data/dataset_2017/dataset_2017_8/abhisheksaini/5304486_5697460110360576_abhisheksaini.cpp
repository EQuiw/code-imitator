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
string S[lim];
lld A[lim],B[lim],Quan[1003][1003];
double C[lim];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;

bool valid(lld n){
    lld t,low,high,mid;
    double curr,val,l=0.9-EPS,h=1.10+EPS;
    low = 1;
    high = Quan[1][B[1]];
    // rep(i,1,n) Error3(i,B[i],Quan[i][B[i]]);
    while(low<=high){
        mid = low+(high - low)/2;
        t = 1;
        rep(i,1,n){
            val = A[i]*mid;
            curr = Quan[i][B[i]]/val;
            // if(mid==1) Error4(A[i],B[i],val,curr);
            if(curr<l) t = 2;
            if(curr>h) t = 3;
        }
        // Error2(mid,t);
        if(t==1) return true;
        if(t==3) low = mid+1;
        if(t==2) high = mid-1;
    }
    return false;
}


int main(){
    lld T,i,n,m,p,j,l,e,r,b,c,k,q,a,d,w,x,y,v,z,t,curr,prev,sum,ans,pos,val,countA,secondMin,indicator;
    sc(T);
    rep(testC,1,T){
        printf("Case #%lld: ",testC);
        sc2(n,p);
        rep(i,1,n) sc(A[i]);
        ans = 0;
        rep(i,1,n) B[i] = 1;
        rep(i,1,n) rep(j,1,p) sc(Quan[i][j]);
        rep(i,1,n) sort(Quan[i]+1,Quan[i]+p+1);
        while(true){
            if(valid(n)){
                ans++;
                rep(i,1,n) B[i]++;
            }
            else{
                rep(i,1,n) C[i] = Quan[i][B[i]]*1.0/A[i];
                x = 1;
                rep(i,2,n) if(C[i]<C[x]) x = i;
                B[x]++;
            }
            t = 0;
            rep(i,1,n) t += (B[i]>p);
            if(t>0) break;
        }
        prL(ans);
    }
    return 0;
}