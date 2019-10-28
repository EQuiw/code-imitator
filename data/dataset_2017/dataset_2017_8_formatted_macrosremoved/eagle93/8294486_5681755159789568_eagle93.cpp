#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
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
  priority_queue<pair<pii, ll>, vector<pair<pii, ll>>, greater<pair<pii, ll>>>
      Q;
  Q.push(make_pair(make_pair(0LL, 0LL), src));
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
        Q.push(make_pair(make_pair(new_dist, cnt_till_now + 1), i));
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
