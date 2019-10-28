#include <cstdio>
using namespace std;
int test, N, R, O, Y, G, B, V, t;
char a[6];
int main() {
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
  scanf("%d", &test);
  for (int kase = 1; kase <= test; kase++) {
    scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);
    if (R > Y + B || Y > R + B || B > R + Y) {
      printf("Case #%d: IMPOSSIBLE\n", kase);
      continue;
    }

    if (R >= Y && Y >= B) {
      a[1] = 'R';
      a[2] = 'Y';
      a[3] = 'B';
    } else if (R <= Y && Y <= B) {
      a[1] = 'B';
      a[2] = 'Y';
      a[3] = 'R';
    } else if (R >= B && B >= Y) {
      a[1] = 'R';
      a[2] = 'B';
      a[3] = 'Y';
    } else if (R <= B && B <= Y) {
      a[1] = 'Y';
      a[2] = 'B';
      a[3] = 'R';
    } else if (B >= R && R >= Y) {
      a[1] = 'B';
      a[2] = 'R';
      a[3] = 'Y';
    } else if (B <= R && R <= Y) {
      a[1] = 'Y';
      a[2] = 'R';
      a[3] = 'B';
    }
    if (R < Y) {
      t = R;
      R = Y;
      Y = t;
    }
    if (R < B) {
      t = R;
      R = B;
      B = t;
    }
    if (Y < B) {
      t = Y;
      Y = B;
      B = t;
    }
    // YRYR...BRBR....YBR.........R
    // x+y+z=R,x+z=Y,y+z=B
    // x=R-B,y=R-Y,z=Y+B-R
    // printf("Case #%d: ",kase);
    char s[1010];
    int i;
    int l = -1;
    for (i = 1; i <= R - B; i++) {
      s[++l] = a[2];
      s[++l] = a[1];
    }
    // printf("%c%c",a[2],a[1]);
    for (i = 1; i <= R - Y; i++) {
      s[++l] = a[3];
      s[++l] = a[1];
    }
    // for (i=1;i<=R-B;i++) printf("%c%c",a[3],a[1]);
    for (i = 1; i <= Y + B - R; i++) {
      s[++l] = a[2];
      s[++l] = a[3];
      s[++l] = a[1];
    }
    // for (i=1;i<=Y+B-R;i++) printf("%c%c%c",a[2],a[3],a[1]);
    printf("Case #%d: ", kase);
    for (i = 0; i <= l; i++)
      printf("%c", s[i]);
    printf("\n");
  }
  // fclose(stdin);fclose(stdout);
}

// f[7][7]:end,or
// DP?
// chain?
// O = G = V = 0. (Each unicorn has only one hair color in its mane.)
// only RYB:RYRYRY....RYRBRBRRRRRRRRR
// RRR,B,Y    RYRBR
// RBYRBRBRYRY....
// RBYRBY...
/*A mane with only one color of hair appears to be that color. For example, a
mane with only blue hairs is blue. A mane with red and yellow hairs appears
orange. A mane with yellow and blue hairs appears green. A mane with red and
blue hairs appears violet. You have R, O, Y, G, B, and V unicorns with red,
orange, yellow, green, blue, and violet manes, respectively.*/
