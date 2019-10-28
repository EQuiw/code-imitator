#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <vector>

#define MAX_CITIES 100
#define MAX_PAIRS 100
#define MAX_DOUBLE 100000000000000

int N; // cities
int Q; // queries
long long E[MAX_CITIES];
long long S[MAX_CITIES];

long long D[MAX_CITIES][MAX_CITIES];

long long U[100];
long long K[100];

using namespace std;

vector<pair<pair<int, int>, double>> times;

map<int, vector<pair<int, double>>> hours;

map<int, double> ansMap;

double getMin(int n);
// long long LEN[100];

void solve(void);

int main(int argc, const char *argv[]) {
  freopen("/Volumes/4HOPE/Dropbox/17Todai/CodeJam/R1B-2017-C/in.txt", "r",
          stdin);
  freopen("/Volumes/4HOPE/Dropbox/17Todai/CodeJam/R1B-2017-C/out.txt", "w",
          stdout);
  int t;
  scanf("%d", &t);
  for (int cnt = 0; cnt < t; cnt++) {
    scanf("%d %d", &N, &Q);
    for (int c_i = 0; c_i < N; c_i++) {
      scanf("%lld %lld", &E[c_i], &S[c_i]);
    }
    for (int y = 0; y < N; y++) {
      for (int x = 0; x < N; x++) {
        scanf("%lld", &D[y][x]);
      }
    }
    for (int k = 0; k < Q; k++) {
      scanf("%lld %lld", &U[k], &K[k]);
    }
    printf("Case #%d: ", cnt + 1);
    solve();
  }
  return 0;
}

void solve(void) {
  long long len = 0;
  hours.clear();
  ansMap.clear();
  for (int s = 0; s < N; s++) {
    len = 0;
    for (int e = s + 1; e < N; e++) {
      len += D[e - 1][e];
      if (len > E[s]) {
        break;
      }
      //            times.push_back(make_pair(make_pair(s,e),(double)len/(double)S[s]));
      hours[e].push_back(make_pair(s, (double)len / (double)S[s]));
    }
  }
  printf("%f\n", getMin(N - 1));
}
// nにたどり着ける経路のうち、最短のものを探す
double getMin(int n) {
  if (n == 0) {
    return 0.0;
  }
  auto iter = ansMap.find(n);
  if (iter != ansMap.end()) {
    return ansMap[n];
  }
  vector<pair<int, double>> *vec = &hours[n];
  double nowMin = MAX_DOUBLE;
  for (pair<int, double> s : *vec) {
    double nowTarget = getMin(s.first) + s.second;
    if (nowTarget < nowMin) {
      nowMin = nowTarget;
    }
  }
  ansMap[n] = nowMin;
  return nowMin;
}
