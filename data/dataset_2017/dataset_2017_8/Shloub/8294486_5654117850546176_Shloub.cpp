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
    int N, R, O, Y, G, B, V; std::cin >> N >> R >> O >> Y >> G >> B >> V;
    std::string s(N, 'N');
    auto ok = true;
    for(auto i=0; i<N-1; ++i){
      auto cmax = 'R';
      auto max = R;
      if(B > max){
      	cmax = 'B';
      	max = B;
      }
      if(Y > max){
      	cmax = 'Y';
      	max = Y;
      }
	
      if((!i and O) or (i and O and s[i-1]=='B')){
	--O;
	s[i] = 'O';
	if(!i and B){
	  --B;
	  s[N-1] = 'B';
	} 
	continue;
      }
      if((!i and G) or (i and G and s[i-1]=='R')){
	--G;
	s[i] = 'G';
	if(!i and R){
	  --R;
	  s[N-1] = 'R';
	} 
	continue;
      }
      if((!i and V) or (i and V and s[i-1]=='Y')){
	--V;
	s[i] = 'V';
	if(!i and Y){
	  --Y;
	  s[N-1] = 'Y';
	} 
	continue;
      }
      if(i and s[i-1]=='O' and B){
	--B;
	s[i] = 'B';
	continue;
      }
      if(i and s[i-1]=='G' and R){
	--R;
	s[i] = 'R';
	continue;
      }
      if(i and s[i-1]=='V' and Y){
	--Y;
	s[i] = 'Y';
	continue;
      }
      if(!i){
      	s[i] = cmax;
      	if(cmax=='B')
      	  --B;
      	if(cmax=='R')
      	  --R;
      	if(cmax=='Y')
      	  --Y;	
      	continue;
      }
      if(i and s[i-1] == 'R'){
	if(B>Y or (B==Y and s[0]=='B')){
	  s[i] = 'B';
	  --B;
	}
	else{
	  s[i] = 'Y';
	  --Y;
	}
	continue;
      }
      if(i and s[i-1] == 'B'){
	if(R>Y or (R==Y and s[0]=='R')){
	  s[i] = 'R';
	  --R;
	}
	else{
	  s[i] = 'Y';
	  --Y;
	}
	continue;
      }
      if(i and s[i-1] == 'Y'){
	if(B>R or (B==R and s[0]=='B')){
	  s[i] = 'B';
	  --B;
	}
	else{
	  s[i] = 'R';
	  --R;
	}
	continue;
      }
      if(i < N-1)
	ok = false;
    }
    if(B){
      s[N-1] = 'B';
      --B;
      if(s[0] == 'B' or s[0] == 'V' or s[0] == 'G')
	ok = false;
      if(s[N-2] == 'B' or s[N-2] == 'V' or s[N-2] == 'G')
	ok = false;
    }
    if(R){
      s[N-1] = 'R';
      --R;
      if(s[0] == 'R' or s[0] == 'V' or s[0] == 'O')
	ok = false;
      if(s[N-2] == 'R' or s[N-2] == 'V' or s[N-2] == 'O')
	ok = false;
    }
    if(Y){
      s[N-1] = 'Y';
      --Y;
      if(s[0] == 'Y' or s[0] == 'O' or s[0] == 'G')
	ok = false;
      if(s[N-2] == 'Y' or s[N-2] == 'O' or s[N-2] == 'G')
	ok = false;
    }
    if(G){
      s[N-1] = 'G';
      --G;
      if(s[0] != 'R')
	ok = false;
      if(s[N-2] != 'R')
	ok = false;
    }
    if(O){
      s[N-1] = 'O';
      --O;
      if(s[0] != 'B')
	ok = false;
      if(s[N-2] != 'B')
	ok = false;
    }
    if(V){
      s[N-1] = 'V';
      --V;
      if(s[0] != 'Y')
	ok = false;
      if(s[N-2] != 'Y')
	ok = false;
    }
    // if(t==12){
    //   std::cerr << s << '\n';
    //   std::cerr << R << ' ' << O << ' ' << Y << ' ' << G << ' ' << B << ' ' << V << '\n';
    // }
    auto m = std::min({R, O, Y, G, B, V});
    if(m<0)
      ok = false;
    auto M = std::max({R, O, Y, G, B, V});
    if(M>0)
      ok = false;
    if(s[N-1] == 'N')
      ok = false;
    for(auto i=0; i<N; ++i){
      if(s[i] == 'R' and s[(i+1)%N] == 'R')
	ok = false;
      if(s[i] == 'R' and s[(i+1)%N] == 'O')
	ok = false;
      if(s[i] == 'R' and s[(i+1)%N] == 'V')
	ok = false;
      if(s[i] == 'B' and s[(i+1)%N] == 'B')
	ok = false;
      if(s[i] == 'B' and s[(i+1)%N] == 'G')
	ok = false;
      if(s[i] == 'B' and s[(i+1)%N] == 'V')
	ok = false;
      if(s[i] == 'Y' and s[(i+1)%N] == 'Y')
	ok = false;
      if(s[i] == 'Y' and s[(i+1)%N] == 'G')
	ok = false;
      if(s[i] == 'Y' and s[(i+1)%N] == 'O')
	ok = false;
      if(s[i] == 'O' and s[(i+1)%N] != 'B')
	ok = false;
      if(s[i] == 'G' and s[(i+1)%N] != 'R')
	ok = false;
      if(s[i] == 'V' and s[(i+1)%N] != 'Y')
	ok = false;
    }
    if(!ok)
      s = "IMPOSSIBLE";
    std::cout << "Case #" << t << ": " << s << '\n';
  }
}
