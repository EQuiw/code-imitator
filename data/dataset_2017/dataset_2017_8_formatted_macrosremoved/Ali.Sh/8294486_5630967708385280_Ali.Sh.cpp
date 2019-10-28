#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 101 * 1001;

ifstream fin("in.in");
ofstream fout("out.out");

int32_t main() {
  ios::sync_with_stdio(0);
  fin.tie(0);
  long long t;
  fin >> t;
  fout << fixed << setprecision(6);
  for (long long _ = 1; _ <= t; _++) {
    long long n;
    long double d;
    fin >> d >> n;
    long double lst = 0.;
    for (long long i = 0; i < n; i++) {
      long double x, v;
      fin >> x >> v;
      lst = max(lst, (d - x) / v);
    }
    fout << "Case #" << _ << ": " << d / lst << '\n';
  }
}
