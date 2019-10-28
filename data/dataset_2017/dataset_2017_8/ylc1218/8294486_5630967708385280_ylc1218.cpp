#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int T, D, N;
int main(){
    scanf("%d", &T);
    for(int t = 1; t <= T; t++){
        scanf("%d %d", &D, &N);
        double slowest = 0;
        for(int i = 0; i < N; i++){
            int k, s;
            scanf("%d %d", &k, &s);
            slowest = max(slowest, (D - k) / (double)s);
        }
        printf("Case #%d: %lf\n", t, D / slowest);
    }
    return 0;
}
