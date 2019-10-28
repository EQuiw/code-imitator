#include <iostream>
#include <set>
#include <string>

#define MAX_INT 20000
#define CTONUM(O) O-'0'

using namespace std;

void solve(void);

char num[22];

int main(int argc, const char * argv[]) {
    int t;
    scanf("%d",&t);
    for(int cnt=0;cnt<t;cnt++){
        scanf("%s",num);
        printf("Case #%d: ",cnt+1);
        solve();
        printf("\n");
    }
    return 0;
}

void solve(void){
    
    char ansBuf[20];
    int ansInd=0;
    
    int len=strlen(num);
    for(int k=0;k<len;k++){
        num[k] -= '0';
    }
    num[len] = '9'+1;
    if(len == 1){
        printf("%d",num[0]);
        return;
    }
    
    int lastStepUp=0;
    for(int nowInd=1;nowInd<len+1;nowInd++){

        int bakNum = num[nowInd-1];
        int nowNum = num[nowInd];
        if(bakNum < nowNum){
            lastStepUp = nowInd;
        }
        if(bakNum <= nowNum){
            ansBuf[ansInd] = '0'+bakNum;
            ansInd++;
        }else{
            if(bakNum == 1){
                for(int k=0;k<len-1;k++){
                    ansBuf[k] = '9';
                }
                len --;
                break;
            }
            ansBuf[lastStepUp] = '0'+bakNum-1;
            for(int k=lastStepUp+1; k<len;k++){
                ansBuf[k] = '9';
            }
            break;
        }
        
    }
    ansBuf[len] = '\0';
    printf("%s",ansBuf);
    return;
}
