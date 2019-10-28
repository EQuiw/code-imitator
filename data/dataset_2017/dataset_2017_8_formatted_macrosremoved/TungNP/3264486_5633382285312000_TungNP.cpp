//
//  main.cpp
//  ProblemB
//
//  Created by Tung Nguyen on 4/8/17.
//
//

#include <fstream>
#include <string>

using namespace std;

int int_char(char ch) { return ch - '0'; }

int main(int argc, const char *argv[]) {
  ifstream fin("B-small-attempt2.in.txt");
  ofstream fout("B-small-attempt2.out.txt");

  int T;
  fin >> T;
  for (int Case = 1; Case <= T; Case++) {
    string N;
    fin >> N;

    char n1 = N[0];
    for (int i = 1; i < N.length(); i++) {
      char n2 = N[i];
      if (n2 < n1) {
        for (int j = i - 1; j >= 0; j--) {
          if (j == 0 || N[j - 1] < N[j]) {
            N[j]--;
            for (int k = j + 1; k < N.length(); k++) {
              N[k] = '9';
            }
            break;
          }
        }
        break;
      }
      n1 = n2;
    }
    if (N[0] == '0') {
      N.erase(0, 1);
    }
    fout << "Case #" << Case << ": " << N << endl;
  }

  fout.close();
  fin.close();

  return 0;
}
