#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#define REP(i,n) for( (i)=0 ; (i)<(n) ; (i)++ )
#define rep(i,x,n) for( (i)=(x) ; (i)<(n) ; (i)++ )
#define REV(i,n) for( (i)=(n) ; (i)>=0 ; (i)-- )
#define FORIT(it,x) for( (it)=(x).begin() ; (it)!=(x).end() ; (it)++ )
#define foreach(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
#define rforeach(it,c) for(__typeof((c).rbegin()) it=(c).rbegin();it!=(c).rend();++it)
#define foreach2d(i, j, v) foreach(i,v) foreach(j,*i)
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define SZ(x) ((int)(x).size())
#define MMS(x,n) memset(x,n,sizeof(x))
#define mms(x,n,s) memset(x,n,sizeof(x)*s)
#define pb push_back
#define mp make_pair
#define NX next_permutation
#define UN(x) sort(all(x)),x.erase(unique(all(x)),x.end())
#define CV(x,n) count(all(x),(n))
#define FIND(x,n) find(all(x),(n))-(x).begin()
#define ACC(x) accumulate(all(x),0)
#define PPC(x) __builtin_popcount(x)
#define LZ(x) __builtin_clz(x)
#define TZ(x) __builtin_ctz(x)
#define mxe(x) *max_element(all(x))
#define mne(x) *min_element(all(x))
#define low(x,i) lower_bound(all(x),i)
#define upp(x,i) upper_bound(all(x),i)
#define NXPOW2(x) (1ll << ((int)log2(x)+1))
#define PR(x) cout << #x << " = " << (x) << endl ;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<ll, ll> pii;

const ll OO = 1LL << 60;
const double eps = 1e-9;

const int N = 101;

int n, q;
ll E[N], S[N];
ll a[N][N];
int st, en;
double timeHorse[N][N];
ll cntHorse[N][N];

void dij(int src) {
	priority_queue<pair<pii, ll>, vector<pair<pii, ll>>, greater<pair<pii, ll>> > Q;
	Q.push(mp(mp(0LL, 0LL), src));
	timeHorse[src][src] = 0;
	while (Q.size()) {
		ll cur = Q.top().second;
		ll cnt_till_now = Q.top().first.second;
		ll dist_till_now = Q.top().first.first;
		double total_time_now = double(dist_till_now) / S[src];
		Q.pop();
		if (fabs(total_time_now - timeHorse[src][cur]) > eps)
			continue;
		for (ll i = 0; i < n; i++) {
			if (i == src || a[cur][i] == -1)
				continue;
			ll new_dist = dist_till_now + a[cur][i];
			if (new_dist > E[src])
				continue;
			double new_time = double(new_dist) / S[src];
			if (timeHorse[src][i] > new_time) {
				timeHorse[src][i] = new_time;
				cntHorse[src][i] = cnt_till_now + 1;
				Q.push(mp(mp(new_dist, cnt_till_now + 1), i));
			}
		}
	}
}

double dp[N][N];
int vis[N][N];
int vid;

double calc(int cnt, int cur) {
	if (cur == en)
		return 0;
	double &ret = dp[cnt][cur];
	if (vis[cnt][cur] == vid)
		return ret;
	vis[cnt][cur] = vid;
	ret = OO;
	for (int i = 0; i < n; i++) {
		if (cnt + cntHorse[cur][i] <= n) {
			ret = min(ret, timeHorse[cur][i] + calc(cnt + cntHorse[cur][i], i));
		}
	}
	return ret;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
//#ifndef ONLINE_JUDGE
	freopen("C-small-attempt1.in", "rt", stdin);
	freopen("out.txt", "wt", stdout);
//#endif
	int t, tt = 1;
	cin >> t;
	while (t--) {
		cin >> n >> q;
		for (int i = 0; i < n; i++)
			cin >> E[i] >> S[i];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
				timeHorse[i][j] = OO;
				cntHorse[i][j] = OO;
			}
		}
		for (int i = 0; i < n; i++)
			dij(i);
		cout << "Case #" << tt++ << ":";
		cout << fixed << setprecision(6);
		for (int i = 0; i < q; i++) {
			cin >> st >> en;
			st--, en--;
			vid++;
			double res = calc(0, st);
			cout << " " << res;
		}
		cout << "\n";
	}
	return 0;
}
