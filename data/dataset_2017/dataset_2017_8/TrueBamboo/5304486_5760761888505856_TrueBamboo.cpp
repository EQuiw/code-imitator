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
	int m,n,T,t,i,j,d,k;
	cin>>T;
	for (t=1;t<=T;t++) {
		char s[30][30];
		cin>>m>>n;
		for (i=0;i<m;i++) {
			scanf("%s",s[i]);
		}
		for (i=0;i<m;i++) {
			//printf("%s\n",s[i]);
		}
		int a[26][2],b[26][2];
		memset(a,1,sizeof(a));
		memset(b,0,sizeof(b));
		for (i=0;i<m;i++) {
			for (j=0;j<n;j++) {
				if (s[i][j]!='?') {
					k=s[i][j]-'A';
					a[k][0]=min(a[k][0],i);
					a[k][1]=min(a[k][1],j);
					b[k][0]=max(b[k][0],i);
					b[k][1]=max(b[k][1],j);
				}
			}
		}
		for (k=0;k<26;k++) {
			for (i=a[k][0];i<=b[k][0];i++) {
				for (j=a[k][1];j<=b[k][1];j++) {
					s[i][j]=k+'A';
				}
			}
		}
		for (k=0;k<26;k++) {
			if (a[k][0]>m) {
				continue;
			}
			for (d=1;d<999;d++) {
				i=a[k][0]-1;
				if (i<0) {
					break;
				}
				for (j=a[k][1];j<=b[k][1];j++) {
					if (s[i][j]!='?') {
						break;
					}
				}
				if (j<=b[k][1]) {
					break;
				}
				for (j=a[k][1];j<=b[k][1];j++) {
					s[i][j]=k+'A';
				}
				a[k][0]--;
			}
			for (d=1;d<999;d++) {
				i=a[k][1]-1;
				if (i<0) {
					break;
				}
				for (j=a[k][0];j<=b[k][0];j++) {
					if (s[j][i]!='?') {
						break;
					}
				}
				if (j<=b[k][0]) {
					break;
				}
				for (j=a[k][0];j<=b[k][0];j++) {
					s[j][i]=k+'A';
				}
				a[k][1]--;
			}
		}
		for (k=0;k<26;k++) {
			if (a[k][0]>m) {
				continue;
			}
			for (d=1;d<999;d++) {
				i=b[k][0]+1;
				if (i>=m) {
					break;
				}
				for (j=a[k][1];j<=b[k][1];j++) {
					if (s[i][j]!='?') {
						break;
					}
				}
				if (j<=b[k][1]) {
					break;
				}
				for (j=a[k][1];j<=b[k][1];j++) {
					s[i][j]=k+'A';
				}
				b[k][0]++;
			}
			for (d=1;d<999;d++) {
				i=b[k][1]+1;
				if (i>=n) {
					break;
				}
				for (j=a[k][0];j<=b[k][0];j++) {
					if (s[j][i]!='?') {
						break;
					}
				}
				if (j<=b[k][0]) {
					break;
				}
				for (j=a[k][0];j<=b[k][0];j++) {
					s[j][i]=k+'A';
				}
				b[k][1]++;
			}
		}
		printf("Case #%d:\n",t);
		for (i=0;i<m;i++) {
			printf("%s\n",s[i]);
		}
	}
    return 0;
}
