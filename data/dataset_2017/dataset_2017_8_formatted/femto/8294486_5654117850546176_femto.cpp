#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int R = 1;
const int Y = 2;
const int B = 4;
// R O Y G B V
const int r = 0;
const int o = 1;
const int y = 2;
const int g = 3;
const int b = 4;
const int v = 5;
int C[6] = {R, R + Y, Y, Y + B, B, R + B};
string s[6] = {"R", "O", "Y", "G", "B", "V"};

bool check(vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] & v[(i + 1) % v.size()])
      return false;
  }
  return true;
}

void solve() {
  int cnt[6];
  int tmp[6];
  int N;
  cin >> N;
  for (int i = 0; i < 6; i++) {
    cin >> cnt[i];
    tmp[i] = cnt[i];
  }
  if (cnt[o] > cnt[b] + 1 || cnt[g] > cnt[r] + 1 || cnt[v] > cnt[y] + 1) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  cnt[b] -= cnt[o];
  cnt[r] -= cnt[g];
  cnt[y] -= cnt[v];
  int n = cnt[b] + cnt[r] + cnt[y];

  typedef pair<int, int> P;
  P p[3] = {{cnt[b], b}, {cnt[r], r}, {cnt[y], y}};
  sort(p, p + 3);
  reverse(p, p + 3);

  if (p[0].first > p[1].first + p[2].first) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  vector<int> t(p[0].first, 1);
  int idx = 0;
  for (int i = 0; i < p[1].first; i++) {
    t[idx] += 2;
    idx = (idx + 1) % t.size();
  }
  for (int i = 0; i < p[2].first; i++) {
    t[idx] += 4;
    idx = (idx + 1) % t.size();
  }

  vector<int> ans;
  for (auto x : t) {
    for (int i = 0; i <= 2; i++) {
      if ((x >> i & 1) == 0)
        continue;
      int c = p[i].second;
      if (c == b && tmp[o]) {
        for (int j = 0; j < tmp[o]; j++) {
          ans.push_back(c);
          ans.push_back(o);
        }
        tmp[o] = 0;
      }
      if (c == r && tmp[g]) {
        for (int j = 0; j < tmp[g]; j++) {
          ans.push_back(c);
          ans.push_back(g);
        }
        tmp[g] = 0;
      }
      if (c == y && tmp[v]) {
        for (int j = 0; j < tmp[v]; j++) {
          ans.push_back(c);
          ans.push_back(v);
        }
        tmp[v] = 0;
      }
      ans.push_back(c);
    }
  }
  assert(ans.size() == N);
  assert(check(ans));
  for (auto x : ans) {
    cout << s[x];
  }
  cout << endl;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cerr << i << endl;
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
}