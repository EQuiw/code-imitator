#include<iostream>
#include<string>

int main(){
  int T; std::cin >> T;
  for(auto t=1; t<=T; ++t){
    std::string r {""};
    std::string s; std::cin >> s;
    // std::cerr << s << '\n';
    auto ns = s;
    auto i = 0U;
    while((i<s.size()-1) and (s[i] <= s[i+1]))
      ++i;
    if(i == s.size()-1)
      r = s;
    else{
      --ns[i];
      while(i>0 and ns[i]<ns[i-1]){
	--i;
	--ns[i];
      }
      while(i+1<s.size()){
	++i;
	ns[i] = '9';
      }
      i = 0;
      while(ns[i] == '0')
	ns.erase(0, 1);
      r = ns;
    }
    std::cout << "Case #" << t << ": " << r << '\n';
  }
}
