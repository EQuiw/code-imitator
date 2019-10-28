#include <bits/stdc++.h>

using namespace std;

#define SZ(x) ((int)(x).size())
#define PB(x) push_back(x)
#define MEMSET(x, v) memset(x, v, sizeof(x))
#define REP(i, n) for (int(i) = 0; (i) < (n); ++(i))
#define x first
#define y second
#define INF (0x3f3f3f3f)

typedef long long LL;
typedef pair<int, char> P2;
template <class A, class B> inline bool mina(A &x, B y) {
  return (x > y) ? (x = y, 1) : 0;
}
template <class A, class B> inline bool maxa(A &x, B y) {
  return (x < y) ? (x = y, 1) : 0;
}

int N, R, O, Y, G, B, V;
int B2, R2, Y2;

void solve() {
  cin >> N >> R >> O >> Y >> G >> B >> V;
  if (B < O || R < G || Y < V) {
    printf("IMPOSSIBLE\n");
    return;
  }
  if (B == O && B) {
    if (B + O == N) {
      REP(i, B) { cout << "BO"; }
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << endl;
    return;
  }
  if (R == G && R) {
    if (R + G == N) {
      REP(i, R) { cout << "RG"; }
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << endl;
    return;
  }
  if (Y == V && Y) {
    if (Y + V == N) {
      REP(i, Y) { cout << "YV"; }
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << endl;
    return;
  }
  B -= O;
  R -= G;
  Y -= V;
  P2 in[3];
  in[0] = P2(R, 'R');
  in[1] = P2(B, 'B');
  in[2] = P2(Y, 'Y');
  sort(in, in + 3);
  if (in[2].x > in[0].x + in[1].x) {
    printf("IMPOSSIBLE\n");
    return;
  }
  string ans = "";
  REP(i, in[2].x) {
    ans += in[2].y;
    if (in[1].x) {
      ans += in[1].y;
      in[1].x--;
    } else {
      ans += in[0].y;
      in[0].x--;
    }
  }
  // cout << ans << endl;
  string ans2 = "";
  while (in[0].x) {
    ans2 += ans.substr(0, 2);
    ans2 += in[0].y;
    in[0].x--;
    ans = ans.substr(2);
  }
  ans2 += ans;
  REP(i, SZ(ans2)) {
    if (O && ans2[i] == 'B') {
      REP(j, O) { printf("BO"); }
      O = 0;
    } else if (G && ans2[i] == 'R') {
      REP(j, G) { printf("RG"); }
      G = 0;
    } else if (V && ans2[i] == 'Y') {
      REP(j, V) { printf("YV"); }
      V = 0;
    }
    printf("%c", ans2[i]);
  }
  cout << endl;
}

int main() {
  int test;
  cin >> test;
  REP(tt, test) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}
