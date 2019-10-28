#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
void solve() {
  int r, c;
  cin >> r >> c;
  vector<string> s(r);
  for (int(i) = 0; (i) < (int)(r); ++(i))
    cin >> s[i];

  // // 各行に何かしら文字があるか？
  // bool row=true;
  // rep(i,r)
  // {
  //     bool ok=false;
  //     rep(j,c)if(s[i][j]!='?') ok=true;
  //     row&=ok;
  // }
  //
  // // 各列に何かしら文字があるか？
  // bool column=true;
  // rep(i,c)
  // {
  //     bool ok=false;
  //     rep(j,r)if(s[j][i]!='?') ok=true;
  //     column&=ok;
  // }

  // 横に伸ばす
  for (int(i) = 0; (i) < (int)(r); ++(i))
    for (int(j) = 0; (j) < (int)(c); ++(j)) {
      if (s[i][j] != '?') {
        int L = j, R = j;
        while (L > 0 && s[i][L - 1] == '?')
          --L;
        while (R < c - 1 && s[i][R + 1] == '?')
          ++R;

        for (int k = L; k <= R; ++k)
          s[i][k] = s[i][j];
      }
    }

  for (int(i) = 0; (i) < (int)(r); ++(i)) {
    if (s[i][0] != '?') {
      int L = i, R = i;
      while (L > 0 && s[L - 1][0] == '?')
        --L;
      while (R < r - 1 && s[R + 1][0] == '?')
        ++R;

      for (int j = L; j <= R; ++j) {
        for (int(k) = 0; (k) < (int)(c); ++(k))
          s[j][k] = s[i][k];
      }
    }
  }
  for (int(i) = 0; (i) < (int)(r); ++(i))
    for (int(j) = 0; (j) < (int)(c); ++(j))
      assert(s[i][j] != '?');

  for (int(i) = 0; (i) < (int)(r); ++(i))
    cout << s[i] << endl;
}

int main() {
  int T;
  cin >> T;
  for (int(t) = 0; (t) < (int)(T); ++(t)) {
    printf("Case #%d:\n", t + 1);
    solve();
  }
  return 0;
}
