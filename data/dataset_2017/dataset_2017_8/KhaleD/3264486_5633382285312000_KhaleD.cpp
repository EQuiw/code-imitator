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

const int N = 1002;
int t,digits;
ll n;
bool dp[N][12];
string ans,nString;

bool biggerThanN(string x){
    if(sz(x) < sz(nString)) return false;
    if(sz(x) > sz(nString)) return true;
    return x > nString;
}

string conv(ll x){
    stringstream ss;
    ss <<x;
    return ss.str();
}

void solve(int i, int p, string curr){
    if(biggerThanN(curr)){
        dp[i][p] = true;
        return;
    }
    if(i <= digits+1 and curr != ""){
        if(sz(curr) > sz(ans)) ans = curr;
        if(sz(curr) == sz(ans) and curr > ans) ans = curr;
    }
    if(i == digits+1) return;
    if(dp[i][p]) return;

    lp(j,p,9) solve(i+1, j, curr + char(j + '0'));
}

int main(){
    freopen("B-small-attempt0.in","r",stdin);
    freopen("output.txt","w",stdout);
    readi(t);
    lp(testCase,1,t){
        cin >>n;
        digits = (int)log10(n) + 1;
        nString = conv(n);

        ans = "";
        mem(dp,0);
        solve(1,1,"");
        printf("Case #%d: ",testCase);
        println(ans);
    }
}

//freopen("input.txt","r",stdin);
//freopen("output.txt","w",stdout);
//ios::sync_with_stdio(0);cin.tie(0);
