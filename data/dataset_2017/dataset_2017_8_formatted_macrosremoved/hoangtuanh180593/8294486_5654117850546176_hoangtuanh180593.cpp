#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void mf() {
  // freopen("input.in","r",stdin);

  freopen("Bsmall.in", "r", stdin);
  freopen("Bsmall.ou", "w", stdout);

  // freopen("Blarge.in","r",stdin);
  // freopen("Blarge.ou","w",stdout);
}
bool fr[6][6];
string color[6] = {"R", "O", "Y", "G", "B", "V"};
vector<int> ke[10];
// 0R 1O 2Y 3G 4B 5V 6R
struct data {
  int type;
  string s;
};
int n;
int a[10];
vector<data> ans[10];
void init() {
  memset(fr, true, sizeof fr);
  for (int i = 0; i < 6; i++)
    fr[i][i] = false;
  for (int i = 0; i < 6; i++) {
    int j = (i + 1) % 6;
    fr[i][j] = false;
    fr[j][i] = false;
  }
  fr[1][3] = fr[3][1] = false;
  fr[1][5] = fr[5][1] = false;
  fr[3][5] = fr[5][3] = false;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++)
      if (fr[i][j])
        ke[i].push_back(j);
  }
  // for(int i = 0;i<6;i++)
  // 	cout<<ke[i].size()<<endl;
}
int cc[10];
void solve() {
  cin >> n;
  for (int i = 0; i < 6; i++) {
    cin >> a[i];
  }
  ////////
  for (int i = 0; i < 6; i++) {
    int rr = 0, sz = ke[i].size();
    for (int j : ke[i])
      rr += a[j];

    if (a[i] > rr) {
      cout << "IMPOSSIBLE" << endl;
      return;
    }

    if (sz == 1 && a[i] == rr && a[i] != 0) {
      if (a[i] + rr < n) {
        cout << "IMPOSSIBLE" << endl;
        return;
      } else {
        for (int t = 0; t < n; t++) {
          int j = ke[i][0];
          if (t % 2 == 0) {
            cout << color[i];
          } else {
            cout << color[j];
          }
        }
        cout << endl;
        return;
      }
    }
  }
  for (int i = 0; i < 6; i++)
    cc[i] = 0;

  for (int i = 1; i < 6; i += 2) { // xet OVG
    if (a[i] == 0)
      continue;
    data p;
    p.type = ke[i][0];
    int j = ke[i][0];
    a[j] -= (a[i] + 1);
    string s = color[j];
    for (int t = 0; t < a[i]; t++) {
      s += color[i] + color[j];
    }
    p.s = s;
    ans[j].push_back(p);
    cc[j]++;
  }
  for (int i = 0; i < 6; i += 2) {
    if (a[i] == 0)
      continue;
    for (int t = 0; t < a[i]; t++) {
      data p;
      p.type = i;
      p.s = color[i];
      ans[i].push_back(p);
    }
    cc[i] += a[i];
  }

  int maxcc = max(cc[0], cc[2]);
  maxcc = max(maxcc, cc[4]);
  if (2 * maxcc > (cc[0] + cc[2] + cc[4])) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  int maxT = -1, minT1 = -1, minT2 = -1;
  for (int i = 0; i < 6; i += 2) {
    if (maxT == -1 && maxcc == cc[i]) {
      maxT = i;
    } else {
      if (minT1 == -1) {
        minT1 = i;
      } else {
        minT2 = i;
      }
    }
  }
  if (cc[minT1] < cc[minT2])
    swap(minT1, minT2);
  // RBY
  int cRBY = cc[0] + cc[2] + cc[4] - 2 * maxcc;
  for (int t = 0; t < cRBY; t++) {
    data p = ans[maxT].back();
    ans[maxT].pop_back();
    cout << p.s;
    p = ans[minT1].back();
    ans[minT1].pop_back();
    cout << p.s;
    p = ans[minT2].back();
    ans[minT2].pop_back();
    cout << p.s;
  }

  while (!ans[maxT].empty()) {
    data p = ans[maxT].back();
    ans[maxT].pop_back();
    cout << p.s;
    if (!ans[minT1].empty()) {
      p = ans[minT1].back();
      ans[minT1].pop_back();
      cout << p.s;
    } else {
      p = ans[minT2].back();
      ans[minT2].pop_back();
      cout << p.s;
    }
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);

  init();
  int ntest;
  cin >> ntest;
  for (int nt = 1; nt <= ntest; nt++) {
    cout << "Case #" << nt << ": ";
    solve();
  }

  return 0;
}
