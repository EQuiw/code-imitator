#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

double matrix[105][105];
struct XD {
  int a;
  double b;
  XD(int _a, double _b) : a(_a), b(_b) {}
};
struct Horse {
  int a, b;
  Horse(int _a, int _b) : a(_a), b(_b) {}
};
vector<XD> nG[105];
queue<int> q;
int inq[105], N;
double dis[105];
double SSSP(int st, int ed) {
  for (int i = 0; i < N; i++) {
    dis[i] = 1e15;
  }
  dis[st] = 0;
  q.push(st);
  int now;
  //  cout << "start\n";
  while (!q.empty()) {

    now = q.front();
    q.pop();
    inq[now] = 0;
    int nxt;
    double nlen;
    for (int i = 0; i < nG[now].size(); i++) {
      nxt = nG[now][i].a;
      nlen = nG[now][i].b;
      //  cout << "nxt: " << nxt;
      //  cout << " " << dis[nxt] ;
      //  cout << " " << dis[now] + nlen<<"\n";
      if (dis[now] + nlen + 1e-7 < dis[nxt]) {
        dis[nxt] = dis[now] + nlen;
        if (inq[nxt] == 0) {
          q.push(nxt);
          inq[nxt] = 1;
        }
      }
    }
  }
  return dis[ed];
}
int main() {

  // freopen("A-large.in","r",stdin);
  // freopen("ALout.txt","w",stdout);
  vector<Horse> v;
  int T;
  cin >> T;
  for (int ca = 1; ca <= T; ca++) {
    int Q;
    cin >> N >> Q;
    v.clear();
    int a, b;
    for (int i = 0; i < N; i++) {
      cin >> a >> b;
      v.push_back(Horse(a, b));
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> matrix[i][j];
      }
      matrix[i][i] = 0;
      for (int j = 0; j < N; j++) {
        if (matrix[i][j] < 0)
          matrix[i][j] = 1e10;
      }
    }
    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

          if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {

            matrix[i][j] = matrix[i][k] + matrix[k][j];
          }
        }
      }
    }
    /* for(int i=0;i<N;i++){

         for(int j=0;j<N;j++){

             cout << matrix[i][j] << " ";
         }
         cout << "\n";
     }*/
    for (int i = 0; i < N; i++)
      nG[i].clear();
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j)
          continue;
        if (matrix[i][j] <= v[i].a) {
          if (matrix[i][j] > 0) {
            nG[i].push_back(XD(j, matrix[i][j] / (double)v[i].b));
            // cout << "j: " << j << " " << matrix[i][j] / (double)v[i].b
            // <<"\n";
          }
        }
      }
    }
    cout << "Case #" << ca << ":";
    for (int i = 0; i < Q; i++) {

      cin >> a >> b;
      a--;
      b--;
      printf(" %.7lf", SSSP(a, b));
    }
    cout << "\n";
  }

  return 0;
}
/*
3
3 1
2 3
2 4
4 4
-1 1 -1
-1 -1 1
-1 -1 -1
*/
