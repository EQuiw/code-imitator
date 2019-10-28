#include <stdio.h>
#include <string.h>

int len, i, j, cnt;
char N[20];

int main() {
    int cases;
    scanf("%d", &cases);
    for (int kejs = 1; kejs <= cases; kejs++) {
        printf("Case #%d: ", kejs);
        scanf("%s", N);
        len = strlen(N);
        bool change = true;
        while (change) {
            change = false;
            for (i = 1; i < len; i++) {
                if (N[i-1] > N[i]) {
                    change = true;
                    if (N[i-1] == '1') {
                        len--;
                        for (j = 0; j < len; j++) N[j] = '9';
                        N[j] = '\0';
                    } else {
                        N[i-1]--;
                        for (j = i; j < len; j++) N[j] = '9';
                    }
                }
            }
        }
        printf("%s\n", N);
    }
    return 0;
}
