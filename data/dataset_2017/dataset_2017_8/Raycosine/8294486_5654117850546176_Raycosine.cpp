#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define re(i,a,b) for(int i = a; i <= b; i++)
#define rep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
int T;
int n,r,o,y,g,B,v;
int a[3];
char b[3];
int ord[3]; 
int cmp(int x, int y){
	return a[x]<a[y];
}
int main(){
//	freopen("B.in","r",stdin);freopen("B.out","w",stdout);
	scanf("%d", &T);
	re(casen, 1,T)
	{
		scanf("%d", &n);
		scanf("%d%d%d%d%d%d", &r,&o,&y,&g,&B,&v);
		a[0] = r;
		a[1] = y;
		a[2] = B;
		b[0] = 'R';
		b[1] = 'Y';
		b[2] = 'B';
		ord[0] = 0;ord[1]=1;ord[2]=2;
		sort(ord,ord+3,cmp);
		if(a[ord[2]]-a[ord[1]]>a[ord[0]])
			printf("Case #%d: IMPOSSIBLE\n", casen);
		else
		{
			printf("Case #%d: ", casen);
			re(i,1,a[ord[2]]-a[ord[1]])
				printf("%c%c", b[ord[0]],b[ord[2]]);
			re(i,1,a[ord[0]]-(a[ord[2]]-a[ord[1]]))
				printf("%c%c%c",b[ord[0]],b[ord[1]],b[ord[2]]);
			re(i,1,a[ord[2]]-a[ord[0]])
				printf("%c%c", b[ord[1]],b[ord[2]]);
			printf("\n");
		}
	}
//	fclose(stdin);fclose(stdout);
	return 0;
}
