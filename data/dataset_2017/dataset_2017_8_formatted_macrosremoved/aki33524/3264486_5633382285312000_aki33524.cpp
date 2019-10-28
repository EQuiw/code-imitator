#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
string S;

void solve() {
  cin >> S;
  int L = S.size();

  int x = -1;
  for (int i = 0; i < L - 1; i++) {
    if (S[i] > S[i + 1]) {
      x = i;
      break;
    }
  }
  if (x == -1) {
    cout << S << endl;
    return;
  }
  int y = 0;
  for (int i = 1; i <= x; i++) {
    if (S[i - 1] < S[i])
      y = i;
  }
  if (y == 0 && S[y] == '1') {
    for (int i = 0; i < L - 1; i++)
      cout << 9;
    cout << endl;
    return;
  }

  cout << S.substr(0, y);
  cout << char(S[y] - 1);
  for (int i = y + 1; i < L; i++)
    cout << 9;
  cout << endl;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    cout << "Case #" << t + 1 << ": ";
    solve();
  }
  return 0;
}
