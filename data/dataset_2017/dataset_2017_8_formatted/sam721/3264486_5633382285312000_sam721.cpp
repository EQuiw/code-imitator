#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define VI vector<int>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
using namespace std;
char A[20];
int n;
int main() {
  int t;
  scanf("%d", &t);
  for (int c = 1; c <= t; c++) {
    scanf("%s", A);
    printf("Case #%d: ", c);
    int n = strlen(A);
    for (int i = 0; i < n - 1; i++) {
      if (A[i] > A[i + 1]) {
        int j = i;
        while (j >= 0) {
          A[j]--;
          if (A[j] < '0')
            A[j] = '9';
          else
            break;
          j--;
        }
        j = i + 1;
        while (j < n)
          A[j++] = '9';
        i = max(i - 2, -1);
      }
    }
    int p = 0;
    while (p < n && A[p] == '0')
      p++;
    for (; p < n; p++)
      printf("%c", A[p]);
    printf("\n");
  }
  return 0;
}