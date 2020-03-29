
/*
Contest: Google Code Jam 2017 [Round 1C]
*/

#include <algorithm>
#include <stdio.h>
#include <utility>
#include <vector>
#define P pair<int, int>
#define x first
#define y second
#define mp make_pair
using namespace std;

struct event {
  P when;
  int owner;
};
vector<event> bank;

vector<int> freeTime[3];

bool mycmp(const event &ls, const event &rs) {
  return ((ls.when.x) < (rs.when.x));
}

int tl[20];
int ans = 0;

void busyCalculation() {
  tl[0] = 720;
  tl[1] = 720;
  int z = bank.size();
  for (int i = 0; i < z; i++) {
    int team = bank[i].owner;
    int ti = bank[i].when.x;
    int tf = bank[i].when.y;
    int timeUsed = tf - ti;
    tl[team] -= timeUsed;
  }
}

void segmentGeneration() {
  ans = 0;
  for (int i = 0; i < 3; i++)
    freeTime[i].clear();
  int z = bank.size();
  // printf("Total Segment: %d\n",z);
  for (int i = 0; i < z; i++) {
    int thisOne = i;
    int nextOne = (i + 1) % z;
    int t1 = bank[thisOne].owner;
    int t2 = bank[nextOne].owner;
    int sumTeam = t1 + t2;
    // printf("(T%d,T%d)\n",t1,t2);
    int ti = bank[thisOne].when.y;
    int tf = bank[nextOne].when.x;
    int timeUsed = tf - ti;
    if (timeUsed < 0)
      timeUsed += 1440;
    if (sumTeam == 1) {
      ans++;
    }
    // printf("TimeUsed: %d\n",timeUsed);
    if (timeUsed <= 0)
      continue;
    freeTime[sumTeam].push_back(timeUsed);
  }
}

void wasteTeamA() {
  int z = freeTime[0].size();
  if (z == 0)
    return;
  // printf("Segment Count: %d, Time Left: %d\n",z,tl[0]);
  sort(freeTime[0].begin(), freeTime[0].end());
  int reduce = 0;
  for (int i = 0; i < z; i++) {
    if (freeTime[0][i] > tl[0])
      break;
    reduce++;
    tl[0] -= freeTime[0][i];
  }
  int left = z - reduce;
  ans += 2 * left;
  return;
}

void wasteTeamB() {
  int z = freeTime[2].size();
  if (z == 0)
    return;
  // printf("GoB\n");
  sort(freeTime[2].begin(), freeTime[2].end());
  int reduce = 0;
  for (int i = 0; i < z; i++) {
    if (freeTime[2][i] > tl[1])
      break;
    reduce++;
    tl[1] -= freeTime[2][i];
  }
  int left = z - reduce;
  ans += 2 * left;
  return;
}

int solve() {
  bank.clear();
  int ac, aj;
  scanf("%d%d", &ac, &aj);
  int timeLeft = 720;
  for (int i = 0; i < ac; i++) {
    event tst;
    tst.owner = 0;
    scanf("%d%d", &tst.when.x, &tst.when.y);
    bank.push_back(tst);
  }
  for (int i = 0; i < aj; i++) {
    event tst;
    tst.owner = 1;
    scanf("%d%d", &tst.when.x, &tst.when.y);
    bank.push_back(tst);
  }
  sort(bank.begin(), bank.end(), mycmp);
  busyCalculation();
  segmentGeneration();
  // printf("Current Answer: %d\n",ans);
  wasteTeamA();
  wasteTeamB();
  return ans;
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-Small.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
