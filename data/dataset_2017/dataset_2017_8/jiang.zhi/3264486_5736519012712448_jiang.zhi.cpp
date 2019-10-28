#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1010;

char w[N];

int main(){
    int t;
    scanf("%d", &t);
    for(int cas = 0; cas < t; cas++){
        int s;
        scanf(" %s%d", w, &s);
        int n = strlen(w);
        int ans = 0;
        for(int i = 0; i <= n - s; i++){
            if(w[i] == '-'){
                ans++;
                for(int j = 0; j < s; j++){
                    if(w[i+j] == '-') w[i+j] = '+';
                    else w[i+j] = '-';
                }
            }
        }
        for(int i = 0; i < n; i++){
            if(w[i] == '-') ans = -1;
        }
        printf("Case #%d: ",cas+1);
        if(ans == -1) printf("IMPOSSIBLE\n");
        else printf("%d\n", ans);
    }
    
}
