#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int T, N;
double K[1010], S[1010], D;

bool check(double sp) {
  int i;
  for (i = 1; i <= N; i++) {
    if (sp <= S[i])
      continue;
    double pos = sp * K[i] / (sp - S[i]);
    if (pos < D)
      return 0;
  }

  return 1;
}

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int i, t, k;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    fin >> D >> N;

    for (i = 1; i <= N; i++)
      fin >> K[i] >> S[i];

    double l = 0, r = (1LL << 60);
    for (k = 1; k <= 200; k++) {
      double mid = (l + r) / 2;
      if (check(mid))
        l = mid;
      else
        r = mid;
    }

    fout << fixed << setprecision(9) << l << "\n";
  }
  return 0;
}
