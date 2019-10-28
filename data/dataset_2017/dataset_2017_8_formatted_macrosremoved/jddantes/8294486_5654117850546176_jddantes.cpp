#include <bits/stdc++.h>

using namespace std;

int input[7];
int N;

// BYR

int colors[1000]; // 0 for none
int chars[7];

typedef pair<int, int> pi;

bool check_color(int idx, int color) {
  int left = (idx - 1 + N) % N;
  int right = (idx + 1) % N;
  if (colors[left] & color) {
    return false;
  }
  if (colors[right] & color) {
    return false;
  }
  return true;
}

bool found;
int ans[1000];
void f(int idx) {
  if (idx == 0 && colors[idx]) {
    found = true;
    for (int i = 0; i < N; i++) {
      ans[i] = colors[i];
    }
    return;
  }
  // printf("idx %d\n", idx);
  for (int color = 1; color <= 6; color++) {
    if (!input[color])
      continue;
    if (check_color(idx, color)) {
      int old_val = colors[idx];
      input[color]--;
      colors[idx] = color;
      f((idx + 1) % N);
      colors[idx] = old_val;
      input[color]++;
      break;
    }
  }
}

int main() {
  chars[0b001] = 'R';
  chars[0b110] = 'G';
  chars[0b100] = 'B';
  chars[0b011] = 'O';
  chars[0b010] = 'Y';
  chars[0b101] = 'V';

  int cases;
  scanf("%d", &cases);

  for (int e = 0; e < cases; e++) {
    int R, O, Y, G, B, V;
    scanf("%d %d %d %d %d %d %d", &N, &R, &O, &Y, &G, &B, &V);
    input[0b001] = R;
    input[0b110] = G;
    input[0b100] = B;
    input[0b011] = O;
    input[0b010] = Y;
    input[0b101] = V;
    memset(colors, 0, sizeof colors);
    found = false;

    pi arr[3];
    arr[0] = pi(input[0b001], 0b001);
    arr[1] = pi(input[0b010], 0b010);
    arr[2] = pi(input[0b100], 0b100);
    sort(arr, arr + 3);

    // printf("Got: ");
    // for(int i = 0; i<3; i++){
    //     printf("%d %c\n", arr[i].first, chars[arr[i].second]);
    // }

    found = true;
    for (int i = 0; i < N;) {
      bool f = false;
      for (int j = 2; j >= 0; j--) {
        int clr = arr[j].second;
        int num = arr[j].first;
        if (!num)
          continue;

        if (check_color(i, clr)) {
          colors[i++] = clr;
          arr[j].first--;
          f = true;
        }
      }
      if (!f) {
        found = false;
        break;
      }
    }

    for (int i = 0; i < N; i++) {
      ans[i] = colors[i];
    }

    // f(0);
    if (found) {
      printf("Case #%d: ", e + 1);
      for (int i = 0; i < N; i++) {
        printf("%c", chars[ans[i]]);
      }
      printf("\n");
    } else {
      printf("Case #%d: IMPOSSIBLE\n", e + 1);
    }
  }
  return 0;
}
