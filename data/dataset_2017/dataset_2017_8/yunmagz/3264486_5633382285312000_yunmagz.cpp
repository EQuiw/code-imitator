#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define zero(x) (((x)>0?(x):-(x))<eps)
typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int>PII;
const double eps=1e-8;
const double pi=acos(-1.0);
const int inf=0x3f3f3f3f;
const int INF=2e9+7;
const int mod=1e9+7;
LL powmod(LL a,LL b) {LL res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
int a[1010];
int main(){
    freopen("B-small-attempt1.in","r",stdin);
    freopen("output.txt","w",stdout);
    int t,k,cas=1;
    LL n,m;
    cin>>t;
    while(t--){
        cin>>n;
        printf("Case #%d: ",cas++);
        m=n;
        int cnt=0;
        while(n){
            a[cnt++]=n%10;
            n/=10;
        }
        int f=1;
        for(int i=1;i<cnt&&f;i++){
            if(a[i]>a[i-1]) f=0;
        }
        if(f){
            cout<<m<<endl;
            continue;
        }
        int j=cnt-1;
        for(int i=cnt-1;i>0;i--){
            if(a[i]<a[i-1]) j=i-1;
            if(a[i]>a[i-1]) break;
        }
        a[j]--;
        if(j==cnt-1&&a[j]==0){
            for(int i=1;i<cnt;i++) cout<<"9";
            puts("");
            continue;
        }
        for(int i=cnt-1;i>=j;i--) cout<<a[i];
        for(int i=j-1;i>=0;i--) cout<<"9";
        puts("");
    }
    return 0;
}
