#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define zero(x) (((x)>0?(x):-(x))<eps)
typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int>PII;
typedef pair<double,int>PDI;
const double eps=1e-8;
const double pi=acos(-1.0);
const int inf=0x3f3f3f3f;
const int INF=2e9+7;
const int mod=1e9+7;
LL powmod(LL a,LL b) {LL res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
char g[30][30];
int v[30],n,m;
void solve(){
    memset(v,0,sizeof(v));
    for (int i=0;i<n;i++) {
        cin>>g[i];
        int j=0;
        while (j<m&&g[i][j]=='?') j++;
        if(j<m){
            for (int k=0;k<j;k++) g[i][k]=g[i][j];
            for (int k=j+1;k<m;k++){
                if (g[i][k]=='?') g[i][k]=g[i][k-1];
            }
        }
        else v[i]=1;
    }
    int j=0;
    while(v[j]) j++;
    for (int i=0;i<j;i++) strcpy(g[i],g[j]);
    for (int i=j+1;i<n;i++) {
        if(v[i]) strcpy(g[i],g[i-1]);
    }
}
int main(){
    freopen("A-small-attempt0.in","r",stdin);
    freopen("output.txt","w",stdout);
    int t,cas=1;
    cin>>t;
    while(t--){
        cin>>n>>m;
        solve();
        printf("Case #%d: \n",cas++);
        for(int i=0;i<n;i++) cout<<g[i]<<endl;
    }
    return 0;
}
