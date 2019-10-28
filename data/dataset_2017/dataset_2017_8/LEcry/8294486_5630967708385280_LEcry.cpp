//============================================================================
// Name        : A.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <iostream>
#include <set>
#include <queue>
#define MAXN 100050
#define eps 1e-8
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
using namespace std;
int k[MAXN],s[MAXN];
int main() {
	freopen("A-small-attempt0.in","r",stdin);
	freopen("A-small-attempt0.out","w",stdout);
	int tt,ri=0;
	scanf("%d",&tt);
	while(tt--){
		int d,n;
		scanf("%d%d",&d,&n);
		double ans=-1;
		for(int i=0;i<n;++i)
		{
			scanf("%d%d",&k[i],&s[i]);
			double tmp=1.0*d*s[i]/(1.0*d-k[i]);
			if(ans<0||tmp<ans)
				ans=tmp;
		}
		printf("Case #%d: %.8lf\n",++ri,ans);

	}
	return 0;
}
