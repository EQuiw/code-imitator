#include <fstream>
#include <iostream>
using namespace std;

char gc(unsigned int v) {
  if (v == 0)
    return ('R');
  if (v == 1)
    return ('Y');
  return ('B');
}

int main() {
  ifstream fin("data.in");
  ofstream fout("data.out");
  unsigned int T;
  fin >> T;
  for (unsigned int x = 1; x <= T; x++) {
    fout << "Case #" << x << ": ";
    unsigned int N, R, O, Y, G, B, V, max, sc, tc;
    fin >> N >> R >> O >> Y >> G >> B >> V;
    if (R >= Y && R >= B)
      max = 0;
    else if (Y >= B)
      max = 1;
    else
      max = 2;
    if ((max == 0 && R > Y + B) || (max == 1 && Y > R + B) ||
        (max == 2 && B > R + Y)) {
      fout << "IMPOSSIBLE\n";
      continue;
    }
    unsigned int CC[3];
    CC[0] = R;
    CC[1] = Y;
    CC[2] = B;
    sc = (max + 1) % 3;
    tc = (max + 2) % 3;
    if (CC[sc] < CC[tc]) {
      sc = (max + 2) % 3;
      tc = (max + 1) % 3;
    }
    fout << gc(max);
    unsigned int lc = max;
    for (unsigned int i = 1; i < N; i++) {
      if (CC[max] > CC[sc] && lc != max) {
        fout << gc(max);
        CC[max]--;
        lc = max;
      } else if (CC[sc] > CC[tc] && lc != sc) {
        fout << gc(sc);
        CC[sc]--;
        lc = sc;
      } else {
        fout << gc(tc);
        CC[tc]--;
        lc = tc;
      }
    }
    fout << "\n";
  }
  fin.close();
  fout.close();
  return (0);
}