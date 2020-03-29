#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/B-small-attempt2.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out3.txt", "w", stdout);
}
int n, c, m;

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    scanf("%d", &n);
    scanf("%d", &c);
    scanf("%d", &m);

    int jml[2][1010];
    memset(jml, 0, sizeof(jml));
    for (int i = 0; i < m; i++) {
      int pos, buyer;
      scanf("%d", &pos);
      scanf("%d", &buyer);
      buyer--;
      pos--;
      jml[buyer][pos]++;
    }

    int prev = 0;
    for (int i = 0; i < n; i++) {

      int z = jml[0][i];
      for (int k = 0; k < z; k++) {
        int mxidx = (i == n - 1) ? n - 2 : (i + 1);
        bool found = false;
        for (int j = 0; j < n; j++) {
          if (i == j)
            continue;
          if (jml[1][j] > 0 && jml[1][j] > jml[1][mxidx])
            mxidx = j;
        }
        if (jml[1][mxidx] == 0)
          break;
        else {
          jml[1][mxidx]--;
          jml[0][i]--;
          prev++;
        }
      }
    }
    int ctr = 0;
    int prv = prev;
    // if(n > 2){
    // for(int i = 0;i < n;i++){
    // 	if(jml[0][i] && jml[1][i]){
    // 		ctr++;
    // 		int tt = min(prv, min(jml[0][i], jml[1][i]));
    // 		prv -= tt;
    // 		jml[0][i] -= tt;
    // 		jml[1][i] -= tt;
    // 	}
    // }
    // }

    int promote = 0;

    prev += jml[0][0] + jml[1][0];
    for (int i = 1; i < n; i++) {
      if (jml[0][i] && jml[1][i]) {
        int t = min(jml[0][i], jml[1][i]);
        promote += min(jml[0][i], jml[1][i]);
        jml[0][i] -= t;
        jml[1][i] -= t;
        // cerr << "promote : " << jml[0][i] << " " << jml[1][i] << endl;
      }
      prev += max(jml[0][i], jml[1][i]);
    }

    int tot = prev + promote;

    printf("Case #%d: %d %d\n", ct, tot, promote);

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
