#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
using namespace std;
#define ll long long
#define inf 0x7f7f7f7f

char s[1010];
char type[]="ROYGBV";
int a[10];
int mp[1010];

void init()
{
    memset(s,0,sizeof(s));
}

int main()
{
    int T;
    scanf("%d",&T);
    for (int t=1;t<=T;t++)
    {
        init();
        int i,j,n,last,maxi,secmaxi;
        scanf("%d",&n);
        for (i=0;i<6;i++)
            scanf("%d",&a[i]);
        a[6]=0; last=6;
        printf("Case #%d: ",t);
        for (i=0;i<n;i++)
        {
            /*
            if (i==n-2 && a[mp[0]])
            {
                s[i]=type[mp[0]];
                if (s[i]==s[i-1])
                    break;
                a[mp[0]]--;
                continue;
            }
            */
            maxi=6;
            for (j=0;j<6;j=j+2)
                if (j!=last && a[j]>=a[maxi] && a[j])
                {
                    secmaxi=maxi;
                    maxi=j;
                }
            if (maxi==6)
                break;
            if (a[maxi]==a[secmaxi] && mp[0]!=maxi)
                maxi=secmaxi;
            //printf("%d\n",maxi);
            s[i]=type[maxi];
            mp[i]=maxi;
            if (i && s[i]==s[i-1])
                break;
            a[maxi]--;
            last=maxi;
            //printf("%c\n",s[maxi]);
        }
        if (i!=n || s[0]==s[n-1])
            printf("IMPOSSIBLE\n");
        else printf("%s\n",s);
    }
}
