#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lp(i,a,n) for(int i=(a);i<=(int)(n);++i)
#define lpd(i,a,n) for(int i=(a);i>=(int)(n);--i)
#define mem(a,b) memset(a,b,sizeof a)
#define all(v) v.begin(),v.end()
#define println(a) cout <<(a) <<endl
#define sz(x) ((int)(x).size())
#define readi(x) scanf("%d",&x)
#define read2i(x,y) scanf("%d%d",&x,&y)
#define read3i(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define readll(x) scanf("%I64d",&x)
#define mod 1000000007
#define eps 1e-6
#define infi 1000000000
#define infll 1000000000000000000ll
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef set<int> si;
typedef map<int,int> mii;

const int N = 50;
int t,n,m;
char a[N][N];

int main() {
    freopen("A-small-attempt0.in","r",stdin);
    freopen("output.txt","w",stdout);

    readi(t);
    lp(test,1,t){
        read2i(n,m);
        lp(i,0,n-1) scanf("%s",a[i]);

        lp(i,0,n-1){
            lp(j,1,m-1) if(a[i][j] == '?') a[i][j] = a[i][j-1];
            lpd(j,m-2,0) if(a[i][j] == '?') a[i][j] = a[i][j+1];
        }
        lp(j,0,m-1){
            lp(i,1,n-1) if(a[i][j] == '?') a[i][j] = a[i-1][j];
            lpd(i,n-2,0) if(a[i][j] == '?') a[i][j] = a[i+1][j];
        }

        printf("Case #%d:\n",test);
        lp(i,0,n-1){
            lp(j,0,m-1) printf("%c",a[i][j]);
            puts("");
        }
    }
}

//freopen("input.txt","r",stdin);
//freopen("output.txt","w",stdout);
//ios::sync_with_stdio(0);cin.tie(0);
