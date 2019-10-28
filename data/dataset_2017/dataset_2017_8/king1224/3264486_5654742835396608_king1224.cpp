#include <cstdio>
#include <queue>

using namespace std;

int main(){
	int T;
	long long N,K,tmp;
	scanf("%d",&T);
	for(int i=1;i<=T;++i){
		priority_queue<long long> q;
		scanf("%ld %ld",&N,&K);
		q.push(N);
		for(long long j=1;j<K;++j){
			tmp = q.top();
			q.pop();
			if(tmp == 1) break;
			q.push(tmp/2);
			q.push((tmp-1)/2);
		}
		tmp = q.top();
		printf("Case #%d: %ld %ld\n",i,tmp/2,(tmp-1)/2);
	}
	return 0;
}
