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
int t, n, r, o, y, g, b, v;
char ans[N];

bool conflict(int i, int j) {
  if (ans[i] == ans[j])
    return true;
  if ((ans[i] == 'R' or ans[i] == 'B' or ans[i] == 'Y') and
      (ans[j] == 'R' or ans[j] == 'B' or ans[j] == 'Y'))
    return false;
  if (ans[i] == 'O' and ans[j] != 'B')
    return true;
  if (ans[i] == 'G' and ans[j] != 'R')
    return true;
  if (ans[i] == 'V' and ans[j] != 'Y')
    return true;
  swap(i, j);
  if (ans[i] == 'O' and ans[j] != 'B')
    return true;
  if (ans[i] == 'G' and ans[j] != 'R')
    return true;
  if (ans[i] == 'V' and ans[j] != 'Y')
    return true;
  return false;
}

bool check() {
  lp(i, 0, n - 1) if (conflict(i, (i + 1) % n)) return false;
  return true;
}

int main() {
  freopen("B-small-attempt2.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  readi(t);
  lp(test, 1, t) {
    scanf("%d%d%d%d%d%d%d", &n, &r, &o, &y, &g, &b, &v);
    ans[n] = '\0';
    printf("Case #%d: ", test);

    if (b >= o and r >= g and y >= v) {
      int i = 0;
      if (o) {
        ans[i++] = 'B';
        --b;
        while (o) {
          ans[i++] = 'O', --o;
          if (b)
            ans[i++] = 'B', --b;
        }
      }
      if (g) {
        ans[i++] = 'R';
        --r;
        while (g) {
          ans[i++] = 'G', --g;
          if (r)
            ans[i++] = 'R', --r;
        }
      }
      if (v) {
        ans[i++] = 'Y';
        --y;
        while (v) {
          ans[i++] = 'V', --v;
          if (y)
            ans[i++] = 'Y', --y;
        }
      }

      int rr = r, bb = b, yy = y;
      int j = i;
      // rby
      while (rr or bb or yy) {
        if (rr)
          ans[j++] = 'R', --rr;
        if (bb)
          ans[j++] = 'B', --bb;
        if (yy)
          ans[j++] = 'Y', --yy;
      }
      if (check()) {
        puts(ans);
        continue;
      }

      rr = r, bb = b, yy = y;
      j = i;
      // ryb
      while (rr or bb or yy) {
        if (rr)
          ans[j++] = 'R', --rr;
        if (yy)
          ans[j++] = 'Y', --yy;
        if (bb)
          ans[j++] = 'B', --bb;
      }
      if (check()) {
        puts(ans);
        continue;
      }

      rr = r, bb = b, yy = y;
      j = i;
      // ybr
      while (rr or bb or yy) {
        if (yy)
          ans[j++] = 'Y', --yy;
        if (bb)
          ans[j++] = 'B', --bb;
        if (rr)
          ans[j++] = 'R', --rr;
      }
      if (check()) {
        puts(ans);
        continue;
      }

      rr = r, bb = b, yy = y;
      j = i;
      // bry
      while (rr or bb or yy) {
        if (bb)
          ans[j++] = 'B', --bb;
        if (rr)
          ans[j++] = 'R', --rr;
        if (yy)
          ans[j++] = 'Y', --yy;
      }
      if (check()) {
        puts(ans);
        continue;
      }

      rr = r, bb = b, yy = y;
      j = i;
      // yrb
      while (rr or bb or yy) {
        if (yy)
          ans[j++] = 'Y', --yy;
        if (rr)
          ans[j++] = 'R', --rr;
        if (bb)
          ans[j++] = 'B', --bb;
      }
      if (check()) {
        puts(ans);
        continue;
      }

      rr = r, bb = b, yy = y;
      j = i;
      // byr
      while (rr or bb or yy) {
        if (bb)
          ans[j++] = 'B', --bb;
        if (yy)
          ans[j++] = 'Y', --yy;
        if (rr)
          ans[j++] = 'R', --rr;
      }
      if (check()) {
        puts(ans);
        continue;
      }
      puts("IMPOSSIBLE");
    } else
      printf("IMPOSSIBLE\n");
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
