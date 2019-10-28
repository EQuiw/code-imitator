#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

vi v;
int m;
ll getVal(int id) {
  ll val = 0;
  int bf = 0;
  for (int i = 0; i < id; i++) {
    val *= 10;
    if (bf > v[i])
      return -1;
    bf = v[i];
    val += v[i];
  }

  if (bf >= v[id])
    return -1;
  val *= 10;
  val += v[id] - 1;

  for (int i = id + 1; i < m; i++) {
    val *= 10;
    val += 9;
  }

  return val;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;
  int T;
  cin >> T;
  for (int test = 1; test < T + 1; test++) {
    cout << "Case #" << test << ": ";
    string s;
    cin >> s;
    v.clear();
    for (int i = 0; i < s.size(); i++) {
      v.push_back(s[i] - '0');
    }

    m = v.size();
    if (m == 1) {
      cout << v[0] << endl;
      continue;
    }
    ll res = 0;
    for (int i = 0; i < m - 1; i++) {
      res *= 10;
      res += 9;
    }
    ll tmp = v[0];
    bool flg = false;
    for (int i = 1; i < v.size(); i++) {
      if (v[i - 1] > v[i])
        flg = true;
      tmp *= 10;
      tmp += v[i];
    }
    if (!flg)
      res = max(res, tmp);
    for (int i = 0; i < v.size(); i++) {
      ll val = getVal(i);
      res = max(res, val);
    }
    cout << res << endl;
  }
  return 0;
}
