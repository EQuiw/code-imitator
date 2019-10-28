#include <iostream>
using namespace std;

struct Horse {
  int K, S;
} horse[1000];

int main() {
  int T, N;
  double R, O, Y, G, B, V;
  cin >> T;
  for (int c = 1; c <= T; ++c) {
    cin >> N >> R >> O >> Y >> G >> B >> V;
    string result = "";
    if (R > N / 2 || Y > N / 2 || B > N / 2) {
      result = "IMPOSSIBLE";
    } else {
      if (R >= Y && R >= B) {
        result += 'R';
        R -= 0.5;
      } else if (Y >= R && Y >= B) {
        result += 'Y';
        Y -= 0.5;
      } else if (B >= Y && B >= R) {
        result += 'B';
        B -= 0.5;
      }
      for (int i = 1; i < N; ++i) {
        if (result[i - 1] == 'R') {
          if (Y >= B) {
            result += 'Y';
            --Y;
          } else {
            result += 'B';
            --B;
          }
        }
        if (result[i - 1] == 'Y') {
          if (R > B) {
            result += 'R';
            --R;
          } else {
            result += 'B';
            --B;
          }
        }
        if (result[i - 1] == 'B') {
          if (R > Y) {
            result += 'R';
            --R;
          } else {
            result += 'Y';
            --Y;
          }
        }
      }
    }

    // qsort(horse, N, sizeof(horse[0]), cmp);
    cout << "Case #" << c << ": " << result << endl;
  }
  return 0;
}