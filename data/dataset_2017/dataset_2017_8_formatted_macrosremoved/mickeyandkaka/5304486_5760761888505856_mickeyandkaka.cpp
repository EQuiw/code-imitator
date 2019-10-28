#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef pair<int, int> PII;

vector<string> split(const string &s, char c) {
  vector<string> v;
  stringstream ss(s);
  string x;
  while (getline(ss, x, c))
    v.push_back(x);
  return v;
}
void err(vector<string>::iterator it) {}
template <typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
  cerr << it->substr((*it)[0] == ' ', it->length()) << " = " << a << ", ";
  err(++it, args...);
}
const int INF = 0x3f3f3f3f;

int T;

const int N = 111;
char s[N][N];
int r, c;
bool flag[33];

int main() {
  int cas = 1;
  scanf("%d", &T);

  while (T--) {
    printf("Case #%d: \n", cas++);

    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; ++i) {
      scanf("%s", s[i]);
    }
    memset(flag, false, sizeof(flag));

    for (int i = 0; i < r; i++) {
      int j = 0;
      while (j < c && s[i][j] == '?')
        j++;
      if (j < c) {
        for (int k = 0; k < j; k++)
          s[i][k] = s[i][j];
        for (int k = j + 1; k < c; k++)
          if (s[i][k] == '?')
            s[i][k] = s[i][k - 1];
      } else
        flag[i] = 1;
    }

    int p = 0;
    while (flag[p])
      p++;
    for (int j = 0; j < p; j++)
      strcpy(s[j], s[p]);

    for (int j = p + 1; j < r; j++)
      if (flag[j])
        strcpy(s[j], s[j - 1]);

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++)
        printf("%c", s[i][j]);
      puts("");
    }
  }

  return 0;
}
