#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> Matrix;

const int INF = 1e9 + 7;
const double PI = acos(-1);
const double EPS = 1e-9;

const int N = 1e6 + 5;

bool isTidy(ll n) {
  stringstream second;
  second << n;
  string num = second.str();
  return is_sorted(num.begin(), num.end());
}

int main() {
  int t, k;
  ll n;
  string s;
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    cout << "Case #" << caseNr << ": ";
    cin >> n;
    int res = 1;
    for (int i = (1); i < (n + 1); ++i)
      if (isTidy(i))
        res = i;
    cout << res << endl;
  }
  return 0;
}
