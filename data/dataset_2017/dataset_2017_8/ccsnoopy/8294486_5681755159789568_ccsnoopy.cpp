#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef pair<ii, int> iii;

#ifdef DEBUG
    #define cek(x) cout<<x
#else
    #define cek(x) if(false){}
#endif // DEBUG

#define fi first
#define se second
#define INF 1000000000
#define INFLL 1000000000000000000LL
#define EPS 1e-9
#define PI acos(-1.0)
#define pb push_back
#define TC() while(tc--)
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORN(i,n) for(int i=0;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define REPN(i,a,b) for(int i=a;i<=b;i++)
#define reset(a,b) memset(a,b,sizeof(a))
#define ALL(v) v.begin(), v.end()
#define SORT(v) sort(ALL(v))
#define SORTA(v,n) sort(v, v + n)
#define SZ(v) (int) v.size()
#define sc(x) scanf("%d",&x)

void open(){
	freopen("D:/OneDrive/Code/GCJ/C-small-attempt1 (1).in","r",stdin);
	freopen("D:/OneDrive/Code/GCJ/out22.txt", "w", stdout);
}
int n,q,fr,to;
int energy[120];
int spd[120];
int dist[120][120];
map<iii, double> memo;

double dp(int idx, int pony, int left){
	iii z = make_pair(ii(idx, pony), left);
	if(idx == to)return 0;
	if(memo.find(z) != memo.end() && memo[z] < 1e12)return memo[z];

	double ans = 1e12;

	if(dist[idx][idx + 1] <= left){
		ans = min(dp(idx + 1, pony, left - dist[idx][idx + 1]) + 1.0 * dist[idx][idx + 1] / spd[pony], ans);
	}

	if(dist[idx][idx + 1] <= energy[idx]){
		ans = min(ans, dp(idx + 1, idx, energy[idx] - dist[idx][idx + 1]) + 1.0 * dist[idx][idx + 1]/spd[idx]);
	}
	return memo[z] = ans;
}

int main(void){
	open();
	int tc;
	sc(tc);

	for(int ct = 1; ct <= tc; ct++){
		sc(n);
		sc(q);
		
		FOR(i,n){
			sc(energy[i]);
			sc(spd[i]);
		}
		
		FOR(i,n){
			FOR(j,n){
				sc(dist[i][j]);
			}
		}

		sc(fr);sc(to);
		fr--;
		to--;
		memo.clear();

		printf("Case #%d: %.10lf\n", ct, dp(0,0,energy[0]));

		cerr << "Test " << ct << " done \n";
	}
    return 0;
}


