#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
unsigned long long a,x,y;
int maxt;
int main()
{
    freopen ("in.in","r",stdin);
    freopen ("out.out","w",stdout);
    cin>>maxt;
    for(int t=1;t<=maxt;++t)
    {
        cin>>x;
        y=0;
        int tr=0;
        a=1;while(a<=x)a*=10;
        a=(a-1)/9;
        while(a>0)
        {
            while(a<=x&&tr<9){++tr;x-=a;y+=a;}
            a/=10;
        }
        cout<<"Case #"<<t<<": "<<y<<endl;
    }
    return 0;
}
