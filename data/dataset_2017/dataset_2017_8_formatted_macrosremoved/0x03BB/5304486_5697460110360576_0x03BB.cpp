#include <algorithm>
#include <iostream>
using namespace std;

bool inRange(int e, int d, int x) {
  return (!(e * d * 1.1 < x || e * d * 0.9 > x));
}

int main() {
  int T;
  cin >> T;
  double eps = 0.000001;
  for (int iCase = 1; iCase <= T; ++iCase) {
    int ans = 0;
    int n, p;
    cin >> n >> p;
    int a[100];
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    int b[100][100];
    int max_p = 0;
    int ptr[100];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j) {
        cin >> b[i][j];
        max_p = max(max_p, b[i][j] / a[i] + 1);
      }
      ptr[i] = 0;
      while (ptr[i] < p && b[i][ptr[i]] < a[i] * 0.9) {
        ++ptr[i];
      }
      sort(b[i], b[i] + p);
    }
    for (int i = 1; i <= max_p; ++i) {
      int ptr_backup[100];
      while (true) {
        bool f = false, canDo = true;
        for (int j = 0; j < n; ++j) {
          ptr_backup[j] = ptr[j];
          if (ptr[j] >= p) {
            f = true;
            break;
          }
          while (ptr[j] < p && b[j][ptr[j]] < a[j] * i * 0.9) {
            ++ptr[j];
          }
          if (ptr[j] < p && !(b[j][ptr[j]] > a[j] * i * 1.1)) {
            ++ptr[j];
          } else {
            canDo = false;
          }
        }
        if (f) {
          break;
        }
        if (canDo) {
          ++ans;
        } else {
          for (int k = 0; k <= n; ++k) {
            ptr[k] = ptr_backup[k];
          }
          break;
        }
      }
    }
    cout << "Case #" << iCase << ": " << ans << endl;
  }
}
