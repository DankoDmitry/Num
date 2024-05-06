#include "Matrix.h"
#include "Taim.h"

class Slae
{
    public:
        long int n;
        Matrix Sys;
        Matrix L, U;
        Matrix b;
        Matrix solve_LU;

        Slae(Matrix A) : Sys(A) { n = A.row;}

        void System(Matrix A) { Sys = A; }
        void B(const Matrix& A) { b = A; }

        void LU()
        {
            long int n = Sys.row;
            Matrix u(Sys), l(n,n,'i');
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
            Matrix B(n, solution_count, 'z');

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

            long double *s = new long double[solution_count];
            
            for (long int i = n-1; i!=-1; --i)
            {
                for (long int j = 0; j!=solution_count; ++j)
                    s[j] = 0;

                for (long int j = i+1; j!=n; ++j)   // Почему от i+1 ?????
                    for (long int k = 0; k!=solution_count; ++k)
                        s[k] += X.el[j][k]*U.el[i][j];
                        
                for (long int k = 0; k!=solution_count; ++k)
                    X.el[i][k] = (B.el[i][k] - s[k])/U.el[i][i];
            }
            solve_LU = X;
        }
};



