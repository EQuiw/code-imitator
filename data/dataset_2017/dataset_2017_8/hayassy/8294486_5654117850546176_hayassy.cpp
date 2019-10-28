#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm> // sort
#include <utility>
#include <cmath>

typedef long long ll;
using namespace std;

struct P{
  int n1,n2;
  string s1,s2;
  P(){};
  P(int n1,int n2,string s1,string s2): n1(n1), n2(n2), s1(s1), s2(s2) {};
  bool operator<(const P& rhs) const { return n1 < rhs.n1; };
};

int main(){
  ll T;
  cin >> T;

  for(int t=0; t<T; t++){
    ll N,R,O,Y,G,B,V;
    cin >> N >> R >> O >> Y >> G >> B >> V;

    if(R-G < 0 || Y-V < 0 || B-O < 0){ // cannot make RGR/YVY/BOB
      cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
      continue;
    }

    if(O==0 && Y==0 && B==0 && V==0 && R==G){
      cout << "Case #" << t+1 << ": ";
      for(int i=0; i<R; i++){ cout << "RG"; }
      cout << endl;
      continue;
    }
    if(R==0 && O==0 && G==0 && B==0 && Y==V){
      cout << "Case #" << t+1 << ": ";
      for(int i=0; i<Y; i++){ cout << "YV"; }
      cout << endl;
      continue;
    }
    if(R==0 && Y==0 && G==0 && V==0 && B==O){
      cout << "Case #" << t+1 << ": ";
      for(int i=0; i<B; i++){ cout << "BO"; }
      cout << endl;
      continue;
    }

    // num of RorRGR, num of RGR, "R", "RGR"
    vector<P> ps;
    ps.push_back(P(R-G, G, "R", "RGR"));
    ps.push_back(P(Y-V, V, "Y", "YVY"));
    ps.push_back(P(B-O, O, "B", "BOB"));
    // vector<tuple<int,int,string,string> > ts(3);
    // ts[0] = make_tuple(R-G, G, "R", "RGR");
    // ts[1] = make_tuple(Y-V, V, "Y", "YVY");
    // ts[2] = make_tuple(B-O, O, "B", "BOB");
    //    ts[1] = make_pair(Y-V, "Y");
    //    ts[2] = make_pair(B-O, "B");

    sort(ps.rbegin(), ps.rend());

    // for(int i=0; i<3; i++){
    //   cerr<< ps[i].n1<<" "<<ps[i].n2<<" "<<ps[i].s1<<" "<<ps[i].s2 <<endl;
    // }

    if(ps[0].n1 > ps[1].n1 + ps[2].n1){
      cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
      continue;
    }

    cout << "Case #" << t+1 << ": ";
    int rest = ps[1].n1 + ps[2].n1 - ps[0].n1;
    while(ps[0].n1 > 0 || ps[1].n1 > 0 || ps[2].n1 > 0){
      if(rest-- > 0){
        cout << (ps[0].n2 > 0 ? ps[0].s2 : ps[0].s1);
        cout << (ps[1].n2 > 0 ? ps[1].s2 : ps[1].s1);
        cout << (ps[2].n2 > 0 ? ps[2].s2 : ps[2].s1);
      } else if(ps[1].n1 > 0){
        cout << (ps[0].n2 > 0 ? ps[0].s2 : ps[0].s1);
        cout << (ps[1].n2 > 0 ? ps[1].s2 : ps[1].s1);
      } else {
        cout << (ps[0].n2 > 0 ? ps[0].s2 : ps[0].s1);
        cout << (ps[2].n2 > 0 ? ps[2].s2 : ps[2].s1);
      }
      ps[0].n1--; ps[1].n1--; ps[2].n1--;
      ps[0].n2--; ps[1].n2--; ps[2].n2--;
    }
    cout << endl;



    // while(ps[0].first > 0 || ps[1].first > 0 || ps[2].first > 0){
    //   if(rest > 0){
    //     cout << ps[0].second << ps[1].second << ps[2].second;
    //   } else if(ps[1].first > 0){
    //     cout << ps[0].second << ps[1].second;
    //   } else {
    //     cout << ps[0].second << ps[2].second;
    //   }

    //   ps[0].first--; ps[1].first--; ps[2].first--; rest--;
    // }
    // cout << endl;

  }

  return 0;
}
