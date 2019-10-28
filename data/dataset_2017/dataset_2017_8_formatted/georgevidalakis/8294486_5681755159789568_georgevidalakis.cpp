#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  ifstream fin("data.in");
  ofstream fout("data.out");
  unsigned int T;
  fin >> T;
  for (unsigned int x = 1; x <= T; x++) {
    fout << "Case #" << x << ": ";
    unsigned int N, Q, S[100], U, V;
    unsigned long long int E[100];
    long long int D[100][100];
    fin >> N >> Q;
    for (unsigned int i = 0; i < N; i++)
      fin >> E[i] >> S[i];
    for (unsigned int i = 0; i < N; i++)
      for (unsigned int j = 0; j < N; j++)
        fin >> D[i][j];
    fin >> U >> V;
    long long int HD[100];
    double HT[100];
    for (unsigned int i = 0; i < N; i++) {
      HD[i] = 0;
      HT[0] = 0;
    }
    for (unsigned int i = 0; i < N - 1; i++) {
      if (i > 0) {
        double min = -1;
        for (unsigned int j = 0; j < i; j++)
          if (HD[j] != -1 && (min == -1 || HT[j] < min))
            min = HT[j];
        HT[i] = min;
      }
      for (unsigned int j = 0; j <= i; j++)
        if (HD[j] >= 0) {
          HD[j] += D[i][i + 1];
          if (HD[j] > E[j])
            HD[j] = -1;
          else
            HT[j] += D[i][i + 1] * 1.0 / S[j];
        }
    }
    double min = -1;
    for (unsigned int i = 0; i < N - 1; i++)
      if (HD[i] != -1 && (min == -1 || HT[i] < min))
        min = HT[i];
    fout << setprecision(15) << min << "\n";
  }
  fin.close();
  fout.close();
  return (0);
}