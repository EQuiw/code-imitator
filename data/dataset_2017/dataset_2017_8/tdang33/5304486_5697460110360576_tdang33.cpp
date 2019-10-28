#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>


using namespace std;

void backtrack(vector<bool> & used, vector<vector<int>> & Q, int p, int k,int  & result, vector<vector<vector<int>>> & range) {
    result = max(result, k);
    if (k >= p) return;
    if (range[0][k][0] <= range[0][k][1]){
        for (int m=0;m<p;m++) {
            if (used[m] == false && range[1][m][0] <= range[1][m][1] &&  max(range[0][k][0], range[1][m][0]) <= min(range[0][k][1], range[1][m][1])) {
                used[m] = true;
                backtrack(used, Q, p, k+1, result, range);
                used[m] = false;
            }
        }
    }
}

int solve(vector<vector<int>> & Q, vector<int> & R, int n, int p) {
    vector<vector<vector<int>>> range(n, vector<vector<int>>(p, vector<int>(2)));
    for (int i1 = 0; i1<n;i1++){
        for(int i2=0;i2<p;i2++){
            long long u = Q[i1][i2], a = R[i1];
            double low = u/(1.1*a);
            // cout << low <<endl;
            range[i1][i2][0] = ceil(low);
            // cout << "range " << range[i1][i2][0] <<endl;
            double high = u/(0.9*a);
            range[i1][i2][1] = floor(high);
        }
    }
    int result = 0;
    if (n == 1) {
        for (int i=0;i<p;i++){
            if (range[0][i][0] <= range[0][i][1]) result++;
        }
    } else if (n==2){
        vector<bool> used(p, false);
        backtrack(used, Q, p, 0, result, range);
    }
    // cout << ceil()<<endl;
    return result;
}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        long long n; cin >> n;
        long long p; cin >> p;
        vector<int> R(n);
        for (int j = 0; j < n; j++) {
            cin >> R[j];
        }
        vector<vector<int>> Q(n, vector<int>(p));
        for (int i1=0;i1<n;i1++){
            for(int i2=0;i2<p;i2++){
                cin >> Q[i1][i2];
            }
        }
        cout << "Case #" << i+1 <<": "<< solve(Q,R,n,p) <<endl;
    }
    return 0;
}
