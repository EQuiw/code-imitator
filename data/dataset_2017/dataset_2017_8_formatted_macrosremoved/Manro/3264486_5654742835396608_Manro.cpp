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

const int N = 1e3 + 5;
int occup[N], R[N], L[N];
ll t, n, k;

void precompute() {
  L[0] = 0;
  R[n + 1] = 0;
  for (int i = (1); i < (n + 2); ++i)
    L[i] = occup[i] ? 0 : L[i - 1] + 1;
  for (int i = (n); i >= (0); --i)
    R[i] = occup[i] ? 0 : R[i + 1] + 1;
}

int main() {
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    cout << "Case #" << caseNr << ": ";
    cin >> n >> k;
    memset(occup, 0, sizeof(occup));
    occup[0] = 1;
    occup[n + 1] = 1;
    int best;
    while (k--) {
      precompute();
      best = 1;
      for (int i = (1); i < (n + 1); ++i) {
        if (occup[i])
          continue;
        if (min(L[i], R[i]) > min(L[best], R[best]))
          best = i;
        else if (min(L[i], R[i]) == min(L[best], R[best]) &&
                 max(L[i], R[i]) > max(L[best], R[best]))
          best = i;
      }
      occup[best] = 1;
    }
    cout << max(L[best], R[best]) - 1 << " " << min(L[best], R[best]) - 1
         << endl;
  }
  return 0;
}
