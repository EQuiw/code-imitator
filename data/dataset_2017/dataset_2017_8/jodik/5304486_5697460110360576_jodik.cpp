#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <array>
#include <algorithm>
#include <cmath>
#include <complex>
#include <map>
#include <cassert>
#include <functional>
#include <stdarg.h>

#define FOR(i, a, b) for(int i=(a);i<=(b);i++)
#define FORD(i, a, b) for(int i=(a);i>=(b);i--)
#define REP(i, b) for(int i=0;i<(b);i++)
#define ll long long
#define nl printf("\n")

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

char opposite(char c){
    if(c=='-')
        return '+';
    else
        return '-';
}


vector<ll> rece;
vector<vector<ll> > pack;
vector<vector<pair<ll, ll> > > ranges;
vector<int > indicies;
ll t, n, p;

bool porovnaj(const pair<ll, ll>& a, const pair<ll, ll>& b){
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}

int main(){
    //string m;
    cin>>t;

    for (ll tt = 0; tt < t; tt++){
        cin>>n>>p;
        rece.clear();
        rece.resize(n);
        pack.clear();
        pack.resize(n, vector<ll>(p));
        indicies.clear();
        indicies.resize(n, 0);
        ranges.clear();
        ranges.resize(n, vector<pair<ll, ll> >(p));

        REP(i,n){
            cin>>rece[i];
        }

        REP(i, n){
            REP(j, p){
                cin>>pack[i][j];
            }
        }

        REP(i, n){
            rece[i] *= 11*9;
            REP(j, p){
                ll mi = (pack[i][j] * 10)*9;
                ll ma = (pack[i][j] * 10)*11;
                //cout<<mi<<" "<<ma<<" "<<rece[i]<<endl;
                ll mi2 = mi/rece[i];
                ll ma2 = ma/rece[i];
                if(mi % rece[i]) mi2++;
                ranges[i][j] = make_pair(mi2,ma2);
             //   cout<<"ranges "<<i<<" "<< j<<": "<<mi2<<", "<<ma2<<endl;
            }
            //cout<<endl;
        }

        REP(i, n){
            sort(ranges[i].begin(), ranges[i].end(), porovnaj);
        }

        int res = 0;

        bool con = true;
        while(con){
            ll max_mi = 0;
            ll min_ma = 100000000ll;
            REP(i, n){
                int in = indicies[i];
                max_mi = max(ranges[i][in].first, max_mi);
                min_ma = min(ranges[i][in].second, min_ma);
            }
            if(max_mi <= min_ma){
                res++;
                REP(i, n){
                    indicies[i]++;
                    //cout<<indicies[i]<<" "<<p<<endl;
                    if(indicies[i] >= p){
                        con = false;
                        break;
                    }
                }
            }
            else {
                REP(i, n){
                    int in = indicies[i];
                    if(ranges[i][in].second < max_mi){
                        indicies[i]++;
                        if(indicies[i] >= p){
                            con = false;
                            break;
                        }
                    }
                }
            }
        }



        cout<<"Case #"<<(tt+1)<<": "<<res<<endl;
    }
}