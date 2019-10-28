// Written by Li Bo
#include <bits/stdc++.h> 
using namespace std;
int a[20];
char s[20];
int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas<=T ; cas++) {
        int n;
        scanf("%s",s);
        n = strlen(s);

        for(int i = 0 ; i < n; i ++) 
            a[i] = s[i] - '0';

        for(int i = n-1; i ; i--){
            if (a[i] < a[i-1]) {
                a[i-1]--;
                for (int j = i; j < n; j++) a[j] = 9;
            }
        }

        int i = 0;
        while(a[i] == 0 && i<n-1) i++;
        
        printf("Case #%d: ", cas);
        for (;i<n;i++) printf("%d", a[i]);
        puts("");
    }
    return 0;
}
