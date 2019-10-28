#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1 << 31);
const double pi = acos(-1);

bool check(int a) {
  string s = to_string(a);
  vi k;
  for (int i = (0); i < (s.size()); i++) {
    char m = s[i];
    k.push_back(m - '0');
  }
  vi ne = k;
  sort(ne.begin(), ne.end());
  for (int i = (0); i < (k.size()); i++)
    if (k[i] != ne[i])
      return false;
  return true;
}

int main() {
  cin.sync_with_stdio(false);
  ofstream fout("ans.txt");
  int n;
  cin >> n;
  for (int i = (0); i < (n); i++) {
    int m;
    cin >> m;
    for (int a = m; a >= 0; a--) {
      if (check(a)) {
        fout << "Case #" << i + 1 << ": " << a << endl;
        break;
      }
    }
  }
  return 0;
}
