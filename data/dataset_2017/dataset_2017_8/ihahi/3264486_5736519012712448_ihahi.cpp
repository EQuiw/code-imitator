#include <iostream>
#include <set>
#include <string>

#define MAX_INT 20000

using namespace std;

void solve(void);
char gyaku(char p);
bool flip(char *str,char type, int *counter);
bool chkAllChar(char *str,char type);

int flipflip(char *targetStr, char type);



char input[1002];
int k;
int len;
char minusStr[1002];
int minusCnt,plusCnt;
char plusStr[1002];



int main(int argc, const char * argv[]) {
    freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/Qual2017-A/in.txt","r",stdin);
    freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/Qual2017-A/out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    for(int cnt=0;cnt<t;cnt++){
        memset(input, 0, sizeof(input));
        scanf("%s %d",input,&k);
        len = strlen(input);
        printf("Case #%d: ",cnt+1);
        solve();
        printf("\n");
    }
    return 0;
}

void solve(void){
    
    strcpy(minusStr, input);
    strcpy(plusStr, input);
//    minusCnt = flipflip(minusStr,'-');
    plusCnt = flipflip(plusStr,'+');

//    printf("+:%d, -:%d",plusCnt, minusCnt);
    int ans = plusCnt;
    if(ans == MAX_INT){
        printf("IMPOSSIBLE");
    }else{
        printf("%d",ans);
    }
}

int flipflip(char *targetStr, char type){
    int counter=0;
    int nowInd=0;
    while(1){
        if(chkAllChar(targetStr,type)){//終了している
            return counter;
        }
        while(targetStr[nowInd] == type){
            nowInd++;
        }//'+'を走査する。
        if(nowInd == len){//終了している
            return counter;
        }

        if(nowInd >= len-k+1)//終了しておらず、最後に回せるところ以上まで来てしまったらできなかったとする。
            return MAX_INT;
        if(flip(&targetStr[nowInd], type, &counter)){
            return counter;
        }
    }
//    printf("%d, %d",*Cnt,okflag);
    return MAX_INT;
}


bool chkAllChar(char *str,char type){
    if(strchr(str,gyaku(type)) == NULL){
        return true;//終了している。
    }else{
        return false;
    }
}



bool flip(char *str,char type, int *counter){
//    printf("flipping:%s\n",str);
    if(chkAllChar(str,type)){
        return true;
    }

    for(int ind=0;ind<k; ind++){
        str[ind] = gyaku(str[ind]);
    }
    (*counter)++;
//    printf("flipped:%s\n",str);

    if(chkAllChar(str,type)){
        return true;
    }else{
        return false;
    }
}

char gyaku(char p){
    if (p == '+'){
        return '-';
    }else{
        return '+';
    }
}
