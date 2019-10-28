#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

char s[64];
int n,l;

int main()
{
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0.out","w",stdout);
    int c,t,i,f;
    scanf("%d",&t);
    for(c=0;c<t;c++)
    {
        scanf("%s",s);
        l=strlen(s);
        for(i=l-1;i>=1;i--)
        {
            if(s[i]<s[i-1])
            {
                while((i>=1)&&(s[i-1]=='0'))
                {
                    i--;
                }
                s[i-1]--;
                memset(s+i,'9',(l-i)*sizeof(char));
            }
        }
        printf("Case #%d: %I64d\n",c+1,atoll(s));
    }
    return 0;
}
