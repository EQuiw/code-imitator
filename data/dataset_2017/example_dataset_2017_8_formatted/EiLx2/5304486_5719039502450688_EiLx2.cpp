#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define fi first
#define se second
typedef long long LL;
typedef long double LD;

int T, Hd1, Ad1, Hk1, Ak1, B, D;

int get_nr(int deb, int buf) {
  int Hd = Hd1, Ad = Ad1, Hk = Hk1, Ak = Ak1;
  int maxh = Hd;

  int res = 0;
  bool lst = 0, nlst;
  while (Hk > 0) {
    res++;
    nlst = 0;
    if (Ad >= Hk)
      return res;

    if (Hd <= Ak) {
      if (deb && Hd > max(Ak - D, 0))
        Ak = max(Ak - D, 0), deb--;
      else if (maxh > Ak && !lst)
        Hd = maxh, nlst = 1;
      else
        return (1 << 30);
    } else {
      if (deb)
        Ak = max(Ak - D, 0), deb--;
      else if (buf)
        Ad += B, buf--;
      else
        Hk -= Ad;
    }
    lst = nlst;
    Hd -= Ak;
  }

  return res;
}

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int t, i, j;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    cout << t << "\n";
    fin >> Hd1 >> Ad1 >> Hk1 >> Ak1 >> B >> D;

    int res = (1 << 30);
    for (i = 0; i <= Ak1 + 10; i++)
      for (j = 0; j <= Hk1 + 10; j++)
        res = min(res, get_nr(i, j));

    if (res == (1 << 30))
      fout << "IMPOSSIBLE\n";
    else
      fout << res << "\n";
  }
  return 0;
}
