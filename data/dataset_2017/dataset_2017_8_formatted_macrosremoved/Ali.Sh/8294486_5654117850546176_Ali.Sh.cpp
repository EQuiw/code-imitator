#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 101 * 1001;

ifstream fin("in.in");
ofstream fout("out.out");

/// R O Y G B V

/// R Y B RY YB RB

long long n;

long long a[6];

vector<char> v[MAXN];

int32_t main() {
  ios::sync_with_stdio(0);
  fin.tie(0);
  long long t;
  fin >> t;
  fout << fixed << setprecision(6);
  for (long long _ = 1; _ <= t; _++) {
    long long n;
    fin >> n;
    fin >> a[0] >> a[3] >> a[1] >> a[4] >> a[2] >> a[5];
    char ch;
    long long m;
    bool f = 0;
    if (a[0] > a[1] && a[0] > a[2]) {
      if (a[0] > a[1] + a[2])
        f = 1;
      m = a[0];
      ch = 'R';
      for (long long i = 0; i < m; i++)
        v[i].clear();
      long long j = 0;
      for (long long k = 0; k < a[1]; k++)
        v[j++].push_back('Y');
      for (long long k = 0; k < a[2]; k++) {
        j %= m;
        v[j++].push_back('B');
      }
    } else if (a[1] > a[2]) {
      if (a[1] > a[0] + a[2])
        f = 1;
      m = a[1];
      ch = 'Y';
      for (long long i = 0; i < m; i++)
        v[i].clear();
      long long j = 0;
      for (long long k = 0; k < a[0]; k++)
        v[j++].push_back('R');
      for (long long k = 0; k < a[2]; k++) {
        j %= m;
        v[j++].push_back('B');
      }
    } else {
      if (a[2] > a[0] + a[1])
        f = 1;
      ch = 'B';
      m = a[2];
      for (long long i = 0; i < m; i++)
        v[i].clear();
      long long j = 0;
      for (long long k = 0; k < a[1]; k++)
        v[j++].push_back('Y');
      for (long long k = 0; k < a[0]; k++) {
        j %= m;
        v[j++].push_back('R');
      }
    }
    fout << "Case #" << _ << ": ";
    if (f)
      fout << "IMPOSSIBLE";
    else {
      for (long long i = 0; i < m; i++) {
        fout << ch;
        for (auto u : v[i])
          fout << u;
      }
    }
    fout << '\n';
  }
}
