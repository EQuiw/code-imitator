#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, int> P2;
template <class A, class B> inline bool mina(A &first, B second) {
  return (first > second) ? (first = second, 1) : 0;
}
template <class A, class B> inline bool maxa(A &first, B second) {
  return (first < second) ? (first = second, 1) : 0;
}

const int MAXN = 55;
const int MAXP = 55;
int N, P;
int in[MAXN];
int gram[MAXN][MAXP];
int cur[MAXN];

void solve() {

  cin >> N >> P;
  for (int(i) = 0; (i) < (N); ++(i))
    cin >> in[i];
  for (int(i) = 0; (i) < (N); ++(i)) {
    for (int(j) = 0; (j) < (P); ++(j)) {
      cin >> gram[i][j];
    }
  }
  for (int(i) = 0; (i) < (N); ++(i)) {
    sort(gram[i], gram[i] + P);
  }
  memset(cur, 0, sizeof(cur));
  int ans = 0;

  int maxx = in[0];
  for (int(i) = 0; (i) < (N); ++(i)) {
    maxx = max(maxx, in[i]);
  }
  for (int servings = 1; servings <= 2000000 / maxx; servings++) {
    for (int(i) = 0; (i) < (N); ++(i)) {
      while (cur[i] < P && gram[i][cur[i]] * 100 < 90 * in[i] * servings)
        cur[i]++;
    }
    bool good = true;
    for (int(i) = 0; (i) < (N); ++(i)) {
      if (cur[i] >= P) {
        good = false;
        break;
      }
    }
    if (!good)
      break;
    bool succ = true;
    for (int(i) = 0; (i) < (N); ++(i)) {
      if (gram[i][cur[i]] * 100 > 110 * in[i] * servings) {
        succ = false;
        break;
      }
    }
    if (succ) {
      ans++;
      for (int(i) = 0; (i) < (N); ++(i))
        cur[i]++;
      servings--;
    }
  }
  cout << ans << endl;
}

int main() {
  int test;
  cin >> test;
  for (int(tt) = 0; (tt) < (test); ++(tt)) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}
