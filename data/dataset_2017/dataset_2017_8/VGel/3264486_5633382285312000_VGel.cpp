#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#define LL long long
#define CLR(a,x) memset(a,x,sizeof(a))
using namespace std;
int len;
int a[30];
char str[30];
bool check(int pos)
{
    for (int i=1;i<=pos;i++) if (a[i]<a[i-1]) return false;
    return true;
}
void dfs(int pos)
{
    if (pos>=len) return ;
    if (pos==0) return ;
    while (a[pos]<a[pos-1])
    {
        if (a[pos-1]==0) dfs(pos-1);else a[pos-1]--;
        if (!check(pos-1)) dfs(pos-1);
        for (int i=pos;i<len;i++) a[i]=9;
    }
    dfs(pos+1);
}
int main()
{
    #ifdef VGel
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0.out","w",stdout);
    #endif // VGel
    int T_T;
    scanf("%d",&T_T);
    for (int T=1;T<=T_T;T++)
    {
        scanf("%s",str);
        len=strlen(str);
        for (int i=0;i<len;i++) a[i]=str[i]-'0';
        dfs(1);
        printf("Case #%d: ",T);
        bool f=true;
        for (int i=0;i<len;i++)
        {
            if (f&&a[i]==0) continue;
            f=false;
            putchar(a[i]+'0');
        }
        putchar(10);
    }
    return 0;
}
