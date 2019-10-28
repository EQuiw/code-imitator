#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef long long ll;
typedef double db;
const int N = 1005;

int occupy[N], Left[N], Right[N];
int Min[N], Max[N];

int main() {

  int T;
  scanf("%d", &T);
  for (int ca = 1; ca <= T; ca++) {
    int n, k;
    scanf("%d%d", &n, &k);
    occupy[0] = occupy[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
      occupy[i] = 0, Left[i] = 0, Right[i] = n + 1;
      Min[i] = min(i - Left[i], Right[i] - i);
      Max[i] = max(i - Left[i], Right[i] - i);
    }
    int ch;
    for (int i = 0; i < k; i++) {
      ch = -1;
      for (int j = 1; j <= n; j++) {
        if (!occupy[j]) {
          if (ch == -1 || Min[j] > Min[ch] ||
              Min[j] == Min[ch] && Max[j] > Max[ch]) {
            ch = j;
          }
        }
      }
      occupy[ch] = 1;
      for (int j = ch - 1; !occupy[j]; j--) {
        Right[j] = ch;
        Min[j] = min(j - Left[j], Right[j] - j);
        Max[j] = max(j - Left[j], Right[j] - j);
      }
      for (int j = ch + 1; !occupy[j]; j++) {
        Left[j] = ch;
        Min[j] = min(j - Left[j], Right[j] - j);
        Max[j] = max(j - Left[j], Right[j] - j);
      }
      //            printf("ch:  %d\n", ch);
    }
    printf("Case #%d: %d %d\n", ca, Max[ch] - 1, Min[ch] - 1);
  }
  return 0;
}
