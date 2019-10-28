#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <stdarg.h>
#include <string>
#include <vector>

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

char opposite(char c) {
  if (c == '-')
    return '+';
  else
    return '-';
}

vector<pair<int, int>> starting;
vector<char> chars;
vector<string> pole;

bool dynamika(int znak_cislo, vector<pair<int, int>> &dolne,
              vector<pair<int, int>> &horne, int sucet) {

  if (sucet > pole.size() * pole[0].size()) {
    cout << pole.size() * pole[0].size() << endl;
    return false;
  }
  if (znak_cislo == starting.size()) {
    cout << "trying to testing" << endl;
    if (sucet < pole.size() * pole[0].size()) {
      return false;
    }
    cout << "testing" << endl;
    vector<vector<char>> pole2 =
        vector<vector<char>>(pole.size(), vector<char>(pole[0].size(), '?'));
    for (int i = 0; i < (horne.size()); i++) {
      cout << chars[i] << endl;
      for (int x = dolne[i].first; x < horne[i].first; x++) {
        for (int y = dolne[i].second; y < horne[i].second; y++) {
          cout << x << " " << y << endl;
          cout << pole2[y][x] << endl;
          if (pole2[y][x] == '?') {
            pole2[y][x] = chars[i];
          } else {
            return false;
          }
        }
      }
    }
    // cout<<"end testing"<<endl;
    for (int i = 0; i < (pole2[0].size()); i++) {
      for (int j = 0; j < (pole2.size()); j++) {
        cout << pole2[j][i];
      }
      cout << endl;
    }
    return true;
  } else {
    for (int x1 = 0; x1 < starting[znak_cislo].first + 1; x1++) {
      for (int y1 = 0; y1 < (starting[znak_cislo].second + 1); y1++) {
        dolne.push_back(make_pair(x1, y1));
        for (int x2 = starting[znak_cislo].first + 1; x2 <= pole[0].size();
             x2++) {
          for (int y2 = starting[znak_cislo].second + 1; y2 <= pole.size();
               y2++) {
            horne.push_back(make_pair(x2, y2));
            int vel = (x2 - x1) * (y2 - y1);
            if (dynamika(znak_cislo + 1, dolne, horne, sucet + vel)) {
              return true;
            }
            horne.pop_back();
          }
        }
        dolne.pop_back();
      }
    }
  }
}

void solve(vector<string> pole) {

  for (int i = 0; i < pole[0].size(); i++) {
    char c_last = '?';
    bool has = false;
    for (int j = 0; j < pole.size(); j++) {
      if (pole[j][i] != '?')
        c_last = pole[j][i];
      pole[j][i] = c_last;
    }

    c_last = '?';
    for (int j = pole.size() - 1; j >= 0; j--) {
      if (pole[j][i] != '?') {
        c_last = pole[j][i];
        has = true;
      }
      pole[j][i] = c_last;
    }

    if (!has && i > 0) {
      for (int j = 0; j < pole.size(); j++) {
        pole[j][i] = pole[j][i - 1];
      }
    }
  }

  for (int i = pole[0].size() - 2; i >= 0; i--) {
    char c_last = '?';
    bool has = false;
    for (int j = pole.size() - 1; j >= 0; j--) {
      if (pole[j][i] != '?') {
        c_last = pole[j][i];
        has = true;
      }
      pole[j][i] = c_last;
    }

    if (!has) {
      for (int j = 0; j < pole.size(); j++) {
        pole[j][i] = pole[j][i + 1];
      }
    }
  }

  for (int i = 0; i < (pole.size()); i++) {
    for (int j = 0; j < (pole[0].size()); j++) {
      cout << pole[i][j];
    }
    cout << endl;
  }
}

int main() {
  // string m;
  int t, k, m;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    chars.clear();
    cout << "Case #" << (tt + 1) << ":" << endl;
    cin >> m >> k;
    pole = vector<string>(m);
    vector<pair<int, int>> startings;
    for (int i = 0; i < (m); i++) {
      cin >> pole[i];
      for (int j = 0; j < (k); j++) {
        if (pole[i][j] != '?') {
          startings.push_back(make_pair(i, j));
          chars.push_back(pole[i][j]);
        }
      }
    }

    solve(pole);
  }
}
