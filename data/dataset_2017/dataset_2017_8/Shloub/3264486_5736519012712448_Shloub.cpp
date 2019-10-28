#include<iostream>
#include<string>

int main(){
  int T; std::cin >> T;
  for(auto t=1; t<=T; ++t){
    std::string r {""};
    auto n = 0;
    std::string s; std::cin >> s;
    int k; std::cin >> k;
    for(auto i=0U; i<s.size(); ++i){
      if(s[i] != '+'){
	++n;
	for(auto j=i; j<i+k; ++j){
	  // std::cerr << t << ' ' << j << '\n';
	  if(j>=s.size()){
	    r = "IMPOSSIBLE";
	    break;
	  }
	  s[j] = (s[j] == '+') ? '-' : '+';
	}
	if(r == "IMPOSSIBLE")
	  break;
      }
    }
    if(r != "IMPOSSIBLE")
      r = std::to_string(n);
    std::cout << "Case #" << t << ": " << r << '\n';
  }
}
