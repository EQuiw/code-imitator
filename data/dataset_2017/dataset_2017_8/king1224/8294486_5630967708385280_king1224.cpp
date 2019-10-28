#include <cstdio>

int main(){
	int T;
	long long D,N,K,S;
	double tmp;
	double Max = 0;
	scanf("%d",&T);
	for(int i=1;i<=T;++i){
		Max = 0;
		scanf("%lld %lld",&D,&N);
		while(N--){
			scanf("%lld %lld",&K,&S);
			tmp = (double)(D-K)/(double)S;
			Max = tmp > Max ? tmp : Max;
		}
		printf("Case #%d: %lf\n",i,(double)D/Max);
	}
	return 0;
}
