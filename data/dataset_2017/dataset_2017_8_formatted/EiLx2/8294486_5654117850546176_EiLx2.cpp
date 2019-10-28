#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int T, N, R, O, Y, G, B, V;

char a[3][1010];
int cnt[300];
char cr;

char get_char() {
  if (cnt[cr] == 0) {
    if (cnt['Y'] > 0)
      cr = 'Y';
    else if (cnt['R'] > 0)
      cr = 'R';
    else
      cr = 'B';
  }

  cnt[cr]--;
  return cr;
}

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int t, j, i;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    fin >> N >> R >> O >> Y >> G >> B >> V;
    if (R > Y + B || Y > R + B || B > R + Y) {
      fout << "IMPOSSIBLE\n";
      continue;
    }

    memset(cnt, 0, sizeof(cnt));
    cnt['R'] = R, cnt['Y'] = Y, cnt['B'] = B;

    int tot = N / 2;
    if (R == max({R, Y, B}))
      cr = 'R';
    else if (Y == max({R, Y, B}))
      cr = 'Y';
    else
      cr = 'B';

    for (j = 1; j <= 2; j++) {
      for (i = 1; i <= tot; i++) {
        a[j][i] = get_char();
      }
    }

    if (N % 2)
      a[2][tot + 1] = get_char();
    for (i = 1; i <= tot; i++)
      if (N % 2)
        fout << a[2][i] << a[1][i];
      else
        fout << a[1][i] << a[2][i];

    if (N % 2)
      fout << a[2][tot + 1];
    fout << "\n";
  }
  return 0;
}
