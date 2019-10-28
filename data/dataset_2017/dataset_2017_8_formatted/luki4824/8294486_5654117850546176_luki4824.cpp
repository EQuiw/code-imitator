#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N
#define RED 1
#define YELLOW 2
#define BLUE 4
using namespace std;
int n;
int tab[8];
void clear() {}
char toColor(int color) {
  if (color == 1)
    return 'R';
  if (color == 2)
    return 'Y';
  if (color == 3)
    return 'O';
  if (color == 4)
    return 'B';
  if (color == 5)
    return 'V';
  if (color == 6)
    return 'G';
}
string solveOne() {
  string res = "";
  int z[3];
  int last = -1;

  z[0] = tab[1];
  z[1] = tab[2];
  z[2] = tab[4];
  while (z[0] > 0 || z[1] > 0 || z[2] > 0) {
    int first = -1;
    if (res.length() > 0 && res[0] == 'R')
      first = 0;
    if (res.length() > 0 && res[0] == 'Y')
      first = 1;
    if (res.length() > 0 && res[0] == 'B')
      first = 2;

    int am = 0;
    int poz = 0;
    if (first != -1 && am < z[first] && first != last) {
      poz = first;
      am = z[first];
    }
    if (am < z[0] && 0 != last) {
      poz = 0;
      am = z[0];
    }
    if (am < z[1] && 1 != last) {
      poz = 1;
      am = z[1];
    }
    if (am < z[2] && 2 != last) {
      poz = 2;
      am = z[2];
    }
    // if(res.length()>0 && )
    if (poz == last || z[poz] == 0) {
      //	cout << poz << " " << last << " " << z[0] << " " << z[1] << " "
      //<< z[2] << " \n" << res << "\n";
      return "";
    }
    last = poz;
    z[poz]--;
    if (poz == 0)
      res += toColor(1);
    if (poz == 1)
      res += toColor(2);
    if (poz == 2)
      res += toColor(4);
  }
  if (res[0] == res[res.length() - 1])
    return "";
  return res;
}
string solveOneColor(int c) {
  string res = "";
  int z[3];
  int last = -1;
  z[0] = tab[c];
  z[1] = tab[7 - c];
  z[2] = 0;
  while (z[0] > 0 || z[1] > 0 || z[2] > 0) {
    int first = -1;
    if (res.length() > 0 && res[0] == toColor(c))
      first = 0;
    if (res.length() > 0 && res[0] == toColor(7 - c))
      first = 1;

    int am = 0;
    int poz = 0;
    if (first != -1 && am < z[first] && first != last) {
      poz = first;
      am = z[first];
    }

    if (am < z[0] && 0 != last) {
      poz = 0;
      am = z[0];
    }
    if (am < z[1] && 1 != last) {
      poz = 1;
      am = z[1];
    }

    if (poz == last || z[poz] == 0)
      return "";
    last = poz;
    z[poz]--;
    if (poz == 0)
      res += toColor(c);
    if (poz == 1)
      res += toColor(7 - c);
  }
  if (res[0] == res[res.length() - 1])
    return "";
  return res;
}
string solve() {
  bool posible = true;
  string res;
  if (tab[3] == 0 && tab[5] == 0 && tab[6] == 0)
    return solveOne();
  if (tab[1] == 0 && tab[6] == 0 && tab[2] == 0 && tab[5] == 0)
    return solveOneColor(4);
  if (tab[1] == 0 && tab[6] == 0 && tab[4] == 0 && tab[3] == 0)
    return solveOneColor(2);
  if (tab[4] == 0 && tab[3] == 0 && tab[2] == 0 && tab[5] == 0)
    return solveOneColor(1);

  int last = 0;
  if (tab[1] <= tab[6])
    posible = false;
  if (tab[2] <= tab[5])
    posible = false;
  if (tab[4] <= tab[3])
    posible = false;
  if (posible == false)
    return "";
  if (tab[6]) {
    res += toColor(1);
    last = 1;
  }
  for (int i = 0; i < tab[6]; ++i)
    res += toColor(6) + "" + toColor(1);
  if (tab[5]) {
    res += toColor(2);
    last = 2;
  }
  for (int i = 0; i < tab[5]; ++i)
    res += toColor(5) + "" + toColor(2);
  if (tab[3]) {
    res += toColor(4);
    last = 4;
  }
  for (int i = 0; i < tab[3]; ++i)
    res += toColor(3) + "" + toColor(4);
  int first;
  if (res.length() > 0 && res[0] == 'R')
    first = 0;
  if (res.length() > 0 && res[0] == 'Y')
    first = 1;
  if (res.length() > 0 && res[0] == 'B')
    first = 2;

  int z[3];
  z[0] = tab[1] - tab[6] - 1;
  z[1] = tab[2] - tab[5] - 1;
  z[2] = tab[4] - tab[3] - 1;
  while (z[0] > 0 || z[1] > 0 || z[2] > 0) {
    int am = 0;
    int poz = 0;
    if (am < z[first] && first != last) {
      poz = first;
      am = z[first];
    }
    if (am < z[0] && 0 != last) {
      poz = 0;
      am = z[0];
    }
    if (am < z[1] && 1 != last) {
      poz = 1;
      am = z[1];
    }
    if (am < z[2] && 2 != last) {
      poz = 2;
      am = z[2];
    }
    if (poz == last || z[poz] == 0)
      return "";
    last = poz;
    z[poz]--;
    if (poz == 0)
      res += toColor(1);
    if (poz == 1)
      res += toColor(2);
    if (poz == 2)
      res += toColor(4);
  }
  if (res[0] == res[res.length() - 1])
    return "";
  return res;
}
int toIntColor(char c) {
  if (c == 'R')
    return 1;
  if (c == 'Y')
    return 2;
  if (c == 'B')
    return 4;
  if (c == 'V')
    return 5;
  if (c == 'O')
    return 3;
  if (c == 'G')
    return 6;
}
void check(string s) {
  if (s.length() == 0)
    return;
  if (s.length() != n)
    printf("Zly rozmiar\n");

  char last = s[s.length() - 1];
  for (int i = 0; i < s.length(); ++i) {
    if (toIntColor(s[i]) & toIntColor(last))
      printf("Blad\n");
    last = s[i];
  }
}
void input() {

  cin >> n >> tab[1] >> tab[3] >> tab[2] >> tab[6] >> tab[4] >> tab[5];
}
int main() {
  int t;
  cin >> t;
  for (int k = 1; k <= t; ++k) {
    clear();
    input();
    printf("Case #%d: ", k);
    string res = solve();
    // check(res);

    if (res.length() == 0)
      printf("IMPOSSIBLE\n");
    else
      cout << res << "\n";
  }
}