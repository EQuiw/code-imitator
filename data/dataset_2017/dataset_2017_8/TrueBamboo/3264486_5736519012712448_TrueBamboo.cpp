//just flip
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<list>
#include<iterator>
#include<stack>
#include<queue>
using namespace std;

#include<fstream>
FILE *fin=freopen("a.in","r",stdin);
FILE *fout=freopen("a.out","w",stdout);

int main() {
	int T,t;
	cin>>T;
	for (t=1;t<=T;t++) {
		char s[1100];
		int k,n,m=0,a[1100],i,j;
		scanf("%s%d",s,&k);
		n=strlen(s);
		for (i=0;i<n;i++) {
			a[i]=(s[i]=='+'?1:0);
		}
		for (i=0;i<=n-k;i++) {
			if (!a[i]) {
				m++;
				for (j=0;j<k;j++) {
					a[i+j]=1-a[i+j];
				}
			}
		}
		for (i=0;i<n;i++) {
			if (!a[i]) {
				break;
			}
		}
		if (i<n)
		printf("Case #%d: IMPOSSIBLE\n",t);
		else printf("Case #%d: %d\n",t, m);
	}
    return 0;
}
