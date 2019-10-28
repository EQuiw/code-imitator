#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

int T;
int N, P;
long long R[60];
long long Q[60][60];
long long Qu[60][60], Qd[60][60];

long long getu(long long a) { return a * 11 / 10; }
long long getd(long long a) { return (a * 9 + 9) / 10; }

long long bsmax(long long rn, long long qn) {
  long long l = 0, r = qn * 2;
  while (l < r) {
    long long mid = (l + r + 1) / 2;
    // printf("l=%d  r=%d mid=%d getd=%d\n", l, r, mid, getd(rn*mid));
    if (getd(rn * mid) <= qn)
      l = mid;
    else
      r = mid - 1;
  }
  return l;
}

long long bsmin(long long rn, long long qn) {
  long long l = 0, r = qn * 2;
  while (l < r) {
    long long mid = (l + r) / 2;
    // printf("l=%d  r=%d mid=%d\n", l, r, mid);
    if (getu(rn * mid) < qn)
      l = mid + 1;
    else
      r = mid;
  }
  return l;
}
bool valid(long long rn, long long qn, long long n) {
  // std::cout << rn << " " << qn << " " << n << std::endl;
  // std::cout << "(" << getu(rn*n) << ", " << getd(rn*n) << ")" << std::endl;
  return getu(rn * n) >= qn && getd(rn * n) <= qn;
}

int main() {
  freopen("B-small-attempt5.in", "r", stdin);
  freopen("B-small-attempt5.out", "w", stdout);
  std::cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    std::cin >> N >> P;
    for (int i = 0; i < N; i++) {
      std::cin >> R[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        std::cin >> Q[i][j];
        Qu[i][j] = bsmax(R[i], Q[i][j]);
        Qd[i][j] = bsmin(R[i], Q[i][j]);
        /*if(Qu[i][j] >= Qd[i][j]) {
                if(!valid(R[i], Q[i][j], Qu[i][j]) || !valid(R[i], Q[i][j],
        Qu[i][j])) { std::cerr << "invalid at " << R[i] << ", " << Q[i][j] <<
        std::endl;
                }
        }*/
        // std::cout << Q[i][j] << ": " << Qu[i][j] << " " << Qd[i][j] <<
        // std::endl;  printf("%d: %d %d\n", Q[i][j], Qu[i][j], Qd[i][j]);
      }
    }
    int ans = 0;
    if (N == 1) {
      for (int j = 0; j < P; j++) {
        if (Qu[0][j] < Qd[0][j]) {
          continue;
        }
        ans++;
      }
    } else if (N == 2) {
      std::vector<int> lst;
      for (int i = 0; i < P; i++) {
        lst.push_back(i);
      }
      do {
        int nans = 0;
        for (int i = 0; i < P; i++) {
          int j1, j2;
          j1 = i;
          j2 = lst[i];
          if (valid(R[0], Q[0][j1], Qu[0][j1]) &&
              valid(R[1], Q[1][j2], Qu[0][j1])) {
            nans++;
          } else if (valid(R[0], Q[0][j1], Qd[0][j1]) &&
                     valid(R[1], Q[1][j2], Qd[0][j1])) {
            nans++;
          } else if (valid(R[0], Q[0][j1], Qu[1][j2]) &&
                     valid(R[1], Q[1][j2], Qu[1][j2])) {
            nans++;
          } else if (valid(R[0], Q[0][j1], Qd[1][j2]) &&
                     valid(R[1], Q[1][j2], Qd[1][j2])) {
            nans++;
          }
        }
        if (nans > ans)
          ans = nans;
      } while (std::next_permutation(lst.begin(), lst.end()));
      /*for(int j1=0; j1<P; j1++) {
              for(int j2=0; j2<P; j2++) {
                      if(Qu[0][j1] < Qd[0][j1] || Qu[1][j2] <  Qd[1][j2]) {
                              continue;
                      }
                      if(Qd[0][j1] > Qu[1][j2] || Qd[1][j2] > Qu[0][j1]) {
                              continue;
                      }
                      ans++;
                      if(valid(R[0], Q[0][j1], Qu[0][j1]) && valid(R[1],
      Q[1][j2], Qu[0][j1])) { ans++;
                      }
                      else if(valid(R[0], Q[0][j1], Qd[0][j1]) && valid(R[1],
      Q[1][j2], Qd[0][j1])) { ans++;
                      }
                      else if(valid(R[0], Q[0][j1], Qu[1][j2]) && valid(R[1],
      Q[1][j2], Qu[1][j2])) { ans++;
                      }
                      else if(valid(R[0], Q[0][j1], Qd[1][j2]) && valid(R[1],
      Q[1][j2], Qd[1][j2])) { ans++;
                      }
              }
      }*/
    } else {
      std::cout << "?????" << std::endl;
    }
    std::cout << "Case #" << tc << ": " << ans << std::endl;
  }
}
