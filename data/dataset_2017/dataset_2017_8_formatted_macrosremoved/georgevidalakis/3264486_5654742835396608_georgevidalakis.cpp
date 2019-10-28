#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ifstream fin("data.in");
  ofstream fout("data.out");
  unsigned int T;
  fin >> T;
  for (unsigned int x = 1; x <= T; x++) {
    fout << "Case #" << x << ": ";
    unsigned int u = 1;
    unsigned long long int N, K, T[3][2];
    fin >> N >> K;
    T[0][0] = N;
    T[0][1] = 1;
    while (K > T[0][1]) {
      K -= T[0][1];
      unsigned long long int S[2][2], s;
      if (T[0][0] % 2) {
        s = 1;
        S[0][0] = (T[0][0] - 1) / 2;
        S[0][1] = T[0][1] * 2;
      } else {
        s = 2;
        S[0][0] = T[0][0] / 2;
        S[1][0] = T[0][0] / 2 - 1;
        S[0][1] = S[1][1] = T[0][1];
      }
      for (unsigned int i = 1; i < u; i++) {
        T[i - 1][0] = T[i][0];
        T[i - 1][1] = T[i][1];
      }
      u--;
      for (unsigned int i = 0; i < s; i++) {
        bool found = false;
        for (unsigned int j = 0; j < u; j++) {
          if (T[j][0] == S[i][0]) {
            found = true;
            T[j][1] += S[i][1];
          }
        }
        if (!found) {
          T[u][0] = S[i][0];
          T[u][1] = S[i][1];
          u++;
        }
      }
      if (u == 2 && T[0][0] < T[1][0]) {
        unsigned long long int tmp;
        tmp = T[0][0];
        T[0][0] = T[1][0];
        T[1][0] = tmp;
        tmp = T[0][1];
        T[0][1] = T[1][1];
        T[1][1] = tmp;
      }
      /*for (unsigned int i = 0; i < u; i++)
      {
              for (unsigned int j = 0; j < T[i][1]; j++) fout << T[i][0] << ",";
      }
      fout << "\n";*/
    }
    if (T[0][0] % 2)
      fout << (T[0][0] - 1) / 2 << " " << (T[0][0] - 1) / 2 << "\n";
    else
      fout << T[0][0] / 2 << " " << T[0][0] / 2 - 1 << "\n";
  }
  fin.close();
  fout.close();
  return (0);
}
