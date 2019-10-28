#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, char> P2;
template <class A, class B> inline bool mina(A &first, B second) {
  return (first > second) ? (first = second, 1) : 0;
}
template <class A, class B> inline bool maxa(A &first, B second) {
  return (first < second) ? (first = second, 1) : 0;
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
      for (int(i) = 0; (i) < (B); ++(i)) {
        cout << "BO";
      }
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << endl;
    return;
  }
  if (R == G && R) {
    if (R + G == N) {
      for (int(i) = 0; (i) < (R); ++(i)) {
        cout << "RG";
      }
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << endl;
    return;
  }
  if (Y == V && Y) {
    if (Y + V == N) {
      for (int(i) = 0; (i) < (Y); ++(i)) {
        cout << "YV";
      }
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
  if (in[2].first > in[0].first + in[1].first) {
    printf("IMPOSSIBLE\n");
    return;
  }
  string ans = "";
  for (int(i) = 0; (i) < (in[2].first); ++(i)) {
    ans += in[2].second;
    if (in[1].first) {
      ans += in[1].second;
      in[1].first--;
    } else {
      ans += in[0].second;
      in[0].first--;
    }
  }
  // cout << ans << endl;
  string ans2 = "";
  while (in[0].first) {
    ans2 += ans.substr(0, 2);
    ans2 += in[0].second;
    in[0].first--;
    ans = ans.substr(2);
  }
  ans2 += ans;
  for (int(i) = 0; (i) < (((int)(ans2).size())); ++(i)) {
    if (O && ans2[i] == 'B') {
      for (int(j) = 0; (j) < (O); ++(j)) {
        printf("BO");
      }
      O = 0;
    } else if (G && ans2[i] == 'R') {
      for (int(j) = 0; (j) < (G); ++(j)) {
        printf("RG");
      }
      G = 0;
    } else if (V && ans2[i] == 'Y') {
      for (int(j) = 0; (j) < (V); ++(j)) {
        printf("YV");
      }
      V = 0;
    }
    printf("%c", ans2[i]);
  }
  cout << endl;
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
