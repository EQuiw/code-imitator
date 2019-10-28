#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/A-small-attempt1.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    int r, c;
    scanf("%d", &r);
    scanf("%d", &c);
    string str[30];
    string ret[30];
    for (int i = 0; i < r; i++) {
      cin >> str[i];
      // if(ct == 74){
      // 	cerr << str[i] << endl;
      // }
      ret[i] = str[i];
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (str[i][j] == '?')
          continue;
        int minx, maxx;
        minx = maxx = i;
        int miny, maxy;
        miny = maxy = j;
        while (miny > 0 && str[i][miny - 1] == '?' && ret[i][miny - 1] == '?')
          miny--;
        while (maxy < c - 1 && str[i][maxy + 1] == '?' &&
               ret[i][maxy + 1] == '?')
          maxy++;
        while (minx > 0) {
          bool valid = true;
          for (int k = miny; k <= maxy; k++) {
            if (str[minx - 1][k] != '?' || ret[minx - 1][k] != '?') {
              valid = false;
              break;
            }
          }
          if (valid) {
            minx--;
          } else
            break;
        }
        bool adabawah = false;
        for (int k = i + 1; k < r; k++) {
          for (int l = 0; l < c; l++) {
            if (str[k][l] != '?') {
              adabawah = true;
              break;
            }
          }
        }
        if (!adabawah) {
          maxx = r - 1;
        }

        for (int k = minx; k <= maxx; k++) {
          for (int l = miny; l <= maxy; l++) {
            ret[k][l] = str[i][j];
          }
        }
      }
    }

    printf("Case #%d: \n", ct);
    for (int i = 0; i < r; i++) {
      cout << ret[i] << "\n";
    }

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
