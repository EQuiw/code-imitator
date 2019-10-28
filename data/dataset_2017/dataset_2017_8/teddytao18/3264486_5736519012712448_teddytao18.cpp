#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
#define ll long long

int k;
char s[1010];

void flip(int pos)
{
    int i;
    for (i=0;i<k;i++)
        if (s[i+pos]=='+')
            s[i+pos]='-';
        else s[i+pos]='+';
}

int main()
{
    int T;
    scanf("%d",&T);
    for (int t=1;t<=T;t++)
    {
        int i,l,times;
        scanf("%s",s);
        scanf("%d",&k);
        l=strlen(s); times=0;
        for (i=0;i<l-k+1;i++)
            if (s[i]=='-')
            {
                flip(i);
                times++;
            }
        for (;i<l;i++)
            if (s[i]=='-')
                break;
        printf("Case #%d: ",t);
        if (i==l)
            printf("%d\n",times);
        else printf("IMPOSSIBLE\n");
    }
}
