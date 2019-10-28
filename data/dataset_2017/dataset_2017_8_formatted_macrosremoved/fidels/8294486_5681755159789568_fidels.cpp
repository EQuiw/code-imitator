#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int T, t, N, Q, D[128], i, j, k;
  long long n[128][128];
  double time[128][128], S[128];

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> N >> Q;

    for (i = 1; i <= N; i++)
      cin >> D[i] >> S[i];
    for (i = 1; i <= N; i++)
      for (j = 1; j <= N; j++) {
        cin >> n[i][j];
        if (n[i][j] == -1) {
          if (i == j)
            n[i][j] = 0;
          else
            n[i][j] = 1000000000000000000LL;
        }
      }

    for (k = 1; k <= N; k++)
      for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
          if (n[i][j] > n[i][k] + n[k][j])
            n[i][j] = n[i][k] + n[k][j];

    //		for (i=1; i<=N; i++) {
    //			for (j=1; j<=N; j++) cerr << n[i][j] << '\t';
    //			cerr << endl;
    //		}

    for (i = 1; i <= N; i++)
      for (j = 1; j <= N; j++) {
        if (n[i][j] <= D[i])
          time[i][j] = n[i][j] / S[i];
        else
          time[i][j] = 1e18;
        ;
      }

    for (k = 1; k <= N; k++)
      for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
          if (time[i][j] > time[i][k] + time[k][j])
            time[i][j] = time[i][k] + time[k][j];

    //		for (i=1; i<=N; i++) {
    //			for (j=1; j<=N; j++) printf("%.8lf\t", time[i][j]);
    //			cerr << endl;
    //		}

    printf("Case #%d:", t);
    for (i = 0; i < Q; i++) {
      cin >> j >> k;
      printf(" %.8lf", time[j][k]);
    }
    printf("\n");
  }

  return 0;
}
