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
using namespace std;

int main(){
	int tests;
	cin >> tests;
	for (int t = 0; t < tests; t++){
		string status;
		cin >> status;
		int K;
		cin >> K;
		int changed = 0;
		for (int i = 0; i < (int)(status.size()) - K + 1; i++){
			if (status[i] == '-'){
				changed++;
				for (int j = 0; j < K; j++){
					status[i+j] = (status[i+j] == '+')?'-':'+';
				}
			}
		}
		bool ok = true;
		for (int i = 0; i < status.size(); i++){
			if (status[i] == '-'){
				ok = false;
				break;
			}
		}
		cout << "Case #" << (t+1) << ": ";
		if (!ok){
			cout << "IMPOSSIBLE" << endl;
		} else {
			cout << changed << endl;
		}
	}
}
