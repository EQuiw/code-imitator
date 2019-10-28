#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/B-small-attempt0.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);
  for (int ct = 1; ct <= tc; ct++) {
    printf("Case #%d: ", ct);
    char str[100];
    scanf("%s", str);
    bool valid = true;
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
      if (str[i] > str[i + 1]) {
        valid = false;
        int idx = i;
        int carry = 1;
        while (i >= 0 && carry) {
          if (str[i] != '0') {
            str[i]--;
            carry = 0;
          } else {
            str[i] = '9';
            carry = 1;
          }

          if (i > 0 && str[i - 1] > str[i]) {
            carry = 1;
            str[i] = '9';
          }

          i--;
        }

        for (int j = 0; j <= idx; j++) {
          if (j == 0 && str[j] == '0')
            continue;
          printf("%c", str[j]);
        }

        for (int j = idx + 1; j < len; j++) {
          printf("9");
        }
        printf("\n");
        break;
      }
    }

    if (valid) {
      printf("%s\n", str);
    }

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
