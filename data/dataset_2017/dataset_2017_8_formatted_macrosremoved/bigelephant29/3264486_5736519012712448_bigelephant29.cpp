#include <cstdio>
#include <cstring>
using namespace std;
const int MAX = 1000 + 10;
char arr[MAX];
int main() {
  int TN;
  scanf("%d", &TN);
  for (int casen = 1; casen <= TN; casen++) {
    printf("Case #%d: ", casen);
    int k, cnt = 0;
    scanf("%s %d", arr, &k);
    int len = strlen(arr);
    for (int i = 0; i < len - k + 1; i++) {
      if (arr[i] == '-') {
        cnt++;
        for (int j = 0; j < k; j++) {
          if (arr[i + j] == '-')
            arr[i + j] = '+';
          else
            arr[i + j] = '-';
        }
      }
    }
    bool check = true;
    for (int i = 0; i < len; i++) {
      check &= arr[i] == '+';
    }
    if (check)
      printf("%d\n", cnt);
    else
      puts("IMPOSSIBLE");
  }
  return 0;
}
