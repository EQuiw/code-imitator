#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int ca,k;
const int maxn = 1010;
char s[maxn];
void init(){
    scanf("%s",s);
    scanf("%d",&k);
    int len = strlen(s);
    int ans = 0;
    for(int i = 0 ; i <= len-k ; i++){
        if(s[i] == '-'){
            ans++;
            for(int j = i ; j < i+ k ; j++)
                s[j] = (s[j] == '+'?'-':'+');
        }
    }
    printf("Case #%d: ",ca);
    for(int i = 0 ; i < len ; i++){
        if(s[i] == '-'){
            printf("IMPOSSIBLE\n");
            return;
        }
    }
    printf("%d\n",ans);
}

int main(){
    int T;
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    scanf("%d",&T);
    for(ca = 1; ca <= T ;ca++){
        init();
    }
}
