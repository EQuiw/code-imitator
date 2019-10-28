#include <cstdio>
#include <cstring>
using namespace std;
const int MAX = 25 + 10;
char arr[MAX][MAX];
int main() {
  int TN;
  scanf("%d", &TN);
  for (int casen = 1; casen <= TN; casen++) {
    printf("Case #%d:\n", casen);
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
      scanf("%s", arr[i]);
    }
    for (int i = 0; i < n; i++) {
      char first = '?';
      char now = '?';
      for (int j = 0; j < m; j++) {
        if (first == '?' && arr[i][j] != '?')
          first = arr[i][j];
        else if (arr[i][j] != '?')
          now = arr[i][j];
        arr[i][j] = now;
      }
      for (int j = 0; j < m && arr[i][j] == '?'; j++) {
        arr[i][j] = first;
      }
    }
    int last = -1;
    for (int i = 0; i < n; i++) {
      if (arr[i][0] == '?') {
        int pick = -1;
        for (int j = i + 1; j < n; j++) {
          if (arr[j][0] != '?') {
            pick = j;
            break;
          }
        }
        if (pick == -1)
          break;
        strcpy(arr[i], arr[pick]);
      } else
        last = i;
    }
    for (int i = last + 1; i < n; i++) {
      strcpy(arr[i], arr[last]);
    }
    for (int i = 0; i < n; i++) {
      printf("%s\n", arr[i]);
    }
  }
  return 0;
}
