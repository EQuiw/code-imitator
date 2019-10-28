
/*
Contest: Google Code Jam 2017 [Round 1A]
*/

#include <algorithm>
#include <math.h>
#include <queue>
#include <stdio.h>
#include <utility>
#define P pair<int, int>
#define x first
#define y second
#define mp make_pair
#define SP pair<int, P>
using namespace std;

int n, p;
int req[55];

int pack[55][55];
int cp[55][55];
bool closed[55][55];
int openCount[55];
priority_queue<SP> deadList[55];
int point = 0;

struct ingredient {
  int val;
  P pos;
  char mode;
};
vector<ingredient> bank;

void calculation(int r, int c) {
  double want = req[r];
  double have = pack[r][c];
  // Part A
  double lb = have / (1.1 * want);
  lb = ceil(lb);
  // Part B
  double ub = have / (0.9 * want);
  ub = floor(ub);
  // Check
  int l = (int)lb;
  if (l == 0)
    l++;
  int u = (int)ub;
  if (l > u) {
    closed[r][c] = true;
    return;
  } // Impossible in any number
  // printf("->[%d,%d]\n",l,u);
  // Make Something!
  ingredient tst;
  tst.pos = mp(r, c);

  tst.val = l;
  tst.mode = 'O';
  bank.push_back(tst);
  tst.val = u;
  tst.mode = 'C';
  bank.push_back(tst);
  cp[r][c] = u;
  return;
}

bool mycmp(const ingredient &ls, const ingredient &rs) {
  if (ls.val != rs.val)
    return (ls.val < rs.val);
  return ls.mode > rs.mode;
}

bool isOk() {
  for (int i = 0; i < n; i++)
    if (openCount[i] <= 0)
      return false;
  return true;
}

void takeIt() {
  for (int i = 0; i < n; i++) {
    SP t = deadList[i].top();
    deadList[i].pop();
    openCount[i]--;
    int cr = t.y.x;
    int cc = t.y.y;
    closed[cr][cc] = true;
  }
  point++;
}

void process(int idx) {
  // printf("PROCESSING
  // <%d(%d,%d),%c>",bank[idx].val,bank[idx].pos.x,bank[idx].pos.y,bank[idx].mode);
  int cr = bank[idx].pos.x;
  int cc = bank[idx].pos.y;
  if (bank[idx].mode == 'C') // Close
  {
    if (closed[cr][cc])
      return; // Nothing to do
    deadList[cr].pop();
    openCount[cr]--;
    closed[cr][cc] = true;
    return;
  }
  // OPEN!
  // printf("OPEN\n");
  int closePoint = cp[cr][cc];
  deadList[cr].push(mp(-1 * closePoint, bank[idx].pos));
  openCount[cr]++;
  // Check if it's a possible move
  bool vd = isOk();
  if (!vd)
    return;
  // Take It!
  takeIt();
  return;
}

void debug() {
  printf("Current status\n");
  for (int i = 0; i < bank.size(); i++) {
    printf("Mode: %c, Position: %d, [%d,%d]\n", bank[i].mode, bank[i].val,
           bank[i].pos.x, bank[i].pos.y);
  }
}

int solve() {
  scanf("%d%d", &n, &p);
  for (int i = 0; i < n; i++)
    scanf("%d", &req[i]);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      scanf("%d", &pack[i][j]);
  // Some Reset
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      closed[i][j] = false;
  bank.clear();
  for (int i = 0; i < n; i++)
    openCount[i] = 0;
  for (int i = 0; i < n; i++)
    while (!deadList[i].empty())
      deadList[i].pop();
  point = 0;
  // Calculation
  // printf("Calculation Process\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      calculation(i, j);
  // printf("End Of Calculation\n");
  if (bank.empty())
    return 0; // Obvious!
  sort(bank.begin(), bank.end(), mycmp);
  // printf("Sorted\n");
  // debug();

  // Go!
  int z = bank.size();
  for (int i = 0; i < z; i++)
    process(i);
  return point;
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-SmallOutput.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
