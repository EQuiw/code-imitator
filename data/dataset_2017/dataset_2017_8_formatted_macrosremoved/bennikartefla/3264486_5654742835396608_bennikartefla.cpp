#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1 << 31);
const double pi = acos(-1);

int main() {
  cin.sync_with_stdio(false);
  ofstream fout("ans.txt");
  int n;
  cin >> n;
  for (int i = (0); i < (n); i++) {
    priority_queue<int> k;
    int m, q;
    cin >> m >> q;
    fout << "Case #" << i + 1 << ": ";
    k.push(m - 1);
    for (int a = (0); a < (q - 1); a++) {
      if (k.empty())
        break;
      else {
        int at = k.top();
        k.pop();
        if (at == 0)
          continue;
        int want = at / 2;
        int first = want;
        if (first != 0)
          k.push(first - 1);
        int second = at - want;
        k.push(second - 1);
      }
    }
    if (k.empty())
      fout << "0 0" << endl;
    else {
      int at = k.top();
      if (at == 0)
        fout << "0 0" << endl;
      else {
        int first = at / 2;
        fout << at - first << " " << first << endl;
      }
    }
  }
  return 0;
}
