//
//  main.cpp
//  ProblemD
//
//  Created by Tung Nguyen on 4/9/17.
//
//

#include <fstream>

using namespace std;

int N;
char G[100][100];
char O[100][100];

void solve() {
  //  if no o, upgrade x to o or asign o to [0][0], then asign + to all row or
  //  column with o
  int oC = -1;
  int xC = -1;
  for (int c = 0; c < N; c++) {
    if (G[0][c] == 'o') {
      oC = c;
    }
    if (G[0][c] == 'x') {
      xC = c;
    }
  }
  if (oC == -1) {
    if (xC != -1) {
      G[0][xC] = 'o';
      xC = -1;
      oC = xC;
    } else {
      G[0][0] = 'o';
      oC = 0;
    }
  }
  for (int c = 0; c < N; c++) {
    if (c != oC) {
      G[0][c] = '+';
    }
  }

  //  fill x to other rows
  int xCl = oC - 1;
  int xCr = oC + 1;
  for (int r = 1; r < N; r++) {
    if (xCl >= 0) {
      G[r][xCl] = 'x';
      xCl--;
    } else if (xCr < N) {
      G[r][xCr] = 'x';
      xCr++;
    }
  }
  for (int c = 1; c < N - 1; c++) {
    G[N - 1][c] = '+';
  }
}

int main(int argc, const char *argv[]) {

  ifstream fin("D-small-attempt3.in.txt");
  ofstream fout("D-small-attempt3.out.txt");

  int T;
  fin >> T;
  for (int Case = 1; Case <= T; Case++) {
    int M;
    fin >> N >> M;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        G[i][j] = '.';
        O[i][j] = '.';
      }
    }
    for (int i = 0; i < M; i++) {
      char ch;
      int r, c;
      fin >> ch >> r >> c;
      G[r][c] = ch;
      O[r][c] = ch;
    }

    solve();

    int score = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (G[i][j] == 'o') {
          score += 2;
          count++;
        }
        if (G[i][j] == '+' || G[i][j] == 'x') {
          score += 1;
          count++;
        }
      }
    }
    fout << "Case #" << Case << ": " << score << " " << count << endl;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (G[i][j] != O[i][j]) {
          fout << G[i][j] << " " << i << " " << j << endl;
        }
      }
    }
  }

  fout.close();
  fin.close();

  return 0;
}
