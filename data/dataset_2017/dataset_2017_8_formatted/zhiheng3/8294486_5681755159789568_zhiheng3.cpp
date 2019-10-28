#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Horse {
  int E, S;
} horse[100];
int N;

int d[100][100];

double f[100][100];

double calc(int U, int V) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      f[i][j] = -1;
    }
  }
  long long s[100];
  s[0] = 0;
  for (int i = 1; i < N; ++i) {
    s[i] = s[i - 1] + d[i - 1][i];
  }
  f[0][0] = 0;
  for (int i = 1; i < N; ++i) {
    for (int j = 0; j < i; ++j) {
      if (horse[j].E < s[i] - s[j]) {
        f[i][j] = -1;
      } else {
        f[i][j] = (s[i] - s[j]) * 1.0 / horse[j].S;
        if (j > 0) {
          double minn = f[j][j - 1];
          for (int k = 0; k < j - 1; ++k) {
            if (f[j][k] > 0 && f[j][k] < minn) {
              minn = f[j][k];
            }
          }
          f[i][j] += minn;
        }
      }
    }
  }

  double result = f[N - 1][N - 2];
  for (int i = 0; i < N - 2; ++i) {
    if (f[N - 1][i] > 0 && f[N - 1][i] < result) {
      result = f[N - 1][i];
    }
  }
  return result;
}

int main() {
  cout.precision(8);
  cout.flags(ios::fixed);
  int T, Q;
  cin >> T;
  for (int c = 1; c <= T; ++c) {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) {
      cin >> horse[i].E >> horse[i].S;
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cin >> d[i][j];
      }
    }
    cout << "Case #" << c << ":";
    for (int i = 0; i < Q; ++i) {
      int U, V;
      cin >> U >> V;
      cout << ' ' << calc(U, V);
    }
    cout << endl;
  }
  return 0;
}