#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
using namespace std;

int main(){
  ifstream infile;
  ofstream outfile;
  infile.open("horse.in");
  outfile.open("horse.txt");
  double i,j,t,n,p,d,speed;
  infile >> t;
  for (i=0;i<t;i++){
    infile >> d >> n;
    vector<pair<double,double> > hs;
    for (j=0;j<n;j++){
      infile >> p >> speed;
      hs.push_back(make_pair(p,speed));
    }
    sort(hs.begin(),hs.end());
    double minp=hs[0].first,mins=hs[0].second;
    for (j=1;j<hs.size();j++){
      if ((hs[j].first-minp)/(mins-hs[j].second)>=0 && 
         ((hs[j].first-minp)/(mins-hs[j].second))*mins+minp<=d){
        minp=hs[j].first;
        mins=hs[j].second;
      }
      else break;
    }
    outfile << "Case #" << (int) i+1 << ": ";
    outfile << setprecision(6) << fixed << d/((d-minp)/mins) << endl;
  }
  return 0;
}
