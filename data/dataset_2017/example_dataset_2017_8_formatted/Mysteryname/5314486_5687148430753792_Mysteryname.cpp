
/*
Contest: Google Code Jam 2017 [Round 2]
*/

#include <algorithm>
#include <queue>
#include <stdio.h>
using namespace std;

int n, c, m;

struct ticket {
  int owner;
  int position;
};
ticket stuff[1111];

int oneCount[5];
int otherCount[5];

int edge[1111][1111];

int SOURCE;
int SINK;
int INF = 9999;

int visitId[1111];
int prv[1111];
int roundCount = 0;

bool findPath() {
  queue<int> bank;
  roundCount++;
  bool ok = false;
  bank.push(SOURCE);
  prv[SOURCE] = -1;
  visitId[SOURCE] = roundCount;
  while (!bank.empty()) {
    int cur = bank.front();
    bank.pop();
    // printf("Working on %d\n",cur);
    // SPAN
    for (int i = m + 1; i >= 0; i--) {
      if (edge[cur][i] <= 0)
        continue; // Looking for NON-ZERO EDGE
      if (visitId[i] == roundCount)
        continue;
      visitId[i] = roundCount;
      prv[i] = cur;
      if (i == SINK) {
        ok = true;
        break;
      }
      bank.push(i);
    }
  }
  if (!ok)
    return false;
  int bottleneck = INF;
  int curNode = SINK;
  // printf("Path Found\n");
  while (curNode >= 0) {
    // printf("Node: %d\n",curNode);
    int last = prv[curNode];
    if (last == -1)
      break;
    bottleneck = min(bottleneck, edge[last][curNode]);
    curNode = last;
  }
  // printf("Bottle Neck: %d\n",bottleneck);
  curNode = SINK;
  while (curNode >= 0) {
    int last = prv[curNode];
    if (last == -1)
      break;
    edge[curNode][last] += bottleneck;
    edge[last][curNode] -= bottleneck;
    curNode = last;
  }
  return true;
}

int getMatching() {
  SOURCE = m;
  SINK = m + 1;
  for (int i = 0; i < m + 2; i++)
    for (int j = 0; j < m + 2; j++) {
      edge[i][j] = 0;
    }
  // Make Edge
  for (int i = 0; i < m; i++) {
    if (stuff[i].position == 1)
      continue;
    int owner = stuff[i].owner;
    if (owner == 1)
      edge[SOURCE][i] = 1;
    else
      edge[i][SINK] = 1;
  }
  for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++) {
      if (stuff[i].owner != 1)
        continue;
      if (stuff[j].owner != 2)
        continue;
      if (stuff[i].position == stuff[j].position)
        continue; // Invalid Match
      edge[i][j] = INF;
    }
  // Go algorithm!
  for (int i = 0; i < m + 2; i++)
    visitId[i] = 0;
  roundCount = 0;
  while (true) {
    bool vd = findPath();
    if (!vd)
      break;
  }
  // Get Answer
  int ret = 0;
  for (int i = 0; i < m; i++)
    ret += edge[i][SOURCE];
  return ret;
}

void smallSolver() {
  scanf("%d%d%d", &n, &c, &m);
  oneCount[0] = 0;
  oneCount[1] = 0;
  otherCount[0] = 0;
  otherCount[1] = 0;
  for (int i = 0; i < m; i++)
    scanf("%d%d", &stuff[i].position, &stuff[i].owner);
  for (int i = 0; i < m; i++) {
    int det = 0;
    if (stuff[i].owner == 2)
      det = 1;
    if (stuff[i].position == 1)
      oneCount[det]++;
    else
      otherCount[det]++;
  }
  int base = oneCount[0] + oneCount[1];
  otherCount[0] = max(otherCount[0] - oneCount[1], 0);
  otherCount[1] = max(otherCount[1] - oneCount[0], 0);
  // printf("Other: <%d,%d>\n",otherCount[0],otherCount[1]);
  int additional = max(otherCount[0], otherCount[1]);
  // printf("Additional: %d\n");
  int minRide = base + additional;

  int maxMatch = getMatching();
  // printf("MAX FLOW: %d\n",maxMatch);
  int delta = otherCount[0] - otherCount[1];
  if (delta < 0)
    delta *= -1;
  int promote = max(0, additional - (maxMatch + delta));

  printf("%d %d\n", minRide, promote);
}

int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-Small.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    smallSolver();
  }
  return 0;
}
