#include <cstdio>
#include <cstdlib>
#define C_R 0
#define C_O 1
#define C_Y 2
#define C_G 3
#define C_B 4
#define C_V 5


int T, N;
int num[6];
int ans[1005];
int haveAns;
int valid[6][6] = {0};
char m[] = {'R', 'O', 'Y', 'G', 'B', 'V'};

int possible(int n){
    int bound = n == N ? n / 2 : (n + 1) / 2;
    //red
    if (num[C_R] + num[C_O] + num[C_V] > bound){
        return 0;
    }
    //yellow
    if (num[C_O] + num[C_Y] + num[C_G] > bound){
        return 0;
    }
    //blue
    if (num[C_G] + num[C_B] + num[C_V] > bound){
        return 0;
    }
    return 1;
}

void dfs(int layer){
    if (!possible(N - layer)){
        return;
    }

    if (layer == N){
        if (valid[ans[0]][ans[N - 1]]){
            haveAns = 1;
            return;
        }
    }
    for(int i = 0; i < 6; i++){
        if ((layer == 0 || valid[ans[layer-1]][i]) && num[i] > 0){
            ans[layer] = i;
            num[i]--;
            dfs(layer + 1);
            num[i]++;
            if (haveAns){
                return;
            }
        }
    }
}

int main(){

    valid[C_R][C_Y] = valid[C_R][C_G] = valid[C_R][C_B] = 1;
    valid[C_Y][C_R] = valid[C_Y][C_B] = valid[C_Y][C_V] = 1;
    valid[C_B][C_R] = valid[C_B][C_O] = valid[C_B][C_Y] = 1;
    valid[C_G][C_R] = valid[C_O][C_B] = valid[C_V][C_Y] = 1;

    scanf("%d", &T);
    for(int t = 1; t <= T; t++){
        scanf("%d", &N);
        for(int i = 0; i < 6; i++){
            scanf("%d", &num[i]);
        }
        haveAns = 0;
        dfs(0);
        printf("Case #%d: ", t);
        if (haveAns){
            for(int i = 0; i < N; i++){
                printf("%c", m[ans[i]]);
            }
            printf("\n");
        }
        else{
            printf("IMPOSSIBLE\n");
        }
    }
    return 0;
}
