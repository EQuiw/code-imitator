#include<iostream>
#include<cstdio>
#include<cstring>
#define rep(i, l, r) for(int i = l; i <= r; ++i)
using namespace std;
typedef long long ll;
ll f[21][12][2], t[21], pow[21];
int tot, ans[21];
ll dp(int step, int last, int flag){
	if(f[step][last][flag] != -1) return f[step][last][flag];
	if(step == 0) return f[step][last][flag] = 1;
	ll ret = 0;
	if(flag){
		for(int i = last; i <= 9; ++i){
			ll tmp = dp(step-1, i, flag);
			if(tmp) ans[step] = i;
			ret += dp(step -1, i, flag);
		}
	}
	else {
		for(int i = last; i <= t[step]; ++i){
			ll tmp = dp(step - 1, i, i < t[step] ? 1 : 0);
			if(tmp) ans[step] = i;
			ret += dp(step -1, i, i < t[step] ? 1 : 0);
		}
	}
	//printf("f[%d][%d][%d] = %lld\n", step, last, flag, ret);
	return f[step][last][flag] = ret;
}
int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	cin >> T;
	pow[1] = 1;
		rep(i, 2, 19)
			pow[i] = pow[i - 1] * 10;
		
	rep(cas, 1, T){
		ll n, tmp = 0;
		cin >> n;
		tot = 0;
		for(ll tmp = n; tmp; tmp /= 10){
			t[++tot] = tmp % 10;
		}
		memset(f, -1, sizeof(f));
		ll value = dp(tot, 0, 0);
		printf("Case #%d: ", cas);
		rep(i, 1, tot)
			tmp += ans[i] * pow[i];
		cout << tmp << '\n';
	}
	return 0;
}
