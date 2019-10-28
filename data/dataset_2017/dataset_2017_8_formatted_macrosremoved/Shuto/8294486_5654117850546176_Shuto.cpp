#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

inline void solve() {
  long long int n;
  cin >> n;
  long long int r, o, y, g, b, v;
  cin >> r >> o >> y >> g >> b >> v;
  long long int ma = max(r, max(y, b));
  if (ma > n / 2) {
    puts("IMPOSSIBLE");
    return;
  }
  string left, right;
  vector<pair<long long int, char>> p;
  p.push_back({r, 'R'});
  p.push_back({y, 'Y'});
  p.push_back({b, 'B'});
  sort((p).begin(), (p).end());
  for (long long int i = 0; i < ((long long int)((n + 1) / 2 - p[2].first));
       i++)
    left += p[0].second;
  for (long long int i = 0; i < ((long long int)(p[2].first)); i++)
    left += p[2].second;
  for (long long int i = 0; i < ((long long int)(p[1].first)); i++)
    right += p[1].second;
  for (long long int i = 0; i < ((long long int)(n / 2 - p[1].first)); i++)
    right += p[0].second;
  for (long long int i = 0;
       i < ((long long int)(((long long int)(right).size()) - 1)); i++) {
    if (right[i] != right[i + 1]) {
      swap(right[i], right[((long long int)(right).size()) - 1]);
      break;
    }
  }

  string ress;
  for (long long int i = 0;
       i < ((long long int)(((long long int)(right).size()))); i++) {
    ress += left[i];
    ress += right[i];
  }
  if (n % 2 > 0)
    ress += left[((long long int)(left).size()) - 1];
  cout << ress << endl;

  // check
  if (ress[0] == ress[((long long int)(ress).size()) - 1])
    throw;
  for (long long int i = 0;
       i < ((long long int)(((long long int)(ress).size()) - 1)); i++) {
    if (ress[i] == ress[i + 1])
      throw;
  }
}

int main() {
  long long int t;
  cin >> t;
  for (long long int case_num = 0; case_num < ((long long int)(t));
       case_num++) {
    cout << "Case #" << case_num + 1 << ": ";
    solve();
  }

  return 0;
}
