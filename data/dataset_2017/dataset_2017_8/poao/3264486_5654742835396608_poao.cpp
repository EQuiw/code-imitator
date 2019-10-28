#include <cstdio>
#include <queue>
#include <algorithm>

struct Elem {
	int l, r;
	bool operator<(const Elem&b) const {
		if(r-l != b.r-b.l) {
			return r-l < b.r-b.l;
		}
		else {
			return b.l > b.r;
		}
	}
	Elem(int _l=0, int _r=0) {
		l = _l;
		r = _r;
	}
};

std::priority_queue<Elem> heap;
int T, N, K;

int main() {
	freopen("C-small-1-attempt0.in", "r", stdin);
	freopen("C-small-1-attempt0.out", "w", stdout);
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++) {
		scanf("%d%d", &N, &K);
		while(!heap.empty()) heap.pop();
		heap.push(Elem(0,N+1));
		Elem now;
		int lb, rb;
		for(int i=0; i<K; i++) {
			now = heap.top();
			heap.pop();
			int mid = (now.l+now.r)/2;
			lb = mid - now.l - 1;
			rb = now.r - mid - 1;
			heap.push(Elem(now.l, mid));
			heap.push(Elem(mid, now.r));
			//printf("pick %d\n", mid);
		}
		printf("Case #%d: %d %d\n", tc, std::max(lb, rb), std::min(lb, rb));
	}
	return 0;
}

