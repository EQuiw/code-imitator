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

const int N = 1002;
int t, n, k;

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  readi(t);
  lp(testCase, 1, t) {
    read2i(n, k);

    priority_queue<int, vi> q;
    q.push(n);
    lp(i, 1, k - 1) {
      int x = q.top();
      q.pop();
      if (x / 2)
        q.push(x / 2);
      if (x / 2 - (x % 2 == 0))
        q.push(x / 2 - (x % 2 == 0));
    }

    int x = q.top();
    int y = max(x / 2, x / 2 - (x % 2 == 0)),
        z = min(x / 2, x / 2 - (x % 2 == 0));
    printf("Case #%d: %d %d\n", testCase, y, z);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
