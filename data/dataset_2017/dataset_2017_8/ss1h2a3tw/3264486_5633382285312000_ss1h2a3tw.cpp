#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char num[100];
int main (){
    int T;
    scanf("%d",&T);
    for(int I = 1 ; I <= T ; I ++){
        scanf("%s",num);
        int len = strlen(num);
        for(int x = 0 ; x < len ; x ++){
            for(int i = 0 ; i < len-1 ; i ++){
                if(num[i]>num[i+1]){
                    num[i]--;
                    for(int j = i+1 ; j < len ; j ++){
                        num[j]='9';
                    }
                }
            }
        }
        char *out;
        for(int i = 0 ; i < len ; i ++){
            out = num+i;
            if(*out!='0')break;
        }
        printf("Case #%d: %s\n",I,out);
    }

}
