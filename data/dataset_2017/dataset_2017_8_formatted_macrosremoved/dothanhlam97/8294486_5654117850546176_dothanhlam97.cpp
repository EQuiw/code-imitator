#include <bits/stdc++.h>

const int N = 1000;
typedef long long ll;

using namespace std;

vector<int> v;
int n;
int a[10];

int getmax(int x, int y, int z) { return max(x, max(y, z)); }

int main() {
  int query;
  scanf("%d", &query);
  for (int t = 1; t <= query; t++) {
    v.clear();
    scanf("%d", &n);
    for (int i = 1; i <= 6; ++i)
      scanf("%d", &a[i]);
    int x = a[1];
    int y = a[3];
    int z = a[5];
    int k, k1, k2;
    printf("Case #%d: ", t);

    int vmax = getmax(x, y, z);
    if (x == vmax) {
      k = 1, k1 = 3, k2 = 5;
    } else if (y = vmax) {
      k = 3, k1 = 1, k2 = 5;
    } else if (z == vmax)

    {
      k = 5, k1 = 1, k2 = 3;
    }
    for (int i = 1; i <= a[k]; ++i) {
      v.push_back(k);
      if (i <= a[k1])
        v.push_back(k1);
      if (i >= a[k] - a[k2] + 1)
        v.push_back(k2);
    }
    bool flag = 0;

    if (v[0] == v[(int)v.size() - 1]) {
      flag = 1;
    }
    for (int i = 1; i < v.size(); i++)
      if (v[i] == v[i - 1]) {
        flag = 1;
        break;
      }
    if (flag) {
      printf("IMPOSSIBLE\n");
      continue;
    }

    for (int i = 0; i < v.size(); i++) {
      if (v[i] == 1)
        printf("R");
      else if (v[i] == 3)
        printf("Y");
      else
        printf("B");
    }
    printf("\n");
  }
}
