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
		string line;
		cin >> line;
		int sz = line.size();
		int idx = -1;
		for(int i = sz-1; i > 0; i--){
			char now = line[i];
			char pre = line[i-1];
			int num = (int)now-(int)('0');
			int prenum = (int)pre-(int)('0');
			if(num < prenum){
				idx = i;
				prenum = prenum-1;
				if(prenum == -1) prenum = 9;
			}
			line[i-1] = prenum+(int)('0');
			//cout << line << endl;
		}
		if(idx != -1){
			REP(i,idx,sz){
				line[i] = '9';
			}
		}
		ll re = stoll(line);
		printf("Case #%d: %lld\n", t, re);
	}
	return 0;
}