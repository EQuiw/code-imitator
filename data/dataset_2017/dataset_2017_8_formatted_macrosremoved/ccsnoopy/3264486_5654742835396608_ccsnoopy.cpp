#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/C-small-1-attempt0.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);
  for (int ct = 1; ct <= tc; ct++) {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);
    priority_queue<int> pq;
    pq.push(n);

    printf("Case #%d: ", ct);

    while (k--) {
      int top = pq.top();
      pq.pop();
      int mid = top - 1;
      int l, r;
      l = mid / 2;
      r = (mid + 1) / 2;
      if (k == 0) {
        printf("%d %d\n", r, l);
      }
      if (l) {
        pq.push(l);
      }

      if (r) {
        pq.push(r);
      }
    }

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
