#include "Matrix.h"

using namespace std;


// class Taim
// {
//     private: 
//         int seconds;
//     public:
//         Taim() : seconds(time(NULL)) {}
//         void Past_Time()
//         {
//             int t = time(NULL);
//             cout << "Прошло " << (t - seconds) / 60 << " м. " << (t - seconds) % 60 << " с. " << endl; 
//         }
// };

// int main()
// {
//     // use time() with NULL argument
//     Taim t;
//     sleep(3);
//     t.Past_Time();
//     sleep(3);
//     t.Past_Time();
//     return 0;
// }

class Slae
{
    public:
        long int n;
        Matrix Sys;
        Matrix L, U;
        Matrix b;
        Matrix solve;

        Slae();

        void System(const Matrix& A) { Sys = A; }
        void B(const Matrix& A) { b = A; }

        void LU()
        {
            long int n = Sys.row;
            Matrix u(Sys), l(n,n,'e');
            long double a;
            long double b;
            for (long int i=0; i!=n; ++i)
            {
                if (u.el[i][i] == 0)
                {
                    long int k = i;
                    while (u.el[k][i] == 0 && k != n) k++;
                    if (k == n+1) break;
                    u.swap(i, k);
                }
                else if (u.el[i][i] != 0)
                {
                    a = u.el[i][i];
                    for (long int j=i+1; j!=n; ++j)
                    {
                        b = u.el[j][i];
                        l.el[j][i] = b/a;
                        for (long int k=i; k!=n; ++k)
                            u.el[j][k] -= u.el[i][k]*b/a;
                    }
                }
            U = u;
            L = l;
            }
        }

        Matrix Gauss_B()
        {
            long int solution_count = b.column;
            Matrix B(b);

            long double *s = new long double[solution_count];

            for (long int i = 0; i!=n; ++i)
            {
                for (long int j = 0; j!=solution_count; ++j)
                    s[j] = 0;

                for (long int j = 0; j!=i+1; ++j)
                    for (long int k = 0; k!=solution_count; ++k)
                        s[k] += B.el[j][k]*L.el[i][j];

                for (long int k = 0; k!=solution_count; ++k)
                    B.el[i][k] = (b.el[i][k] - s[k])/L.el[i][i];
            }

            return B;
        }

        void Solve_LU() 
        {
            long int solution_count = b.column;
            Matrix X(b);
            Matrix B = Gauss_B();
            B.Display();
        }
};


int main() 
{
    int N = 4;
    Slae l1;

    Matrix G(N,N,'g');
    Matrix b(N,2,'g');

    G.Display();
    b.Display();

    l1.System(G);
    l1.B(b);

    l1.LU();

    l1.Solve_LU();


}



