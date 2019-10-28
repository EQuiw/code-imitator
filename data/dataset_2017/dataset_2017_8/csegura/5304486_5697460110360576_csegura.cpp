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

int N, P;
int R[100], Q[100][100];

void getServes(int p, int ing, int &minServes, int &maxServes){
	minServes = (Q[ing][p] * 10) / (R[ing] * 11);
	if ((Q[ing][p] * 10) % (R[ing] * 11) != 0){
		minServes++;
	}
	maxServes = (Q[ing][p] * 10) / (R[ing] * 9);
}

bool isCompatible(int i, int j){
	int minFirst, maxFirst, minSecond, maxSecond;
	getServes(i, 0, minFirst, maxFirst);
	getServes(j, 1, minSecond, maxSecond);
	if ((minFirst <= maxFirst) && (minSecond <= maxSecond)){
		if ((maxFirst < minSecond) || (maxSecond < minFirst)){
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

int getScore(vector<int> &assignment){
	int sc = 0;
	for (int i = 0; i < assignment.size(); i++){
		if (isCompatible(i, assignment[i])){
			sc++;
		}
	}
	return sc;
}

int main(){
	int tests;
	cin >> tests;
	for (int t = 0; t < tests; t++){
		cin >> N >> P;
		for (int i = 0; i < N; i++){
			cin >> R[i];
		}
		for (int i = 0; i < N; i++){
			for (int j = 0; j < P; j++){
				cin >> Q[i][j];
			}
		}
		if (N == 2){
			vector<int> assignment;
			for (int i = 0; i < P; i++){
				assignment.push_back(i);
			}
			int score = 0;
			do {
				score = max(score, getScore(assignment));
			} while(next_permutation(assignment.begin(), assignment.end()));
			cout << "Case #" << (t+1) << ": " << score << endl;
		} else if (N == 1){
			int score = 0;
			for (int i = 0; i < P; i++){
				int minS, maxS;
				getServes(i, 0, minS, maxS);
				if (minS <= maxS){
					score++;
				}
			}
			cout << "Case #" << (t+1) << ": " << score << endl;
		}
	}
}
