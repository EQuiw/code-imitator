#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <iostream>

int T, D, N;
const int MN = 1010;
const double EPS = 1e-7;

struct Horse {
	int pos;
	int spd;
	Horse() {
		pos = 0;
		spd = 0;
	}
	bool operator<(const Horse&b) const {
		return pos > b.pos;
	}
} h[MN];

struct Speed {
	int spd;
	double t;
	// change to speed t at time spd
	Speed(int _s=0, double _t=0.0f) {
		spd = _s;
		t = _t;
	}
};

std::vector<Speed> s[MN];

int main() {
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("A-small-attempt0.out", "w", stdout);
	
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++) {
		scanf("%d%d", &D, &N);
		for(int i=0; i<N; i++) {
			scanf("%d%d", &h[i].pos, &h[i].spd);
			s[i] = std::vector<Speed>();
		}
		std::sort(h, h+N);
		for(int i=0; i<N; i++) {
			s[i].push_back(Speed(1, 0));
			s[i].push_back(Speed(h[i].spd, 0));
			if(i == 0) {
				s[i].push_back(Speed(1, D+1));
				continue;
			}
			// adjust new
			int slen = (int)s[i-1].size(), si = 0;
			double prepos = (double)h[i-1].pos, nowpos = (double)h[i].pos;
			for(si=1; si<slen; si++) {
				double deltat = (s[i-1][si].t - s[i-1][si-1].t);
				double prep, nowp;
				prep = prepos + s[i-1][si-1].spd * deltat;
				nowp = nowpos + h[i].spd         * deltat;
				//printf("%d: hit at %d (%f %f)\n", i, si, prepos, nowpos);
				if(nowp+EPS > prep) {
					int newspd;
					double newt;
					newspd = s[i-1][si-1].spd;
					newt = (prepos-nowpos) / (h[i].spd-s[i-1][si-1].spd) + s[i-1][si-1].t;
					s[i].push_back(Speed(newspd, newt));
					break;
				}
				prepos = prep;
				nowpos = nowp;
			}
			for(; si<slen; si++) {
				s[i].push_back(s[i-1][si]);
			}
			s[i].push_back(Speed(1, D+1));
		}
		/*
		for(int i=0; i<N; i++) {
			printf("Horse %d:\n", i);
			printf("%d %d\n", h[i].pos, h[i].spd);
			for(int j=0; j<s[i].size(); j++) {
				printf(">speed %d time %.2f\n", s[i][j].spd, s[i][j].t);
			}
		}//*/
		double walked = (double)h[N-1].pos;
		double ans = 0.0f;
		int len = (int)s[N-1].size();
		for(int si=1; si<len; si++) {
			double deltat = (s[N-1][si].t - s[N-1][si-1].t);
			double walknxt;
			walknxt = walked + s[N-1][si-1].spd * deltat;
			//printf("walked %f walknxt %f %d\n", walked, walknxt, s[N-1][si-1].spd);
			if(walknxt+EPS > D) {
				ans = (D-walked) / s[N-1][si-1].spd + s[N-1][si-1].t;
				break;
			}
			walked = walknxt;
		}
		printf("Case #%d: %.6f\n", tc, D/ans);
	}
	return 0;
}
