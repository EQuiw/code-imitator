#include <bits/stdc++.h>
using namespace std;
#define ST first.first
#define ET first.second
#define WHO second

typedef pair<int, int> pii;
typedef pair<pii, int> ppi;

int interval(ppi a, ppi b) { return (b.ST - a.ET + 1440 * 2) % 1440; }

bool touching(ppi a, ppi b) { return a.ET == b.ST; }

bool isSame(ppi a, ppi b) { return a.WHO == b.WHO; }

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    int ac, aj;
    cin >> ac >> aj;
    vector<ppi> s;
    int x, y;
    int timeleft[3] = {0, 720, 720};
    for (int i = 0; i < ac; i++) {
      cin >> x >> y;
      s.push_back(ppi(pii(x, y), 1));
      timeleft[1] -= (y - x);
    }
    for (int i = 0; i < aj; i++) {
      cin >> x >> y;
      s.push_back(ppi(pii(x, y), 2));
      timeleft[2] -= (y - x);
    }
    sort(s.begin(), s.end());
    s.push_back(s.front());
    while (1) {
      int cl = -1;
      for (int i = 0; i < s.size() - 1; i++) {
        if (touching(s[i], s[i + 1])) {
          continue;
        }
        if (isSame(s[i], s[i + 1]) &&
            interval(s[i], s[i + 1]) <= timeleft[s[i].WHO]) {
          // canidate for compress
          if (cl == -1 ||
              interval(s[i], s[i + 1]) < interval(s[cl], s[cl + 1])) {
            cl = i;
          }
        }
      }
      if (cl == -1) {
        break;
      } else {
        // run compress
        timeleft[s[cl].WHO] -= interval(s[cl], s[cl + 1]);
        // cout << "Compress " << s[cl].ET << " to " << s[cl+1].ST << endl;
        // cout << "Time left " << timeleft[s[cl].WHO] << endl;
        s[cl].ET = s[cl + 1].ST;
      }
    }
    int ans = 0;
    for (int i = 0; i < s.size() - 1; i++) {
      if (touching(s[i], s[i + 1])) {
        if (!isSame(s[i], s[i + 1])) {
          ans += 1;
        }
      } else {
        if (isSame(s[i], s[i + 1])) {
          ans += 2;
        } else {
          ans += 1;
        }
      }
    }
    cout << "Case #" << t << ": " << ans << endl;
    ;
    // int sch[1440];
    // memset(sch,0,sizeof(sch));
    // for(auto i:s){
    // 	for(int j = i.ST;j<i.ET;j++){
    // 		sch[j] = i.WHO;
    // 	}
    // }
    // for(auto i:s){
    // 	cout << i.ST << "-" << i.ET << ": " << i.WHO << endl;
    // }
    // cout << endl;
    // for(int i=0;i<1440;i+=10){
    // 	if(i%120==0) cout << endl;
    // 	cout << i << "-" << sch[i] << " ";
    // }
    // cout << endl;
    // cout << endl;
  }
}