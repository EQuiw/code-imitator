#ifdef VX_PRECOMPILED
    #include "precomp.h"
    typedef mpz_class big;
    // I use 4 cores :)
    #define MAX_THREADS 3
#else
    #include <bits/stdc++.h>
    #include<sys/stat.h>
    #include<unistd.h>
    // http://gmplib.org/ (uncomment if solution uses big nums)
    // most likely you'll get an error about mpz_class not being declared...
    //#include "gmpxx.h"
    #define big mpz_class
    // I figure that when other people want to test my solutions they shouldn't
    // get the whole multi-threaded mess that requires and deletes folders and files...
    #define MAX_THREADS 1
#endif

#define for_each(q,s) for(typeof(s.begin()) q=s.begin(); q!=s.end(); q++)
typedef long long int64;
#define long int64

using namespace std;

//=========================================================
// program:
//
const int MAX = 1001;
struct solver
{
    int N;
    int R,O,Y,G,B,V;
    char mem[3][MAX][MAX][MAX]; //we got the RAMs
    char s;
    
    bool rec(int last, int A, int B, int C)
    {
        if ( (A < 0) || (B < 0) || (C < 0)) {
            return 0;
        }
        char & res = mem[last][A][B][C];
        if (res == -1) {
            res = 0;
            int p = N - (A + B + C);
            if (p == N) {
                // picked all of them
                res = 1;
            } else {
                for (int i = 0; i < 3; i++) {
                    if ( (i != last) && ( (p != N-1) || (i != s) ) ) {
                        if (rec(i, A - (i==0), B - (i==1), C - (i==2))) {
                            res = 1;
                        }
                    }
                }
            }
        }
        return res;
    }
    string solve()
    {
        assert(O == 0);
        assert(G == 0);
        assert(V == 0);
        if ( R != 0) {
            R--;
            s = 0;
        } else if (Y != 0) {
            Y--;
            s = 2;
        } else if (B != 0) {
            B--;
            s = 1;
        }
        memset(mem, -1, sizeof(mem));
        if (rec(s, R,B,Y)) {
            // build it
            string res(N, '?');
            const string chars = "RBY";
            res[0] = chars[s];            
            int last = s;
            int A = R, C = Y;
            for (int p = 1; p < N; p++) {
                for (int i = 0; i < 3; i++) {
                    if ( (i != last) && ( (p != N-1) || (i != s) ) ) {
                        // try it
                        if (rec(i, A - (i==0), B - (i==1), C - (i==2) )) {
                            // a valid one
                            res[p] = chars[i];
                            last = i;
                            A -= (i==0);
                            B -= (i==1);
                            C -= (i==2);
                            break;
                        }
                    }
                }
                assert(res[p] != '?');                
            }
            return res;
        } else {
            return "IMPOSSIBLE";
        }
    }
    void init() { }
    void read() {
        cin >> N >> R >> O >> Y >> G >> B >> V;
    }
    #if MAX_THREADS > 1
        ofstream cout;
    #endif
    void write(int cn) {
        string s = solve();
        cout << "Case #"<<cn<<": "<<s << endl;
    }
    
};

//=========================================================
// I/O:
//
#if MAX_THREADS > 1
    void run(const char* x)
    {
        int r = system(x);
        cerr<<x<<" "<<"("<<r<<")"<<endl;
    }
#endif

int main(int argc, const char* argv[])
{
    int TestCases, mode;
    #if MAX_THREADS == 1
        // Simple and straight forward. 
        cin >> TestCases;
        solver * theSolver = new solver;
        theSolver->init();
        for (int i=1; i<= TestCases; i++) {
            theSolver->read();
            theSolver->write(i);
        }
        delete theSolver;    
    #else
        cin>>TestCases;
        //-------------------------------------------
        // Copy the whole input to a file...
        ofstream f;
        f.open("tests/.input");
        f << cin.rdbuf();
        f.close();
        // Yeah...wipe that folder... Cause we will need its files to be empty
        run("rm ./tests/.t*");
        int k = 0;
        mode = 0;
        // We create some extra threads...
        while (k < MAX_THREADS) {
            if ( fork() == 0 ) {
                mode = k + 1;
                break;
            }
            k++;
        }
        // Reopen the input, this happens for each of the threads...
        if (mode != 0) {
            assert( freopen( "tests/.input","r",stdin) );
        }
    
        solver * theSolver = new solver;
        theSolver->init();
        for (int i=1; i<= TestCases; i++) {
            // Yeah, I don't like this much either
            ofstream f;
            char fn1[200], fn2[200];
            sprintf(fn1, "tests/.test.%d", i);
            sprintf(fn2, "tests/.test.%d.done", i);
            if (mode == 0) {
                // main thread shall just join stuff together as it becomes ready
                struct stat stFileInfo;
                // When a thread finishes a test case, it writes the .done file
                // Wait for that...
                while ( stat(fn2, &stFileInfo) !=0 ) {
                    sleep(1);
                }
                // Now copy the output file...
                ifstream f(fn1);
                cout << f.rdbuf();
            } else {
                // The trick is to make each thread read all the inputs, whether
                // it will process it or not...
                theSolver->read();
                // If fn1 exists, it is being processed already. Else process it
                f.open(fn1, ios_base::out | ios_base::in);
                if ( !f ) {
                    theSolver->cout.open(fn1, ios_base::out);
                    cerr << "[" << i << "/"<<TestCases<<"] "<<mode << endl;
                    theSolver->write(i);
                    theSolver->cout.close();
                    f.open(fn2);
                    f << "1" << endl;
                }
            }
        }
        delete theSolver;
    #endif

    
    return 0;
}
