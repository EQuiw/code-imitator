
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
  for (int(cas) = 0; (cas) < (Tcas); (cas)++) {
    printf("Case #%d: ", cas + 1);
    int n, c, m;
    cin >> n >> c >> m;
    vector<PII> v;
    for (int(i) = 0; (i) < (m); (i)++) {
      PII p;
      cin >> p.first >> p.second;
      v.push_back(p);
    }
    sort((v).begin(), (v).end());
    memset((train), (false), sizeof(train));
    vector<int> trainSeat;
    vector<vector<int>> buyer;
    for (int(ticket) = 0; (ticket) < (m); (ticket)++) {
      bool hasTaken = false;
      for (int(i) = 0; (i) < (trainSeat.size()); (i)++)
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
    for (int(i) = 0; (i) < (m); (i)++)
      cake[v[i].first]++;
    for (int(i) = 0; (i) < (2000); (i)++)
      res += max(0, cake[i] - (int)trainSeat.size());

    cout << res << endl;
  }
}
