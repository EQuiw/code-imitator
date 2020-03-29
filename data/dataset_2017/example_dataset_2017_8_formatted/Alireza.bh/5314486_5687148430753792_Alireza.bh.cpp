#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:100000000000")
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
#define FR(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define FOR(i, c, n) for (int(i) = (c); (i) < (n); (i)++)
#define REP(it, v, cont)                                                       \
  for (cont::iterator(it) = (v).begin(); (it) != (v).end(); ++(it))
#define CLR(a, c) memset((a), (c), sizeof(a))
#define ALL(v) (v).begin(), (v).end()
#define SQR(a) ((a) * (a))
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

bool train[2000][2000];
int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcas;
  cin >> Tcas;
  FR(cas, Tcas) {
    printf("Case #%d: ", cas + 1);
    int n, c, m;
    cin >> n >> c >> m;
    vector<PII> v;
    FR(i, m) {
      PII p;
      cin >> p.first >> p.second;
      v.push_back(p);
    }
    sort(ALL(v));
    CLR(train, false);
    vector<int> trainSeat;
    vector<vector<int>> buyer;
    FR(ticket, m) {
      bool hasTaken = false;
      FR(i, trainSeat.size())
      if (v[ticket].first > trainSeat[i] &&
          train[i][v[ticket].second] == false && trainSeat[i] < n) {
        hasTaken = true;
        train[i][v[ticket].second] = true;
        trainSeat[i]++;
        buyer[i].push_back(v[ticket].first);
        break;
      }
      if (hasTaken == false) {
        trainSeat.push_back(1);
        train[trainSeat.size() - 1][v[ticket].second] = true;
        vector<int> temp;
        temp.push_back(v[ticket].first);
        buyer.push_back(temp);
      }
    }
    cout << trainSeat.size() << " ";

    /*int res=0;
    FR(i,buyer.size()){
            vector<int> temp=buyer[i];
            sort(ALL(temp));
            FR(j,temp.size()-1){
                    if(temp[j+1]==temp[j]) res++;
            }
    }*/
    int res = 0;
    int cake[2000] = {0};
    FR(i, m) cake[v[i].first]++;
    FR(i, 2000) res += max(0, cake[i] - (int)trainSeat.size());

    cout << res << endl;
  }
}