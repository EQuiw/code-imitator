#include <bits/stdc++.h>

using namespace std;

int isTidy(int n){
    int last = 10;
    while(n){
        int dig = n%10;
        n/=10;
        if(dig<=last){
            last = dig;
        } else {
            return 0;
        }
    }
    return 1;
}
set<int, greater<int>> dump;
int main(){
    for(int i = 1; i<=1000; i++){
        if(isTidy(i)){
            dump.insert(i);
        }
    }

    int cases;
    scanf("%d", &cases);

    for(int e = 0; e<cases; e++){
        int n;
        scanf("%d", &n);
        int x = *dump.lower_bound(n);
        printf("Case #%d: %d\n", e+1, x);
    }

    return 0;
}