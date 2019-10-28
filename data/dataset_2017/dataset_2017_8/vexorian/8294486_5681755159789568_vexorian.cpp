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
    int N, Q;
    vector<int> E, S;
    int D[101][101];
    int U[101];
    int V[101];
    
    double solve()
    {
        assert(U[0] == 1);
        assert(V[0] == N);
        assert(Q == 1);        

        // from city 0 to N-1 ...
        double dp[100][100];
        for (int i = 0; i < N; i++) {
            dp[N-1][i] = 0.0;
        }
        for (int j = N-2; j >= 0; j--) {
            for (int h = 0; h <= j; h++) {
                long traveled = 0;
                for (int i = h; i < j; i++) {
                    traveled += D[i][i+1];                    
                }
                dp[j][h] = dp[j+1][j] +  D[j][j+1] / (double)S[j] ; // switch horse
                // keep the horse
                if ( traveled + D[j][j+1] <= E[h]) {
                    dp[j][h]= std::min( dp[j][h], D[j][j+1] / (double)S[h] + dp[j+1][h] ); 
                }
            }            
        }
        return dp[0][0];
    }
    void init() { }
    void read() {
        cin>> N >> Q;
        E.resize(N);
        S.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> E[i] >> S[i]; 
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> D[i][j];
            }
        }
        for (int i = 0; i < Q; i++) {
            cin >> U[i] >> V[i];
        }
        
    }
    #if MAX_THREADS > 1
        ofstream cout;
    #endif
    void write(int cn) {
        double r = solve();
        cout << "Case #"<<cn<<": ";
        cout.precision(10);
        cout.setf(ios::fixed, ios::fixed);
        cout << r << endl;
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
