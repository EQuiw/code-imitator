//
//  main.cpp
//  ProblemC
//
//  Created by Tung Nguyen on 4/22/17.
//
//

#include <fstream>

using namespace std;

int N, Q;
long long E[100], S[100];
long long D[100][100];
int U[100], V[100];

double result[100];

double bestsofar[100];

void solve() {
  for (int i = 0; i < 100; i++) {
    bestsofar[i] = -1;
  }

  bestsofar[0] = 0;
  for (int i = 0; i < N; i++) {
    long long e = E[i], s = S[i];
    double time = bestsofar[i];
    for (int j = i + 1; j < N; j++) {
      long long distance = D[j - 1][j];
      if (distance > e) {
        break;
      }
      time += distance * 1.0 / s;
      if (bestsofar[j] == -1 || time < bestsofar[j]) {
        bestsofar[j] = time;
      }
      e -= distance;
    }
  }
  result[0] = bestsofar[N - 1];
}

int main(int argc, const char *argv[]) {
  ifstream fin("C-small-attempt0.in.txt");
  ofstream fout("C-small-attempt0.out.txt");

  int T;
  fin >> T;
  for (int Case = 1; Case <= T; Case++) {
    fin >> N >> Q;
    for (int i = 0; i < N; i++) {
      fin >> E[i] >> S[i];
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        fin >> D[i][j];
      }
    }

    for (int i = 0; i < Q; i++) {
      fin >> U[i] >> V[i];
    }

    solve();

    fout << "Case #" << Case << ":";
    for (int i = 0; i < Q; i++) {
      char buff[100];
      snprintf(buff, sizeof(buff), "%.8f", result[i]);
      fout << " " << buff;
    }
    fout << endl;
  }

  fin.close();
  fout.close();
  return 0;
}
