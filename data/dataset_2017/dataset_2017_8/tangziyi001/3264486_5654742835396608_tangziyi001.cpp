/*
 *	
 *	Created by Ziyi Tang
 *
 */

//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <bitset>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
typedef vector<pi> vpi;
typedef vector<vpi> vvpi;
const int INF = 0x3f3f3f;
const ll INFL = (ll)1E18+10;
const int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))
#define MAXN 1000
#define MOD 1000000007

int main(){
	int T;
	cin >> T;
	REP(t,1,T+1){
		ll n,k;
		cin >> n >> k;
		priority_queue<ll> pq;
		pq.push(n);
		ll minp = n;
		ll maxp = n;
		while(k--){
			ll now = pq.top();
			pq.pop();
			if(now&1){
				pq.push((now-1)/2);
				pq.push((now-1)/2);
				minp = min(minp, (now-1)/2);
				maxp = min(maxp, (now-1)/2);
			}
			else{
				pq.push((now-1)/2);
				pq.push(now/2);
				minp = min(minp, (now-1)/2);
				maxp = min(maxp, now/2);
			}
		}
		printf("Case #%d: %lld %lld\n", t, maxp,minp);
	}
	return 0;
}