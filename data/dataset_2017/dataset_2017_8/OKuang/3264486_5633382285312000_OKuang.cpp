#include <cstdio>
#include <cstring>
using namespace std;
char s[25];
inline void solve() {
    scanf("%s",s);
    for (int i=strlen(s)-1; i>0; i--)
        if (s[i]<s[i-1]) {
            for (int j=i; s[j]!='\0'; j++)
                s[j]='9';
            s[i-1]--;
        }
    if (s[0]=='0') printf("%s\n",s+1);
        else printf("%s\n",s);
}
int main() {
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    for (int tcase=1; tcase<=T; tcase++) {
        printf("Case #%d: ",tcase);
        solve();
    }
    return 0;
}