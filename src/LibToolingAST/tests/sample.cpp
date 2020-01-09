#include <stdio.h>

typedef const int typtyp;
typtyp mm = 0;

int test(int a, int b, int c){
    return(a+b+c);
}

int main() {

    for(int i=mm; i < 10; i++){
        int j = i;
        if(i > 5){
            j++;
            {
                int kk = 20;
                printf("%d\n", kk);
            }
            if(j!=0){
                {
                    int ll = 3333;
                    printf("%d\n", ll);
                }
                printf("%d\n", j);
            }

            if(j>5) {
                printf("%d\n", j - 1);
            } else {
                printf("ddd%d\n", j - 1);
            }
        }
    }

    float f = 20.0;
    return 0;
}

