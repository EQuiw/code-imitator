#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool f(int n){
  if (n<10) return true;
  int a = n%10;
  int b = n%100/10;
  return f(n/10) && (a>=b);
}

char s[100];
int main(void){
    int t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){

        // int g;
        // scanf("%d",&g);
        // for(;!f(g);--g);
        // printf("Case #%d: %d\n", tt, g);
        // continue;


        scanf("%s", s);
        int k;      
        for (k=1;s[k]!=0;++k) {
          if(s[k]<s[k-1])
            break;
        }
        if(s[k]==0){
          printf("Case #%d: %s\n", tt, s);
          continue;
        }

        int i=max(0,k-1);
        for(int j=strlen(s)-1;j>i;--j)s[j]='9';

        for(;i>=0;--i){
          if(i==0 || s[i]>s[i-1]){
            --s[i];
            break;
          }
          s[i]='9';
        }

        printf("Case #%d: %s\n", tt, s[0]=='0'?s+1:s);
    }
    return 0;
}

