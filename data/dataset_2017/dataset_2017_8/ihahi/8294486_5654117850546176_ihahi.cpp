#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

int R,Y,B,O,G,V, N;
char buffer[1005];
char lastChar;
char firstChar;
int bufInd;

void solve(void);
using namespace std;
bool my_greater(pair<char,int> l, pair<char,int> r);
void setBuf(char k);
void use(pair<char,int> *k);

int main(int argc, const char * argv[]) {
    freopen("/Volumes/4HOPE/Dropbox/17Todai/CodeJam/R1B-2017-B/in.txt","r",stdin);
    freopen("/Volumes/4HOPE/Dropbox/17Todai/CodeJam/R1B-2017-B/out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    for(int cnt=0;cnt<t;cnt++){
        scanf("%d %d %d %d %d %d %d",&N, &R,&O,&Y,&G,&B,&V);
        printf("Case #%d: ",cnt+1);
        solve();
    }
    return 0;
}

void solve(void){
    bufInd = 0;
    memset(buffer, 0, sizeof(char)*1005);
    vector<pair<char,int>> a;
    a.push_back(make_pair('R',R-G));
    a.push_back(make_pair('Y',Y-V));
    a.push_back(make_pair('B',B-O));
    firstChar = '0';
    sort(a.begin(),a.end(),my_greater);

    if(a[0].second >= a[1].second + a[2].second + 1){
        printf("IMPOSSIBLE\n");
        return;
    }else{
/*        char lastChar=a[0].first;
        printf("%c",a[0].first);
        a[0].second--;*/
        lastChar = '0';//a[2].first;
        firstChar = a[0].first;
        for(int k=0;k<N;k++){
            sort(a.begin(),a.end(),my_greater);
            if(a[0].first != lastChar && a[0].second > 0){
                use(&a[0]);
            }else if(a[1].first != lastChar && a[1].second > 0){
                use(&a[1]);
            }else if(a[2].first != lastChar && a[2].second > 0){
                use(&a[2]);
            }else{
                printf("IMPOSSIBLE\n");
                return;
            }
//            sort(a.begin(),a.end(),my_greater);
        }
        if(buffer[bufInd-1] == buffer[0]){
            printf("OKASII %s\n",buffer);
            return;
        }else{
            buffer[bufInd] = 0;
            printf("%s\n",buffer);
            return;
        }
    }
//    printf("\n");
}


void use(pair<char,int> *k){
    setBuf(k->first);
    //                printf("%c",a[0].first);
    k->second--;
    lastChar = k->first;
}


bool my_greater(pair<char,int> l, pair<char,int> r){
    if(l.second == r.second){
            if(firstChar == l.first){
                return true;
            }else if(firstChar == r.first){
                return false;
            }
        return l.first < r.first;
    }else{
        return l.second > r.second;
    }
}

void setBuf(char k){
    buffer[bufInd] = k;
    bufInd++;
}
