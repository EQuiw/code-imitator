#include<cstdio>
#include<cstring>
using namespace std;
char s[1010];
int t,l,ans,i,j,k,a[1010];;
int main()
{
  //freopen("a.out","w",stdout);
  scanf("%d",&t);
  
  for (int kase=1;kase<=t;kase++)
  {
    scanf("%s",s);scanf("%d",&k);
    ans=0;
    l=strlen(s);
    for (i=1;i<=l;i++) 
      if (s[i-1]=='+') a[i]=1;else a[i]=0;
    bool flag=0;
    for (i=1;i<=l;i++)
    {
      if (a[i]==1) continue;
      if (i+k-1>l) {flag=1;break;}
      for (j=i;j<i+k;j++) a[j]=1-a[j];
      ans++;
    }
    if (flag) printf("Case #%d: IMPOSSIBLE\n",kase);
    else printf("Case #%d: %d\n",kase,ans);
  }
  //fclose(stdout);
}
