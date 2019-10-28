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
  char str[1010];
  int k;

  for (int ct = 1; ct <= tc; ct++) {
    scanf("%s", str);
    scanf("%d", &k);
    int ret = 0;
    int len = strlen(str);

    for (int j = 0; j < len; j++) {
      if (str[j] == '-') {
        if (j + k > len) {
          ret = -1;
          break;
        }
        for (int l = 0; l < k; l++) {
          if (str[l + j] == '+')
            str[l + j] = '-';
          else
            str[l + j] = '+';
        }
        ret++;
        // printf("%s\n", str);
      }
    }

    printf("Case #%d: ", ct);

    if (ret == -1) {
      printf("IMPOSSIBLE\n");
    } else {
      printf("%d\n", ret);
    }
    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
