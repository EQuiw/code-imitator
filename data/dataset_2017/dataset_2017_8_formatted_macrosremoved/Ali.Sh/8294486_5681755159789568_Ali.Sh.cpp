#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 111;

ifstream fin("in.in");
ofstream fout("out.out");

long long d[MAXN][MAXN];

long double dis[MAXN][MAXN];

long long l[MAXN], v[MAXN];

int32_t main() {
  ios::sync_with_stdio(0);
  fin.tie(0);
  long long t;
  fin >> t;
  fout << fixed << setprecision(6);
  for (long long _ = 1; _ <= t; _++) {
    long long n, q;
    fin >> n >> q;
    for (long long i = 0; i < n; i++)
      fin >> l[i] >> v[i];
    for (long long i = 0; i < n; i++)
      for (long long j = 0; j < n; j++) {
        fin >> d[i][j];
        if (d[i][j] == -1)
          d[i][j] = 1e18;
        if (i == j)
          d[i][j] = 0;
      }
    for (long long k = 0; k < n; k++)
      for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    for (long long i = 0; i < n; i++)
      for (long long j = 0; j < n; j++) {
        dis[i][j] = 1e18;
        if (d[i][j] <= l[i])
          dis[i][j] = (long double)d[i][j] / (long double)v[i];
      }
    for (long long k = 0; k < n; k++)
      for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
          dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    fout << "Case #" << _ << ": ";
    for (long long i = 0; i < q; i++) {
      long long s, t;
      fin >> s >> t;
      fout << dis[s - 1][t - 1] << ' ';
    }
    fout << '\n';
  }
}
