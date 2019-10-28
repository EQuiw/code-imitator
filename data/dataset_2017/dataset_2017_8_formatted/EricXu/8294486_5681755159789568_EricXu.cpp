#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int T, N, Q, U, V;
int *E, *S;
long long *D;

long long dist(int i, int j) {
  int k;
  long long s = 0;
  for (k = i; k < j; k++) {
    s += D[k];
  }
  return s;
}

double mymin(double a, double b) {
  if (a == -1.0)
    return b;
  else
    return min(a, b);
}

double solve() {
  int i, j;
  double *M;
  M = new double[N];
  M[0] = 0;
  long long td;
  for (i = 1; i < N; i++) {
    M[i] = -1.0;
    for (j = 0; j < i; j++) {
      td = dist(j, i);
      if (E[j] >= td)
        M[i] = mymin(M[i], M[j] + 1.0 * td / S[j]);
    }
  }
  double r = M[N - 1];
  delete[] M;
  return r;
}

int main() {
  int i, j, k, temp;
  ifstream infile("pony.in");
  ofstream outfile;
  outfile.open("pony.txt");
  infile >> T;
  for (i = 0; i < T; i++) {
    infile >> N >> Q;
    E = new int[N];
    S = new int[N];
    D = new long long[N];
    for (j = 0; j < N; j++)
      infile >> E[j] >> S[j];
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        if (k == j + 1)
          infile >> D[j];
        else
          infile >> temp;
      }
    }
    for (j = 0; j < Q; j++) {
      infile >> U >> V;
    }
    double r = solve();
    outfile << "Case #" << i + 1 << ": " << setprecision(10) << r << endl;
    delete[] E;
    delete[] S;
    delete[] D;
  }
  outfile.close();
  infile.close();
  return 0;
}
