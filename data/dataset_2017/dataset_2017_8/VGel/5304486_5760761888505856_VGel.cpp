#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#define LL long long
#define CLR(a,x) memset(a,x,sizeof(a))
using namespace std;
const int N=30;
int n,m;
char str[N][N];
bool flag;
void FILL(int ki,int kj,int li,int lj,char ch)
{
    for (int k=ki;k<=kj;k++)
        for (int l=li;l<=lj;l++) str[k][l]=ch;
}
int main()
{
    #ifdef VGel
    freopen("A-small-attempt0.in","r",stdin);
    freopen("A-small-attempt0.out","w",stdout);
    #endif // VGel
    int T_T;
    scanf("%d",&T_T);
    for (int T=1;T<=T_T;T++)
    {
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++) scanf("%s",str[i]);
        int last=0,i,j,lj;
        for (i=0;i<n;i++)
        {
            flag=false;
            lj=0;
            for (j=0;j<m;j++)
            {
                if (str[i][j]!='?')
                {
                    flag=true;
                    FILL(last,i,lj,j,str[i][j]);
                    lj=j+1;
                }
            }
            if (flag&&lj<m)
            {
                FILL(last,i,lj,m-1,str[i][lj-1]);
            }
            if (flag) last=i+1;
        }
        if (last<n)
        {
            for (int k=last;k<n;k++)
                for (int l=0;l<m;l++) str[k][l]=str[last-1][l];
        }
        printf("Case #%d:\n",T);
        for (int i=0;i<n;i++) printf("%s\n",str[i]);
    }
    return 0;
}
