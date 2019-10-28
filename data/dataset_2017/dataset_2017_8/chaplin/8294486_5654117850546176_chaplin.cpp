//============================================================================
// Name        : jam17cpp.cpp
// Author      : Javier Sardinas
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <queue>
#include <bits/stdc++.h>

using namespace std;


void p2017_1b_a_small() {
	int t, d, n;
	int k, s;
	cin >> t;
	for (int cas = 1; cas <= t; cas++){
		cin >> d >> n;
		double t = 0.0, maxt = 0.0;
		for (int i = 0; i < n; ++i){
			cin>>k>>s;
			t = 1.0*(d - k)/s;
			if (t > maxt)maxt = t;
		}

		printf("Case #%d: %6lf\n", cas, 1.0*d/maxt);
		//cout << "Case #" << cas << ": " << 1.0*d/maxt << "\n";
	}
}

void p2017_1b_b_small() {
	int t, n, r, g, b, y, o, v;
	cin >> t;
	for (int cas = 1; cas <= t; cas++){
		cin>>n>>r>>o>>y>>g>>b>>v;
		if (r+y < b || r+b<y || y+b<r)cout << "Case #" << cas << ": IMPOSSIBLE\n";
		else{
			int x1,x2,x3;
			char c1,c2,c3;
			if(r>y){
				if(r>b){
					x1=r, c1='R';
					if(y>b)
						x2=y,c2='Y',x3=b,c3='B';
					else
						x3=y,c3='Y',x2=b,c2='B';
				}
				else{
					x1=b, c1='B',x2=r,c2='R',x3=y,c3='Y';
				}
			}
			else{
				if(y>b){
					x1=y, c1='Y';
					if(r>b)
						x2=r,c2='R',x3=b,c3='B';
					else
						x3=r,c3='R',x2=b,c2='B';
				}
				else
					x1=b, c1='B',x2=y,c2='Y',x3=r,c3='R';
			}


			cout << "Case #" << cas << ": ";
			char last=c1;
			while(x1 || x2 || x3){
				cout<<last;
				if (last==c1){
					x1--;
					last = x2>=x3?c2:c3;
				}
				else if (last==c2){
					x2--;
					last = x1>=x3?c1:c3;
				}
				else {
					x3--;
					last = x1>=x2?c1:c2;
				}
			}
			cout<<"\n";
		}
	}
}
void p2017_1b_c_small() {
	int t;
	cin >> t;
	for (int cas = 1; cas <= t; cas++){

		cout << "Case #" << cas << ":\n";
	}
}

int main() {

	p2017_1b_b_small();

	return 0;
}
