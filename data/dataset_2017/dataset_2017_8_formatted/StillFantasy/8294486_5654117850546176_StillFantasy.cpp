#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
#define INF 0x3f3f3f3f
#define INF16 16000000000000000LL
#define INF18 1000000000000000000LL
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define mod9 (int)(1e7 + 9)
#define mod7 (int)(1e7 + 7)
#define eps 1e-9
#define mse(x, y) memset(x, y, sizeof(x))
#define ALL(x) x.begin(), x.end()
#define RALL(x) x.rbegin(), x.rend()
#define IOS                                                                    \
  do {                                                                         \
    ios::sync_with_stdio(0);                                                   \
    cin.tie(0);                                                                \
  } while (0)
typedef pair<int, int> pii;
typedef long long ll;

template <typename Iter> ostream &_out(ostream &s, Iter a, Iter b) {
  for (auto it = a; it != b; it++)
    s << (it == a ? "" : " ") << *it;
  return s;
}

template <typename A, typename B>
ostream &operator<<(ostream &s, pair<A, B> &p) {
  return s << "(" << p.F << " , " << p.S << ")";
}
template <typename T> ostream &operator<<(ostream &s, vector<T> &v) {
  return _out(s, ALL(v));
}

inline ll rit() {
  int key = 1;
  char c = getchar();
  while (!isdigit(c)) {
    if (c == '-')
      key = -1;
    c = getchar();
  }

  ll x = 0;
  while (isdigit(c)) {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * key;
}

int __ = 1;

/*********default*********/

void init() {}

void read() {}

void solve() {}

char box[1010];
pair<int, char> a[10];

bool cmp(pair<int, char> a, pair<int, char> b) { return a.first > b.first; }

int main() {
  int test, kase = 0;
  scanf("%d", &test);
  while (test--) {
    int n = 0;
    cin >> n;
    for (int i = 0; i < 6; i++)
      a[i].first = rit();
    a[0].second = 'R';
    a[2].second = 'Y';
    a[4].second = 'B';
    sort(a, a + 6, cmp);

    int Max = a[0].first;
    for (int i = 1; i < 6; i++)
      Max = max(Max, a[i].first);

    if (Max > n / 2) {
      printf("Case #%d: IMPOSSIBLE\n", ++kase);
      continue;
    }

    for (int i = 0; i < n; i += 2) {
      if (a[0].first) {
        box[i] = a[0].second;
        a[0].first--;
      } else if (a[1].first) {
        box[i] = a[1].second;
        a[1].first--;
      } else {
        box[i] = a[2].second;
        a[2].first--;
      }
    }

    for (int i = 1; i < n; i += 2) {
      if (a[0].first) {
        box[i] = a[0].second;
        a[0].first--;
      } else if (a[1].first) {
        box[i] = a[1].second;
        a[1].first--;
      } else {
        box[i] = a[2].second;
        a[2].first--;
      }
    }

    printf("Case #%d: ", ++kase);
    for (int i = 0; i < n; i++)
      printf("%c", box[i]);
    puts("");
  }
  return 0;
}
