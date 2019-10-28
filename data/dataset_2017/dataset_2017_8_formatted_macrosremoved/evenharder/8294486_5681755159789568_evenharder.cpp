#include <algorithm>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>

typedef std::pair<int, int> pi;
const int INF_INT = 1000000007;
const double INF_DOU = 3e11;

int data[103][103];
double rdata[103][103];

void floyd(int siz_, std::vector<pi> &horse) {
  for (int i = 0; i < siz_; i++) {
    for (int j = 0; j < siz_; j++) {
      if (i == j)
        data[i][j] = 0;
      if (data[i][j] == -1)
        data[i][j] = INF_INT;
    }
  }
  for (int k = 0; k < siz_; k++) {
    for (int i = 0; i < siz_; i++) {
      for (int j = 0; j < siz_; j++) {
        if (data[i][j] > data[i][k] + data[k][j]) {
          data[i][j] = data[i][k] + data[k][j];
        }
      }
    }
  }
  for (int i = 0; i < siz_; i++) {
    for (int j = 0; j < siz_; j++) {
      if (data[i][j] <= horse[i].first) {
        rdata[i][j] = data[i][j] / (double)horse[i].second;
      } else {
        rdata[i][j] = INF_DOU;
      }
    }
  }
  for (int k = 0; k < siz_; k++) {
    for (int i = 0; i < siz_; i++) {
      for (int j = 0; j < siz_; j++) {
        if (rdata[i][j] > rdata[i][k] + rdata[k][j]) {
          rdata[i][j] = rdata[i][k] + rdata[k][j];
        }
      }
    }
  }
}

void process(int TEST_CASE) {
  int n, q;
  std::vector<pi> horse;
  memset(data, 0, sizeof(data));
  memset(data, 0, sizeof(rdata));

  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    int e, s;
    scanf("%d%d", &e, &s);
    horse.push_back(std::make_pair(e, s));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &data[i][j]);
    }
  }
  floyd(n, horse);
  printf("Case #%d: ", TEST_CASE);
  for (int i = 0; i < q; i++) {
    int q1, q2;
    scanf("%d%d", &q1, &q2);
    printf("%.6lf ", rdata[q1 - 1][q2 - 1]);
  }
  puts("");
}

int main() {

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    process(i);
  }
}
