#ifdef VX_PRECOMPILED
    #include "precomp.h"
    typedef mpz_class big;
    // I use 4 cores :)
    #define MAX_THREADS 4
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
struct solver
{
    int D, N;
    vector<int> K, S;
    
    double intersectPoint(double x0, double m0, double x1, double m1)
    {
        if (m0 == m1) {
            // they'll never cross
            return 1e100;
        }
        //x = x0 + y*m0
        //x = x1 + y*m1
        //0 = (x0 - x1) + (m0 - m1)*y
        //y = (x1 - x0) / (m0 - m1)
        double y = (x1 - x0) / (m0 - m1);
        return x0 + y*m0;
    }
    bool validSpeed(double v)
    {
        for (int i = 0; i < N; i++) {
            double w = intersectPoint(0,v, K[i],S[i]);
            if (0.0 <= w && w < D) {
                //cout << "speed "<<v<<" is invalid for horse "<<i<<endl;
                //cout<< "w = "<<w<<endl;
                return false;
            }
        }
        return true;
    }
    
    double solve()
    {
        double lo = 0.0;  // P(lo) is true
        double hi = 1e30; //P(hi) is false
        for (int i = 0; i < 100000; i++) {
            double ha = (lo + hi) / 2;
            if ( validSpeed(ha) ) {
                lo = ha;
            } else {
                hi = ha;
            }
        }
        return lo;
    }
    void init() { }
    void read() {
        cin >> D >> N;
        K.resize(N);
        S.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> K[i] >> S[i];
        }
    }
    #if MAX_THREADS > 1
        ofstream cout;
    #endif
    void write(int cn) {
        double x = solve();
        cout << "Case #"<<cn<<": ";
        cout.precision(10);
        cout.setf(ios::fixed, ios::fixed);
        cout << x <<endl;
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
