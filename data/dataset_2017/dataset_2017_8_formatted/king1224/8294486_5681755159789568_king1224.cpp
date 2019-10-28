#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

struct Horse {
  long long left;
  int speed;
} H[110], tmpH;

double dis[110][110];
bool visit[110];
vector<int> vec[110];
int d;
double ans;

void BT(int s, Horse preH, double time) {
  if (s == d) {
    ans = time < ans ? time : ans;
    return;
  }
  int next;
  for (int i = 0; i < vec[s].size(); ++i) {
    next = vec[s][i];
    //				printf("%d to %d: Not in If,
    //time=%lf\n",s,next,time+dis[s][next]); 		if(!visit[next]){
    Horse tmpH = preH;
    if (preH.left >= dis[s][next]) {
      //				visit[next] = true;
      preH.left -= dis[s][next];
      //				printf("%d to %d: used preH,
      //time=%lf\n",s,next,time+dis[s][next]/tmpH.speed);
      BT(next, preH, time + dis[s][next] / preH.speed);
      preH.left += dis[s][next];
      //				visit[next] = false;
    }
    tmpH = H[s];
    if (H[s].left >= dis[s][next]) {
      visit[next] = true;
      H[s].left -= dis[s][next];
      //				printf("%d to %d: used newH,
      //time=%lf\n",s,next,time+dis[s][next]/tmpH.speed);
      BT(next, H[s], time + dis[s][next] / H[s].speed);
      H[s].left += dis[s][next];
      visit[next] = false;
    }
    //		}
  }
}

int main() {
  int T;
  int N, Q;
  int s;
  scanf("%d", &T);
  for (int ii = 1; ii <= T; ++ii) {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; ++i) {
      scanf("%lld %d", &H[i].left, &H[i].speed);
      vec[i].clear();
    }
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        scanf("%lf", &dis[i][j]);
        if (dis[i][j] != -1) {
          vec[i].push_back(j);
        }
      }
    }

    printf("Case #%d:", ii);
    for (int i = 0; i < Q; ++i) {
      ans = 9999999999999;
      memset(visit, false, sizeof(visit));
      scanf("%d %d", &s, &d);
      tmpH.left = 0;
      visit[s] = true;
      BT(s, tmpH, 0);
      printf(" %.8lf", ans);
    }
    puts("");
  }
  return 0;
}
