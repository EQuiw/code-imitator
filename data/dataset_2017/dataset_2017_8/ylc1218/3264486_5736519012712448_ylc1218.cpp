#include <cstdio>
#include <cstdlib>
#include <cstring>

int T, S, K;
char str[1005];
int state[1005];

int main(){
    scanf("%d", &T);

    for(int t = 1; t <= T; t++){

        scanf("%s %d", str, &K);
        S = strlen(str);
        for(int s = 0; s < S; s++){
            state[s] = str[s] == '-' ? 0 : 1;
        }

        int ans = 0;
        for(int s = 0; s <= S - K; s++){
            if (state[s] == 0){
                for(int i = s; i < s + K; i++){
                    state[i] ^= 1;
                }
                ans++;
            }
        }

        for(int s = S - K + 1; s < S; s++){
            if (state[s] != 1){
                ans = -1;
                break;
            }
        }
        if (ans != -1){
            printf("Case #%d: %d\n", t, ans);
        }
        else{
            printf("Case #%d: IMPOSSIBLE\n", t);
        }
    }

    return 0;
}
