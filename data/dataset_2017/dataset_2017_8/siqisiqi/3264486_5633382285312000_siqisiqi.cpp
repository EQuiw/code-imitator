#include <string>
#include <cstdio>
#include <iostream>
using namespace std ;

bool lessThan(string a, string b ) {
        if ( a.size() < b.size() ) return true;
        if ( a.size() > b.size() ) return false;
        // equal size
        for ( int i = 0 ; i < a.size() ; ++i ) {
                if ( a[i] < b[i] ) return true;
                if ( a[i] > b[i] ) return false;
        }
        // equal string
        return false;
}
void set( string &c, int st, int num ) {

        for ( int i = st ; i < c.size() ; ++i )
                c[i] = '0' + num;
}

string work(string s){

        string current = s;

        if ( s.size() == 1 ) return s;

        for ( int i = 0 ; i < s.size() ; ++i ) {
                current[i] = '1';
        }
        if ( lessThan(s,current) ) {        //      return "99999....9999" 
                for ( int i = 0 ; i < current.size() ; ++i ) current[i] = '9';
                current = current.substr(0, current.size()-1);
                return current;
        }

        for ( int i = 0 ; i < s.size() ; ++i ) {
        
                for ( int num = ( i == 0 ? 1 : current[i-1]-'0') ; num < 10 ; ++num ) {
                        set( current, i, num ); 
                        if ( lessThan(s,current) ) {
                                current[i] = num-1+'0';
                                break;
                        }
                }
        
        }
        return current;
}

int main() {

        int T ;
        cin >> T;
        for ( int test = 0 ; test < T ; ++test){
                string s ;
                cin >> s;
                string output = work(s);
                cout << "Case #" << test+1 << ": " << output << endl;
        }
        
        return 0;
}
