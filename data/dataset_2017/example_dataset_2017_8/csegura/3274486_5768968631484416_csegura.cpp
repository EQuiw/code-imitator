#include <iostream>
#include <sstream>
#include <numeric>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>
#include <strings.h>
#include <string.h>
#include <math.h>
#include <iomanip>

using namespace std;

int main(){
	int tests;
	cin >> tests;
	for (int t = 0; t < tests; t++){
		long long N, K;
		cin >> N >> K;
		vector < pair < long, long> > pancakes;
		for (int i = 0; i < N; i++){
			long long r, h;
			cin >> r >> h;
			pancakes.push_back(make_pair(r, h));
		}
		sort(pancakes.begin(), pancakes.end());
		double solution = 0;
		for (int firstSelected = 0; firstSelected < pancakes.size(); firstSelected++){
			long long r = pancakes[firstSelected].first;
			double heightSol = 2 * M_PI * pancakes[firstSelected].first * pancakes[firstSelected].second;
			int selected = 1;
			vector < double > admisibleValues;
			for (int i = firstSelected - 1; i >= 0; i--){
				admisibleValues.push_back(2 * M_PI * pancakes[i].first * pancakes[i].second);
			}
			sort(admisibleValues.begin(), admisibleValues.end());
			for (int i = (int)(admisibleValues.size()) - 1; i >= 0; i--){
				if (selected == K)
					break;
				selected++;
				heightSol += admisibleValues[i];
			}
			double sol = heightSol + M_PI * r * r;
			solution = max(solution, sol);
		}
		cout << "Case #" << fixed << setprecision(8) << (t+1) << ": " << solution << endl;
	}
}
