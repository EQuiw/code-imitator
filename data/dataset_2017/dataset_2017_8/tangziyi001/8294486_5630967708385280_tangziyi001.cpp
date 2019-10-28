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
const ll INFL = (ll)1E18;
const int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))
#define MAXN 1000
#define MOD 1000000007

int main(){
	int T;
	cin >> T;
	REP(t,1,T+1){
		vpi all;
		int d,n;
		cin >> d >> n;
		REP(i,0,n){
			int k,s; cin >> k >> s;
			all.push_back(make_pair(k,s));
		}
		double tt = 0.0;
		REP(i,0,n){
			double ttt = ((double)d-all[i].first)/all[i].second;
			tt = max(tt, ttt);
		}
		printf("Case #%d: %.7f\n", t, (double)d/tt);
	}
	return 0;
}