#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  ifstream fin("data.in");
  ofstream fout("data.out");
  unsigned int T;
  fin >> T;
  for (unsigned int x = 1; x <= T; x++) {
    fout << "Case #" << x << ": ";
    string N;
    fin >> N;
    unsigned int i = 0;
    while (i < N.length() - 1 && N[i] <= N[i + 1])
      i++;
    if (i == N.length() - 1)
      fout << N;
    else {
      for (unsigned int j = i + 1; j < N.length(); j++)
        N[j] = '9';
      while (i > 0 && N[i] == N[i - 1])
        N[i--] = '9';
      N[i] = N[i] - 1;
      for (i = 0; i < N.length(); i++)
        if (N[i] != '0')
          break;
      for (unsigned int j = i; j < N.length(); j++)
        fout << N[j];
    }
    fout << "\n";
  }
  fin.close();
  fout.close();
  return (0);
}
