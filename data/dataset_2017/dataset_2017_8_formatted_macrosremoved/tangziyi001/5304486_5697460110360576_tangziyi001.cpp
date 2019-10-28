/*
 *
 *	Created by Ziyi Tang
 *
 */

//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef vector<vpi> vvpi;
const int INF = 0x3f3f3f;
const ll INFL = (ll)1E18;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int n, p;
vi ins;
vi need;
vi pac1;
vi pac2;
int main() {
  int test;
  cin >> test;
  for (int t = (1); t < (test + 1); t++) {
    ins.clear();
    pac1.clear();
    pac2.clear();
    need.clear();
    cin >> n >> p;
    // pac.assign(n,vi(p,0));
    for (int i = (0); i < (n); i++) {
      int tmp;
      cin >> tmp;
      need.push_back(tmp);
    }
    for (int i = (0); i < (p); i++) {
      // REP(j,0,p){
      // 	int tmp; cin >> tmp;
      // 	pac[i][j] = tmp;
      // }
      int tmp;
      cin >> tmp;
      pac1.push_back(tmp);
    }
    if (n == 2) {
      for (int i = (0); i < (p); i++) {
        int tmp;
        cin >> tmp;
        pac2.push_back(tmp);
      }
    }
    int cont = 0;
    if (n == 1) {
      for (int i = (0); i < (p); i++) {
        for (int j = 1; j * need[0] * 9 / 10 <= pac1[i]; j++) {
          if (pac1[i] >= ceil(j * need[0] * 9 / 10) &&
              pac1[i] <= floor(j * need[0] * 11 / 10)) {
            cont++;
            break;
          }
        }
      }
    } else {
      do {
        int tmpcont = 0;
        for (int i = (0); i < (p); i++) {
          for (int j = 1; j * need[0] * 9 / 10 <= pac1[i] &&
                          j * need[1] * 9 / 10 <= pac2[i];
               j++) {
            if (pac1[i] >= ceil(j * need[0] * 9 / 10) &&
                pac1[i] <= floor(j * need[0] * 11 / 10) &&
                pac2[i] >= ceil(j * need[1] * 9 / 10) &&
                pac2[i] <= floor(j * need[1] * 11 / 10)) {
              tmpcont++;
              break;
            }
          }
        }
        cont = max(cont, tmpcont);
      } while (next_permutation(pac2.begin(), pac2.end()));
    }
    printf("Case #%d: %d\n", t, cont);
  }
  return 0;
}
