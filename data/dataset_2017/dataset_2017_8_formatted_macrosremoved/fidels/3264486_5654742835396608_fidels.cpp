#include <cstring>
#include <iostream>
using namespace std;

int l[1024], r[1024];
bool n[1024];

int main() {
  int T, t, N, K, i, k, best;

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> N >> K;

    memset(n, false, sizeof(n));
    n[0] = n[N + 1] = true;
    for (k = 0; k < K; k++) {
      for (i = 1; i <= N; i++) {
        if (n[i - 1])
          l[i] = 0;
        else
          l[i] = l[i - 1] + 1;
      }
      for (i = N; i >= 0; i--) {
        if (n[i + 1])
          r[i] = 0;
        else
          r[i] = r[i + 1] + 1;
      }

      best = -1;
      for (i = 1; i <= N; i++)
        if (!n[i]) {
          if (best == -1 || min(l[i], r[i]) > min(l[best], r[best]) ||
              (min(l[i], r[i]) == min(l[best], r[best]) &&
               max(l[i], r[i]) > max(l[best], r[best])))
            best = i;
        }
      n[best] = true;
    }
    cout << "Case #" << t << ": " << max(l[best], r[best]) << ' '
         << min(l[best], r[best]) << endl;
  }

  return 0;
}
