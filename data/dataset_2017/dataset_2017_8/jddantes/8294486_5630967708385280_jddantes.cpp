#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
pi input[1000];

int main(){
    int cases;
    scanf("%d", &cases);

    for(int e = 0; e<cases; e++){
        int D,N;
        scanf("%d %d", &D, &N);
        for(int i = 0; i<N; i++){
            int x,s;
            scanf("%d %d", &x, &s);
            input[i] = pi(x,s);
        }
        sort(input, input+N);

        double largest_time = 0;
        for(int i = 0; i<N; i++){
            int dist = D - input[i].first;
            int speed = input[i].second;
            double t = (double) dist / (double) speed;
            largest_time = max(largest_time, t);
        }

        double ans = (double) D / (double) largest_time;
        printf("Case #%d: %f\n", e+1, ans);
        

    }

    return 0;
}