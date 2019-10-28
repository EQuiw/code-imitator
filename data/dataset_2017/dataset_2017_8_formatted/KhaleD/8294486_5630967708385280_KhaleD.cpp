#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lp(i, a, n) for (int i = (a); i <= (int)(n); ++i)
#define lpd(i, a, n) for (int i = (a); i >= (int)(n); --i)
#define mem(a, b) memset(a, b, sizeof a)
#define all(v) v.begin(), v.end()
#define println(a) cout << (a) << endl
#define sz(x) ((int)(x).size())
#define readi(x) scanf("%d", &x)
#define read2i(x, y) scanf("%d%d", &x, &y)
#define read3i(x, y, z) scanf("%d%d%d", &x, &y, &z)
#define readll(x) scanf("%I64d", &x)
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
typedef map<int, int> mii;

const int N = 100002;
int t, d, n, pos[N], speed[N];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  readi(t);
  lp(test, 1, t) {
    read2i(d, n);
    lp(i, 1, n) read2i(pos[i], speed[i]);

    double maxT = 0;
    lp(i, 1, n) maxT = max(maxT, 1.0 * (d - pos[i]) / speed[i]);

    printf("Case #%d: %.6f\n", test, d / maxT);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
