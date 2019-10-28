//
//  main.cpp
//  ProblemB
//
//  Created by Tung Nguyen on 4/15/17.
//
//

#include <cmath>
#include <fstream>

using namespace std;

int N, P;
int R[50];
int Q[50][50];
int nmin[50][50];
int nmax[50][50];

int result;

void find(int n, int p, int *nmax, int *nmin) {
  int q = Q[n][p];
  double rmax = q / 0.9;
  double rmin = q / 1.1;

  *nmin = ceil(rmin / R[n]);
  *nmax = floor(rmax / R[n]);
  if (*nmax == 0 || (*nmin > *nmax)) {
    *nmax = -1;
  }
}

void solve1() {
  int count = 0;
  for (int p = 0; p < P; p++) {
    if (nmax[0][p] > 0) {
      count++;
    }
  }
  result = count;
}

int Pair[50];
bool Paired[50];
int Pair_p;

void solve2() {
  if (Pair_p == P) {
    int count = 0;
    for (int p = 0; p < P; p++) {
      if (nmax[0][p] > 0 && nmax[1][Pair[p]] > 0 &&
          max(nmin[0][p], nmin[1][Pair[p]]) <=
              min(nmax[0][p], nmax[1][Pair[p]])) {
        count++;
      }
    }
    result = max(result, count);
    return;
  }
  for (int i = 0; i < P; i++) {
    if (!Paired[i]) {
      Paired[i] = true;
      Pair[Pair_p] = i;
      Pair_p++;

      solve2();

      Paired[i] = false;
      Pair_p--;
    }
  }
}

void solve() {
  for (int n = 0; n < N; n++) {
    for (int p = 0; p < P; p++) {
      find(n, p, &nmax[n][p], &nmin[n][p]);
    }
  }
  if (N == 1) {
    solve1();
  } else {
    for (int i = 0; i < P; i++) {
      Paired[i] = false;
      Pair[i] = 0;
    }
    Pair_p = 0;
    result = 0;
    solve2();
  }
}

int main(int argc, const char *argv[]) {
  ifstream fin("B-small-attempt0.in.txt");
  ofstream fout("B-small-attempt0.out.txt");

  int T;
  fin >> T;
  for (int Case = 1; Case <= T; Case++) {
    fin >> N >> P;
    for (int i = 0; i < N; i++) {
      fin >> R[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        fin >> Q[i][j];
      }
    }

    solve();

    fout << "Case #" << Case << ": " << result << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
