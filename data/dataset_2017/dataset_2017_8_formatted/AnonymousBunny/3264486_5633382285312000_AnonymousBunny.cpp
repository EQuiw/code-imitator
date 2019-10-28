#include <bits/stdc++.h>
using namespace std;

long long int find(vector<int> v, int n) {
  if (v.size() > n)
    return -1;

  for (int i = 0; i < v.size() - 1; i++) {
    if (v[i] > v[i + 1])
      return -1;
  }

  while (v.size() < n)
    v.push_back(9);

  long long int cur = 1LL, ans = 0LL;
  reverse(v.begin(), v.end());
  for (int i = 0; i < v.size(); i++) {
    ans += 1LL * v[i] * cur;
    cur = 1LL * 10 * cur;
  }
  return ans;
}

long long int ret(vector<int> v) {
  int ind = -1;
  for (int i = 0; i < v.size() - 1; i++) {
    if (v[i] > v[i + 1]) {
      ind = i;
      break;
    }
  }
  vector<int> tmp;
  long long int ans = 0LL;
  for (int t = 0; t < v.size(); t++) {
    vector<int> tt;
    for (int i = 0; i < tmp.size(); i++)
      tt.push_back(tmp[i]);
    for (int i = 0; i < v[t]; i++) {
      tt.push_back(i);
      if (tt.empty())
        continue;
      ans = max(ans, find(tt, v.size()));
      tt.pop_back();
    }
    tmp.push_back(v[t]);
  }
  ans = max(ans, find(tmp, v.size()));
  return ans;
}

void solve(int tt) {
  vector<int> t;
  long long int n;
  cin >> n;
  while (n) {
    t.push_back(n % 10);
    n /= 10;
  }
  reverse(t.begin(), t.end());
  long long int uu = ret(t);
  cout << "Case #" << tt << ": " << uu << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
}