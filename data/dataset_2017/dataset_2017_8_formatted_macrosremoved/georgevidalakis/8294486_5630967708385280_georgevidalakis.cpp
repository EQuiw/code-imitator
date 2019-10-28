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
    unsigned int N, S[1000];
    unsigned long long int D, K[1000];
    double y, T[1000];
    fin >> D >> N;
    for (unsigned int i = 0; i < N; i++)
      fin >> K[i] >> S[i];
    for (unsigned int i = 1; i < N; i++)
      for (unsigned int j = N - 1; j >= i; j--)
        if (K[j] < K[j - 1]) {
          unsigned long long int tmp;
          tmp = K[j];
          K[j] = K[j - 1];
          K[j - 1] = tmp;
          tmp = S[j];
          S[j] = S[j - 1];
          S[j - 1] = tmp;
        }
    for (int i = N - 1; i >= 0; i--) {
      T[i] = (D - K[i]) * 1.0 / S[i];
      if (i < N - 1 && T[i] < T[i + 1])
        T[i] = T[i + 1];
    }
    y = D / T[0];
    fout << setprecision(20) << y << "\n";
  }
  fin.close();
  fout.close();
  return (0);
}
