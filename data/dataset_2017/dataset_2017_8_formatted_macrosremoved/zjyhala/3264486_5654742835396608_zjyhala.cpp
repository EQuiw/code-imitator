#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
long long n, k, sm, la, nusm, nula, t[5], tsm, tla, ans;
int ca;
void init() {
  cin >> n >> k;
  sm = n, la = n + 1;
  nusm = 1;
  nula = 0;
}
long long maxll(long long a, long long b) { return a > b ? a : b; }

long long minll(long long a, long long b) { return a < b ? a : b; }
void getnum(long long a, long long &t1, long long &t2) {
  if (a % 2 == 1)
    t1 = t2 = a / 2;
  else
    t1 = maxll(0, a / 2 - 1), t2 = a / 2;
}

void sov() {
  printf("Case #%d: ", ca);

  while (1) {
    if (k <= nula) {
      ans = la;
      break;
    }
    if (k <= nusm + nula) {
      ans = sm;
      break;
    }
    k -= (nula + nusm);
    getnum(sm, t[1], t[2]);
    getnum(la, t[3], t[4]);
    //        for(int i =1; i <= 4; i++)
    //            cout <<"t["<<i<<"] =  "<<t[i]<<endl;
    sm = minll(minll(t[1], t[2]), minll(t[3], t[4]));
    la = maxll(maxll(t[1], t[2]), maxll(t[3], t[4]));
    tsm = tla = 0;
    for (int i = 1; i <= 4; i++) {
      if (t[i] == sm && i < 3)
        tsm += nusm;
      if (t[i] == sm && i >= 3)
        tsm += nula;
      if (t[i] == la && i >= 3)
        tla += nula;
      if (t[i] == la && i < 3)
        tla += nusm;
    }
    swap(nula, tla);
    swap(nusm, tsm);
    // cout << "sm = "<<nusm <<"  la = "<<nula<<endl;
  }
  getnum(ans, t[1], t[2]);
  if (t[1] < t[2])
    swap(t[1], t[2]);
  cout << t[1] << " " << t[2] << endl;
}

int main() {
  int T;
  freopen("inn.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &T);
  for (ca = 1; ca <= T; ca++) {
    init();
    sov();
  }
}
