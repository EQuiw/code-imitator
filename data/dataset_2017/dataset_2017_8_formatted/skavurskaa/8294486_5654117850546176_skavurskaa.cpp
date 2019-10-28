#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cout << "Case #" << t << ": ";
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    if (R + Y == 0 || R + B == 0 || Y + B == 0)
      cout << "IMPOSSIBLE";
    else if (R == 0)
      if (Y == B)
        for (int i = 0; i < Y; i++)
          cout << "YB";
      else
        cout << "IMPOSSIBLE";
    else if (Y == 0)
      if (R == B)
        for (int i = 0; i < R; i++)
          cout << "RB";
      else
        cout << "IMPOSSIBLE";
    else if (B == 0)
      if (R == Y)
        for (int i = 0; i < R; i++)
          cout << "RY";
      else
        cout << "IMPOSSIBLE";
    else {
      int mx = max(R, max(Y, B));
      int mn = min(R, min(Y, B));
      int md = N - mx - mn;
      if (mx > N / 2)
        cout << "IMPOSSIBLE";
      else {
        vector<pair<int, char>> vt(3);
        vt[0] = {R, 'R'};
        vt[1] = {Y, 'Y'};
        vt[2] = {B, 'B'};
        sort(vt.begin(), vt.end());
        char cmx, cmn, cmd;
        cmx = vt[2].second;
        cmd = vt[1].second;
        cmn = vt[0].second;
        string S(N, '*');
        for (int i = 0; i < mx * 2; i += 2)
          S[i] = cmx;
        for (int i = mx * 2; i < N; i += 2) {
          S[i] = cmd;
          md--;
        }
        for (int i = 1; i < N && md; i += 2) {
          S[i] = cmd;
          md--;
        }
        for (int i = 0; i < N; i++)
          cout << (S[i] == '*' ? cmn : S[i]);
      }
    }
    cout << endl;
  }
}
