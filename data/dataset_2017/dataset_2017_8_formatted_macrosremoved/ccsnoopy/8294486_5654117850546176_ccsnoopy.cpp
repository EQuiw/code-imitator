#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/B-small-attempt1.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out1.txt", "w", stdout);
}

void pr(int idx) {
  switch (idx) {
  case 0:
    printf("R");
    break;
  case 1:
    printf("O");
    break;
  case 2:
    printf("Y");
    break;
  case 3:
    printf("G");
    break;
  case 4:
    printf("B");
    break;
  case 5:
    printf("V");
    break;
  }
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    int n;
    scanf("%d", &n);
    int arr[10];
    printf("Case #%d: ", ct);
    for (int i = 0; i < 6; i++) {
      scanf("%d", &arr[i]);
    }
    bool imp = false;
    for (int i = 0; i < 6; i++) {
      if (arr[i] * 2 > n) {
        imp = true;
        printf("IMPOSSIBLE\n");
        break;
      }
    }

    if (imp)
      continue;

    int maxidx = 0;
    for (int i = 0; i < 6; i++) {
      if (arr[maxidx] < arr[i])
        maxidx = i;
    }
    bool palinggede = true;
    int last = maxidx;
    pr(maxidx);
    arr[maxidx]--;
    int first = last;

    while (true) {
      bool ada = false;
      for (int i = 0; i < 6; i++) {
        if (arr[i] > 0)
          ada = true;
      }

      if (!ada)
        break;

      if (last == 0) {
        if (arr[2] > arr[4]) {
          last = 2;
        } else if (arr[2] < arr[4]) {
          last = 4;
        } else {
          if (first == 2) {
            last = 2;
          } else
            last = 4;
        }
      } else if (last == 2) {
        if (arr[0] > arr[4]) {
          last = 0;
        } else if (arr[0] < arr[4]) {
          last = 4;
        } else {
          if (first == 0) {
            last = 0;
          } else
            last = 4;
        }
      } else {
        if (arr[0] > arr[2]) {
          last = 0;
        } else if (arr[0] < arr[2]) {
          last = 2;
        } else {
          if (first == 0) {
            last = 0;
          } else
            last = 2;
        }
      }
      pr(last);
      arr[last]--;
    }
    printf("\n");

    cerr << "Test " << ct << " done \n";
    if (first == last) {
      cerr << "last equals first\n";
    }
  }
  return 0;
}
