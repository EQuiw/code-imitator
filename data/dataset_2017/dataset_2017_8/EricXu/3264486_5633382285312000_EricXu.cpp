#include <iostream>
#include <fstream>
using namespace std;

int main(){
  ifstream infile;
  ofstream outfile;
  infile.open("tidy.in");
  outfile.open("tidy.txt");
  int i,j,k,t,n;
  infile >> t;
  for (i=0;i<t;i++){
    infile >> n;
    for (j=n;j>0;j--){
      int temp=j,num,previous=100;
      while (temp>0){
        num=temp%10;
        if (num>previous) break;
        previous=num;
        temp/=10; 
      }
      if (temp==0){
        outfile << "Case #" << i+1 << ": " << j << endl; 
        break;
      }
    }
  }
  return 0;
}
