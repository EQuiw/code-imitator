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
	long long n,k,m,r,b;
	cin>>T;
	for (t=1;t<=T;t++) {
		cin>>n>>k;
		printf("Case #%d: ",t);
		for (b=1;b*2<=k;b*=2);
		n-=b;
		k-=b;
		m=n/b;
		r=n%b;
		if (k>r)
		m--;
		r=m/2;
		m-=r;
		cout<<m<<" "<<r<<endl;
	}
    return 0;
}
