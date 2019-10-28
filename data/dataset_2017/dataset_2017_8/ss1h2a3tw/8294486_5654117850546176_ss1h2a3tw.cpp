#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int n;
int c_b[3];
int c_m[3];
const char c_c_b[] = "RYB";
int main(){
    int T;
    scanf("%d",&T);
    for(int I = 1 ; I <= T ; I ++){
        scanf("%d",&n);
        for(int i = 0 ; i < 3 ; i ++){
            scanf("%d%d",c_b+i,c_m+i);
        }
        auto maxit=max_element(c_b,c_b+3);
        if(*maxit > (n-*maxit))printf("Case #%d: IMPOSSIBLE\n",I);
        else{
            auto maxn = *maxit;
            int *c1,*c2;
            if(maxit==c_b){c1=c_b+1;c2=c_b+2;}
            if(maxit==c_b+1){c1=c_b;c2=c_b+2;}
            if(maxit==c_b+2){c1=c_b;c2=c_b+1;}
            string s[1010];
            for(int i = 0 ; i < maxn ; i ++){
                if(*c1>0){
                    s[i]+=c_c_b[c1-c_b];
                    (*c1)--;
                }
            }
            for(int i = maxn-1 ; i >= 0 ; i --){
                if(*c2>0){
                    s[i]+=c_c_b[c2-c_b];
                    (*c2)--;
                }
            }
            printf("Case #%d: ",I);
            for(int i = 0 ; i < maxn ; i ++){
                printf("%c",c_c_b[maxit-c_b]);
                printf("%s",s[i].c_str());
            }
            printf("\n");
        }
    }
}
