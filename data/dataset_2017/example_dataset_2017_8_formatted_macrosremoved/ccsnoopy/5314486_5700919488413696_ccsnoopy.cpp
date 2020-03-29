#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/A-small-attempt0.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    int n, p;
    scanf("%d", &n);
    scanf("%d", &p);
    int arr[120];

    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
    }

    if (p == 2) {
      int tot = 0;
      int ganjil = 0;
      for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
          tot++;
        else
          ganjil++;
      }
      printf("Case #%d: %d\n", ct, tot + ((ganjil + 1) / 2));
    } else if (p == 3) {
      int a[4];
      memset(a, 0, sizeof(a));
      for (int i = 0; i < n; i++) {
        a[arr[i] % 3]++;
      }
      int tot =
          a[0] + min(a[1], a[2]) + (max(a[1], a[2]) - min(a[1], a[2]) + 2) / 3;
      printf("Case #%d: %d\n", ct, tot);
    }

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
