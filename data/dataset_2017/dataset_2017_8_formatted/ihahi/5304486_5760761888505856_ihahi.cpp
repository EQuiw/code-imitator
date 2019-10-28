#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solve(void);
void padFirstToLetter(int start, int x);
bool chkAllQ(int y);
void copyFrom(int fromRow, int toRow);

int R, C;

char IN[26][26];

int main(int argc, const char *argv[]) {
  freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/R1A-2017-A/in.txt", "r",
          stdin);
  freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/R1A-2017-A/out.txt", "w",
          stdout);
  int t;
  scanf("%d", &t);
  for (int cnt = 0; cnt < t; cnt++) {
    scanf("%d %d", &R, &C);
    for (int l = 0; l < R; l++) {
      scanf("%s", &IN[l][0]);
    }
    printf("Case #%d:\n", cnt + 1);
    solve();
    //        printf("\n");
  }
  return 0;
}

void solve(void) {
  for (int y = 0; y < R; y++) {
    padFirstToLetter(0, y);
    /*        for(int x=0;x<C;x++){
                printf("%c",IN[y][x]);
            }
            printf("\n");*/
  }

  char nearestCom[26];
  int nearestFilled = 0;
  for (int y = 0; y < R; y++) {
    if (chkAllQ(y)) {
      if (y == 0) {
        int from = 1;
        while (chkAllQ(from)) {
          from++;
        }
        for (int to = 0; to <= from - 1; to++) {
          copyFrom(from, to);
        }
        nearestFilled = from;
        //                y=from;
      } else {
        copyFrom(nearestFilled, y);
        nearestFilled = y;
      }
    } else {
      nearestFilled = y;
    }
  }
  for (int y = 0; y < R; y++) {
    for (int x = 0; x < C; x++) {
      printf("%c", IN[y][x]);
    }
    printf("\n");
  }
}

void copyFrom(int fromRow, int toRow) {
  for (int x = 0; x < C; x++) {
    IN[toRow][x] = IN[fromRow][x];
  }
}

bool chkAllQ(int y) {
  for (int x = 0; x < C; x++) {
    if (IN[y][x] != '?') {
      return false;
    }
  }
  return true;
}

void padFirstToLetter(int start, int y) {
  if (start == C - 1) {
    return;
  }

  char nowL = '?';
  int pos = start;
  for (int x = start; x < C; x++) {
    if (IN[y][x] != '?') {
      nowL = IN[y][x];
      pos = x;
      break;
    }
  }

  if (nowL == '?') {
    return;
  }

  for (int x = pos; x >= start; x--) {
    IN[y][x] = nowL;
  }
  for (int x = pos + 1; x < C; x++) {
    if (IN[y][x] == '?') {
      IN[y][x] = nowL;
    } else {
      padFirstToLetter(x, y);
    }
  }
}
