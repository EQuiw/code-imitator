#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/C-small-attempt3.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out2.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);
  char str[10][70];

  for (int ctr = 1; ctr <= tc; ctr++) {
    int r, c;
    map<ii, int> mp;
    int ct = 0;
    scanf("%d", &r);
    scanf("%d", &c);
    for (int i = 0; i < r; i++) {
      scanf("%s", str[i]);
    }
    bool bs[2][120];
    memset(bs, true, sizeof(bs));
    bool possible = true;
    set<ii> s;
    vii v;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (str[i][j] == '|' || str[i][j] == '-') {
          mp[ii(i, j)] = ct++;
          int tmpi, tmpj;
          tmpi = i;
          tmpj = j;
          bool valid = true;
          while (true) {
            tmpi--;
            if (tmpi >= 0) {
              if (str[tmpi][j] == '#')
                break;
              if (str[tmpi][j] == '|' || str[tmpi][j] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }
          tmpi = i;
          while (true) {
            tmpi++;
            if (tmpi < r) {
              if (str[tmpi][j] == '#')
                break;
              if (str[tmpi][j] == '|' || str[tmpi][j] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }

          if (!valid) {
            bs[0][mp[ii(i, j)]] = false;
          }

          valid = true;

          while (true) {
            tmpj--;
            if (tmpj >= 0) {
              if (str[i][tmpj] == '#')
                break;
              if (str[i][tmpj] == '|' || str[i][tmpj] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }
          tmpj = j;
          while (true) {
            tmpj++;
            if (tmpj < c) {
              if (str[i][tmpj] == '#')
                break;
              if (str[i][tmpj] == '|' || str[i][tmpj] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }

          if (!valid) {
            bs[1][mp[ii(i, j)]] = false;
          }

          if (!bs[0][mp[ii(i, j)]] && !bs[1][mp[ii(i, j)]])
            possible = false;
        }
      }
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (str[i][j] == '.') {
          v.push_back(ii(i, j));
          bool found = false;
          for (int k = i + 1; k < r; k++) {
            if (str[k][j] == '#')
              break;
            if (str[k][j] == '-' || str[k][j] == '|') {
              if (bs[0][mp[ii(k, j)]]) {

                if (bs[1][mp[ii(k, j)]])
                  s.insert(ii(k, j));
                found = true;
              }
            }
          }
          for (int k = i - 1; k >= 0; k--) {
            if (str[k][j] == '#')
              break;
            if (str[k][j] == '-' || str[k][j] == '|') {
              if (bs[0][mp[ii(k, j)]]) {
                found = true;
                if (bs[1][mp[ii(k, j)]])
                  s.insert(ii(k, j));
              }
            }
          }

          for (int k = j + 1; k < c; k++) {
            if (str[i][k] == '#')
              break;
            if (str[i][k] == '-' || str[i][k] == '|') {
              if (bs[1][mp[ii(i, k)]]) {
                found = true;
                if (bs[0][mp[ii(i, k)]])
                  s.insert(ii(i, k));
              }
            }
          }

          for (int k = j - 1; k >= 0; k--) {
            if (str[i][k] == '#')
              break;
            if (str[i][k] == '-' || str[i][k] == '|') {
              if (bs[1][mp[ii(i, k)]]) {
                if (bs[0][mp[ii(i, k)]])
                  s.insert(ii(i, k));
                found = true;
              }
            }
          }

          if (!found) {
            possible = false;
          }
        }
      }
    }

    for (map<ii, int>::iterator it = mp.begin(); it != mp.end(); it++) {
      ii xy = it->first;
      int x = xy.first;
      int y = xy.second;

      if (bs[0][it->second] && !bs[1][it->second]) {
        str[x][y] = '|';
      } else if (!bs[0][it->second] && bs[1][it->second]) {
        str[x][y] = '-';
      }
    }

    cerr << "jml : " << (int)s.size() << endl;
    if (possible) {
      bool found = false;
      for (ll i = 0; i < (1LL << (int)s.size()); i++) {
        int C = 0;
        bool bs = true;
        for (set<ii>::iterator it = s.begin(); it != s.end(); it++) {
          ii xy = *it;
          int x = xy.first;
          int y = xy.second;
          if (i & (1LL << C)) {
            str[x][y] = '-';
          } else {
            str[x][y] = '|';
          }
        }
        for (int j = 0; j < (int)v.size(); j++) {
          int x = v[j].first;
          int y = v[j].second;
          bool f = false;
          for (int k = x - 1; k >= 0; k--) {
            if (str[k][y] == '#')
              break;
            if (str[k][y] == '|')
              f = true;
          }

          for (int k = x + 1; k < r; k++) {
            if (str[k][y] == '#')
              break;
            if (str[k][y] == '|')
              f = true;
          }

          for (int k = y - 1; k >= 0; k--) {
            if (str[x][k] == '#')
              break;
            if (str[x][k] == '-')
              f = true;
          }

          for (int k = y + 1; k < c; k++) {
            if (str[x][k] == '#')
              break;
            if (str[x][k] == '-')
              f = true;
          }
          if (!f) {
            bs = false;
            break;
          }
        }
        if (bs) {
          found = true;
          break;
        }
      }
      if (!found)
        possible = false;
    }

    printf("Case #%d: %s\n", ctr, possible ? "POSSIBLE" : "IMPOSSIBLE");
    if (possible)
      for (int i = 0; i < r; i++)
        printf("%s\n", str[i]);
    cerr << "Test " << ctr << " done \n";
  }
  return 0;
}
