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

const int N = 1e2;

ll needed[N];
ll got[N][N];
bool available[N][N];
bool ispackage[N][N];
int n, p;

bool is_package(int p1, int p2) {
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  for (
      int i =
          (1 /*max( int(needed[0] * 0.9 / got[0][p1]), int(needed[1] * 0.9 / got[1][p2]) )*/);
      i < (1e6 + 1); ++i) {

    if ((i * needed[0] * 0.9 <= got[0][p1] &&
         i * needed[0] * 1.1 >= got[0][p1]) &&
        (i * needed[1] * 0.9 <= got[1][p2] &&
         i * needed[1] * 1.1 >= got[1][p2])) {
      /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
      return true;
    }
    // if ( i * needed[0] * 0.9 > got[0][p1] || i * needed[1] * 0.9 > got[1][p2]
    // ) 	break;
  }
  return false;
}

int solve(int package) {
  for (int i = (0); i < (p); ++i)
    for (int j = (0); j < (p); ++j)
      ispackage[i][j] = is_package(i, j);
  vi r;
  for (int i = (0); i < (p); ++i)
    r.push_back(i);
  int best = 0;
  do {
    int res = 0;
    for (int i = (0); i < (p); ++i)
      if (ispackage[i][r[i]])
        ++res;
    best = max(best, res);
  } while (next_permutation(r.begin(), r.end()));
  return best;
}

int main() {
  int t;
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    cin >> n >> p;
    /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
    /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
    for (int i = (0); i < (n); ++i)
      cin >> needed[i];
    for (int i = (0); i < (n); ++i) {
      for (int j = (0); j < (p); ++j) {
        cin >> got[i][j];
        available[i][j] = 1;
      }
    }
    if (n == 1) {
      needed[1] = 0;
      memset(got[1], 0, sizeof(got[1]));
      for (int i = (0); i < (p); ++i)
        available[1][i] = 1;
    }
    cout << "Case #" << caseNr << ": " << solve(0) << endl;
  }
  return 0;
}
