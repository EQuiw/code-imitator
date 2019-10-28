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

vector<pair<int, int> > starting;
vector<char > chars;
vector<string > pole;

bool dynamika(int znak_cislo, vector<pair<int,int> >& dolne, vector<pair<int,int> >& horne, int sucet){

    if(sucet > pole.size() * pole[0].size()){
        cout<<pole.size() * pole[0].size()<<endl;
        return false;
    }
    if (znak_cislo == starting.size()){
        cout<<"trying to testing"<<endl;
        if(sucet < pole.size() * pole[0].size()){
            return false;
        }
        cout<<"testing"<<endl;
        vector<vector<char> > pole2 = vector<vector<char> > (pole.size(), vector<char>(pole[0].size(), '?'));
        REP(i, horne.size()){
            cout<<chars[i]<<endl;
            for(int x = dolne[i].first; x < horne[i].first; x++){
                for(int y = dolne[i].second; y < horne[i].second; y++){
                    cout<<x<<" "<<y<<endl;
                    cout<<pole2[y][x]<<endl;
                    if(pole2[y][x] == '?'){
                        pole2[y][x] = chars[i];
                    }
                    else {
                        return false;
                    }
                }
            }
        }
        //cout<<"end testing"<<endl;
        REP(i, pole2[0].size()){
            REP(j, pole2.size()){
                cout<<pole2[j][i];
            }
            cout<<endl;
        }
        return true;
    }
    else {
        for (int x1 = 0; x1 < starting[znak_cislo].first + 1; x1++){
            REP(y1, starting[znak_cislo].second + 1){
                dolne.push_back(make_pair(x1,y1));
                for (int x2 = starting[znak_cislo].first + 1; x2 <= pole[0].size(); x2++){
                    for (int y2 = starting[znak_cislo].second + 1; y2 <= pole.size(); y2++){
                        horne.push_back(make_pair(x2,y2));
                        int vel = (x2-x1)*(y2-y1);
                        if(dynamika(znak_cislo+1, dolne, horne, sucet + vel)){
                            return true;
                        }
                        horne.pop_back();
                    }
                }
                dolne.pop_back();
            }
        }

    }
}

void solve(vector<string> pole){

    for(int i = 0; i < pole[0].size(); i++){
        char c_last = '?';
        bool has = false;
        for(int j = 0; j < pole.size(); j++){
            if(pole[j][i]!='?')
                c_last = pole[j][i];
            pole[j][i] = c_last;
        }

        c_last = '?';
        for(int j = pole.size() - 1; j>=0; j--){
            if(pole[j][i]!='?'){
                c_last = pole[j][i];
                has =true;
            }
            pole[j][i] = c_last;
        }

        if(!has && i > 0){
            for(int j = 0; j < pole.size(); j++){
                pole[j][i] = pole[j][i-1];
            }
        }

    }



    for(int i = pole[0].size()-2; i >= 0; i--){
        char c_last = '?';
        bool has = false;
        for(int j = pole.size() - 1; j>=0; j--){
            if(pole[j][i]!='?'){
                c_last = pole[j][i];
                has =true;
            }
            pole[j][i] = c_last;
        }

        if(!has){
            for(int j = 0; j < pole.size(); j++){
                pole[j][i] = pole[j][i+1];
            }
        }

    }

    REP(i, pole.size()){
        REP(j, pole[0].size()){
            cout<<pole[i][j];
        }
        cout<<endl;
    }

}

int main(){
    //string m;
    int t, k, m;
    cin>>t;
    for (int tt = 0; tt < t; tt++){
        chars.clear();
        cout<<"Case #"<<(tt+1)<<":"<<endl;
        cin>>m>>k;
        pole = vector<string>(m);
        vector<pair<int, int> > startings;
        REP(i, m){
            cin>>pole[i];
            REP(j,k){
                if(pole[i][j] != '?'){
                    startings.push_back(make_pair(i,j));
                    chars.push_back(pole[i][j]);
                }
            }
        }

        solve(pole);
    }
}