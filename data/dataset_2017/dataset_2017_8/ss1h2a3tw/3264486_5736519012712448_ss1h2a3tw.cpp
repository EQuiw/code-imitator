#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char in[1010];
bool p[1010];
int k;
int main (){
    int T;
    scanf("%d",&T);
    for(int I = 1 ; I <= T ; I ++){
        scanf("%s%d",in,&k);
        int len = strlen(in);
        for(int i = 0 ; i < len ; i ++){
            if(in[i]=='+')p[i]=true;
            else p[i]=false;
        }
        int cnt=0;
        for(int i = 0 ; i <= len - k ; i ++){
            if(!p[i]){
                for(int j = 0 ; j < k ; j ++){
                    p[i+j]=!p[i+j];
                }
                cnt++;
            }
        }
        bool fail=false;
        for(int i = 0 ; i < len ; i ++){
            if(!p[i])fail=true;
        }
        printf("Case #%d: ",I);
        if(!fail)printf("%d",cnt);
        else printf("IMPOSSIBLE");
        printf("\n");
    }
}
