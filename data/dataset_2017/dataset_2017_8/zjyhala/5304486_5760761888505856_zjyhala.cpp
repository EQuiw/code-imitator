#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
char s[30][30];
int r,c,ca;

void init(){
    scanf("%d%d",&r,&c);
    for(int i = 0 ; i < r; i++)
        scanf("%s",s[i]);
    for(int i = 0 ;i < r ; i++){
        int f = 0,pos = 0;
        char now,fi;
        for(int j = 0 ; j < c ; j++){
            if(s[i][j] != '?' && f == 0){
                f = 1;
                pos = j;
                now = s[i][j];
                fi = now;
            }
            else if(s[i][j] == '?' && f ==1){
                s[i][j] = now;
            }
            else if(s[i][j] != '?' && f == 1){
                now = s[i][j];
            }

        }
        for(int j = 0 ; j < pos ; j++)
            s[i][j] = fi;

    }
    char now;
    int f = 0,pos = 0;
   for(int i = 0 ; i < r; i++){
        if(s[i][0] == '?' && f == 0){
            continue;
        }
        else if(s[i][0] == '?' && f == 1){
            for(int j =  0; j < c; j++)
                s[i][j] = s[i-1][j];
        }
        else if(s[i][0] != '?' && f == 0){
            f = 1;
            pos = i;
        }
   }
   for(int i = 0 ; i < r; i++){
    if(s[i][0] != '?')
        break;
    else{
        for(int j = 0 ;j < c; j++){
            s[i][j] = s[pos][j];
        }
    }
   }
   printf("Case #%d:\n",ca);
   for(int i = 0 ; i <r; i++){
    printf("%s\n",s[i]);
   }
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
