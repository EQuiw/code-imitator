#include <bits/stdc++.h>

using namespace std;
const int N = 1111;
struct horse {
	double k, s;
}h[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int cas = 1; cas <= T ; cas ++){
		double d, n;
		double mt = -1;
		scanf("%lf%lf", &d, &n);
		double k,s;
		while(n--) {
			scanf("%lf%lf", &k, &s);
			mt = max((d-k)/s, mt);
		}
		printf("Case #%d: %.6f\n", cas, d/mt);
	}
	return 0;
}