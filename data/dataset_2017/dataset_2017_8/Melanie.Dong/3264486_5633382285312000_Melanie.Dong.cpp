#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
string n, m;
int main()
{
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0.out","w",stdout);
    int t, ca=1;
    scanf("%d", &t);
    while(t--)
    {
        printf("Case #%d: ", ca++);
        cin>>n;
        m=n;
        reverse(n.begin(), n.end());
        bool flag=1;
        for(int i=1; i<n.length() && flag; i++)
            if(n[i]>n[i-1])
                flag=0;
        if(flag)
        {
            cout<<m<<endl;
            continue;
        }
        int j=n.length()-1;
        for(int i=j; i>0; i--)
        {
            if(n[i]<n[i-1])
                j=i-1;
            if(n[i]>n[i-1])
                break;
        }
        n[j]--;
        if(j==n.length()-1 && n[j]=='0')
        {
            for(int i=1; i<n.length(); i++)
                putchar('9');
            puts("");
            continue;
        }
        for(int i=n.length()-1; i>=j; i--)
            cout<<n[i];
        for(int i=j-1; i>=0; i--)
            putchar('9');;
        puts("");
    }
    return 0;
}
