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

int main() {
  int t, d, n, k, s;
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    double maxSpeed;
    cin >> d >> n;
    for (int i = (0); i < (n); ++i) {
      cin >> k >> s;
      double speed = d / (double(d - k) / s);
      if (!i || speed < maxSpeed)
        maxSpeed = speed;
    }
    printf("Case #%d: %.8f\n", caseNr, maxSpeed);
    //		cout << "Case #" << caseNr << ": " << setprecimaxSpeed << endl;
  }
  return 0;
}
