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
#include <iomanip>

using namespace std;

int main(){
	int tests;
	cin >> tests;
	for (int t = 0; t < tests; t++){
		int N, K;
		cin >> N >> K;
		double U;
		cin >> U;
		double numbers[N+1];
		for (int i = 0; i < N; i++){
			cin >> numbers[i];
		}
		numbers[N] = 1;
		sort(numbers, numbers + N);
		for (int i = 0; i < N; i++){
			double change = numbers[i+1] - numbers[i];
			double totalChange = (i + 1) * change;
			if (totalChange <= U){
				U -= totalChange;
				for (int j = 0; j <= i; j++){
					numbers[j] = numbers[i+1];
				}
			} else {
				double mod = U / (i + 1);
				for (int j = 0; j <= i; j++){
					numbers[j] += mod;
				}
				break;
			}
		}
		double prob = 1;
		for (int i = 0; i < N; i++){
			prob *= numbers[i];
		}
		cout << "Case #" << (t+1) << ": " << fixed << setprecision(8) << prob << endl;
	}
}
