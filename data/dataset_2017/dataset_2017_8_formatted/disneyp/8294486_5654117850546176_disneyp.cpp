#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
int n;
string s;
int a[100];
string ttt[3];
int R, RY, Y, YB, B, BR;
string ans;
string build() {
  for (int i = 0; i < 3; i++) {
    for (int j = i; j < 3; j++) {
      if (a[i] < a[j]) {
        swap(a[i], a[j]);
        swap(ttt[i], ttt[j]);
      }
    }
  }

  // a[0] = max
  // a[0] <= a[1] + a[2]
  string fst = ttt[0] + ttt[1];
  string snd = ttt[0] + ttt[1] + ttt[2];
  string thr = ttt[0] + ttt[2];
  // cout << fst << " " << snd << " " << thr << endl;
  string ret = "";
  for (int i = 0; i < a[0] - a[2]; i++) {
    ret.append(fst);
  }
  for (int i = 0; i < a[1] + a[2] - a[0]; i++) {
    ret.append(snd);
  }
  for (int i = 0; i < a[0] - a[1]; i++) {
    ret.append(thr);
  }
  // cout << "ret" << ret << endl;
  return ret;
}

int main() {
  freopen("B.in", "r", stdin);
  freopen("B.txt", "w", stdout);
  // ttt[0] = "R";
  // ttt[1] = "Y";
  // ttt[2] = "B";
  int tt;
  cin >> tt;
  for (int aa = 0; aa < tt; aa++) {
    ttt[0] = "R";
    ttt[1] = "Y";
    ttt[2] = "B";
    cin >> n;
    cin >> R >> RY >> Y >> YB >> B >> BR;

    if (RY > B || YB > R || BR > Y) {
      cout << "Case #" << aa + 1 << ": "
           << "IMPOSSIBLE" << endl;
      continue;
    }
    int rr = R - YB;
    int yy = Y - BR;
    int bb = B - RY;
    if (rr > yy + bb || yy > bb + rr || bb > rr + yy) {
      cout << "Case #" << aa + 1 << ": "
           << "IMPOSSIBLE" << endl;
      continue;
    }

    a[0] = rr;
    a[1] = yy;
    a[2] = bb;

    // cout << endl;
    // cout << a[0] << " " << a[1] << " " << a[2]  << endl;
    s = build();
    // cout << s << endl;

    ans.clear();
    string tmp;
    rr = YB;
    yy = BR;
    bb = RY;
    int k = s.size();
    for (int i = 0; i < k; i++) {
      tmp = s[i];
      ans.append(tmp);
      if (s[i] == 'R') {
        if (rr > 0) {
          tmp = "GR";
          ans.append(tmp);
          rr--;
        }
      } else if (s[i] == 'Y') {
        if (yy > 0) {
          tmp = "VY";
          ans.append(tmp);
          yy--;
        }

      } else if (s[i] == 'B') {
        if (bb > 0) {
          tmp = "OB";
          ans.append(tmp);
          bb--;
        }
      }
    }

    while (rr > 0) {
      ans.append("GR");
      rr--;
    }

    while (yy > 0) {
      ans.append("VY");
      yy--;
    }

    while (bb > 0) {
      ans.append("OB");
      bb--;
    }

    cout << "Case #" << aa + 1 << ": " << ans << endl;
  }

  return 0;
}