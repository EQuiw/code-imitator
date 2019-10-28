#include<iostream>
#include<algorithm>
#include <functional>
#include <vector>
#include <utility>
#include <iomanip>
#include <string>

int main(){
  int T; std::cin >> T;
  for(auto t=1; t<=T; ++t){
    int N, Q; std::cin >> N >> Q;
    std::vector<std::pair<long long int, long long int>> es(N);
    for(auto i=0; i<N; ++i)
      std::cin >> es[i].first >> es[i].second;
    std::vector<std::vector<long long int>> m(N);
    for(auto i=0; i<N; ++i){
      m[i] = std::vector<long long int>(N);
      for(auto j=0; j<N; ++j)
	std::cin >> m[i][j];
    }
    std::cout << "Case #" << t << ": ";
    for(auto i=0; i<Q; ++i){
      int u, v; std::cin >> u >> v;
      auto r = 0.;
      std::vector<double> dp(N, 999999999999999);
      dp[N-1] = 0.;
      for(auto j=N-2; j>=0; --j){
	auto k=j;
	long long int d = 0;
	auto min = 999999999999999.;
	while(k+1<N and es[j].first >= m[k][k+1]){
	  es[j].first -= m[k][k+1];
	  d += m[k][k+1];
	  auto t = d/(1.*es[j].second);
	  t += dp[k+1];
	  if(t<min)
	    min = t;
	  ++k;
	}
	dp[j] = min;
      }
      r = dp[0];
      std::cout << std::setprecision(10) << r;
      if(i<Q-1)
	std::cout << ' ';
    }
    std::cout << '\n';
  }
}
