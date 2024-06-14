#include "M.h"
#include "Time.h"

class Slae
{
    public:
        long int n;
        Matrix Sys;        // Изначальная система

        bool Flag_eig_val = 0;
        bool Flag_eig_vec = 0;
        long double *eigen_values;
        Matrix eigen_values_info;
        Matrix Eig_Vec;

        bool Flag_LU = 0;
        Matrix L, U;
        Matrix b;
        Matrix solve_LU;

        bool Flag_QR = 0;
        bool Flag_QR_Householder = 0;
        Matrix Q, R;
        Matrix Q_Householder, R_Householder;

        bool Flag_SVD = 0;
        Matrix U_SVD, S_SVD, V_SVD; // U, S, V

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
                    while (u.el[k][i] == 0 && k != n-1) k++;
                    if (k == n) break;
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
            Flag_LU = 1;
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

        void Solve_LU_Spesial()
        {
            long int solution_count = b.column;
            Matrix X(b);
            Matrix B = Gauss_B();

            long double *s = new long double[solution_count];
            for (long int i = 0; i < solution_count; ++i) X.el[n-i-1][i]=1;

            for (long int i = n-1-solution_count; i!=-1; --i)
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

        void QR()
        {
            long int n = Sys.row;
            long int m = Sys.column;
            Matrix q(Sys), r(m,m,'i'), h(Sys);
            long double coef;

            for (long int i = 0; i!=m; ++i)
            {
                // h_k = Sys_k - SUMM{ j=0, k-1} (Sys_k, q_k)*q_k

                h.copy_column(i, Sys, i);


                for (long int j = 0; j!=i; ++j) 
                {
                    coef = scl_column(Sys, i, q, j);
                    h.minus_column(i, q, j, coef);
                }
                
                q.k_norm(i, h, i);

            }
            Q = q;
            q.Transposition();
            R = mul(q, Sys);

            for (long int i = 0; i!=m; ++i)
                for (long int j = i+1; j!=m; ++j)
                    R.el[j][i] = 0;


            Flag_QR = 1;
        }

        void QR_Householder()
        {
            long int n = Sys.row;
            long int m = Sys.column;

            long int N = max(n, m);


            Matrix r(N,N,'z'), q(N,N,'i');
            for (long int j = 0; j < n; ++j) {
                for (long int k = 0; k < m; ++k) {
                    r.el[j][k] = Sys.el[j][k];
                }
            }

            long double coef;

            for (long int i = 0; i!=N; ++i)
            {
                Matrix P_i(N, N, 'i');
                Matrix v(N - i, 1, 'z');
                long double norm = 0;

                for (long int j = i; j < N; ++j) {v.el[j-i][0] = r.el[j][i]; norm += r.el[j][i]*r.el[j][i];}
                norm = sqrt(norm);
                if (v.el[0][0] <= 0) norm = -1;
                v.el[0][0] += norm;

                norm = 0;
                for (long int j = i; j < N; ++j) {norm += v.el[j-i][0]*v.el[j-i][0];}
                norm = 2/norm;

                for (long int j = i; j < N; ++j) {
                    for (long int k = i; k < N; ++k) {
                        P_i.el[j][k] -= norm*v.el[j-i][0]*v.el[k-i][0];
                    }
                }

                r = mul(P_i, r);
                q = mul(q, P_i);

            }
            
            q.mul(-1);
            r.mul(-1);

            for (long int i = 0; i!=N; ++i)
                for (long int j = i+1; j!=N; ++j)
                    r.el[j][i] = 0;

            if (n <= m) {
                Matrix q_temp(n,n,'z'), r_temp(n,m,'z');
                
                for (long int i = 0; i!=n; ++i) for (long int j = 0; j!=n; ++j) q_temp.el[j][i] = q.el[j][i];
                for (long int i = 0; i!=m; ++i) for (long int j = 0; j!=n; ++j) r_temp.el[j][i] = r.el[j][i];

                Q_Householder = q_temp;
                R_Householder = r_temp;
            }
            else {
                Matrix q_temp(n,m,'z'), r_temp(m,m,'z');
                for (long int i = 0; i!=m; ++i) for (long int j = 0; j!=n; ++j) q_temp.el[j][i] = q.el[j][i];
                for (long int i = 0; i!=m; ++i) for (long int j = 0; j!=m; ++j) r_temp.el[j][i] = r.el[j][i];

                Q_Householder = q_temp;
                R_Householder = r_temp;
            }
            Flag_QR_Householder = 1;
        }


        // Ищет вещественные собственные значения
        void Eigen_Values(double Epsilon = 0.0000001)
        {
            long int n = Sys.row;
            long int m = Sys.column;

            if (n != m) cout << "ERROR: Eigen_Values - a non-square matrix" << endl;

            long int N = min(n,m);
            
            Matrix o(n, m, 'z'), r(N,N,'z'), q(N,N,'z');
            
            if (!Flag_QR_Householder) this->QR_Householder();
            
            for (long int i = 0; i!= N; ++i)
                for (long int j = 0; j != N; ++j)
                {
                    r.el[i][j] = this->R_Householder.el[i][j];
                    q.el[i][j] = this->Q_Householder.el[i][j];
                }
                
            Matrix A(mul(q, r));
            Matrix B(mul(r, q));

            while (distinction_L2(A, B) > Epsilon)
            {
                Slae s(B);
                s.QR_Householder();

                q = s.Q_Householder;
                r = s.R_Householder;

                A = B;
                B = mul(r, q);
            }
        
            long double *temp = new long double[N];
            for (long int i = 0; i < N; i++) temp[i] = B.el[i][i];

            sort(temp, temp + N);

            eigen_values = new long double[N];
            for (long int i = 0; i < N; i++) eigen_values[i] = temp[N-i-1];

            Flag_eig_val = 1;

            Eigen_Values_Info(Epsilon);
        }
        // Составляет матрицу по кратности собственных значений
        void Eigen_Values_Info(double Epsilon = 0.0000001)
        {
            long int N = min(Sys.row, Sys.column);

            if (Sys.row != Sys.column) cout << "ERROR: Eigen_Values - a non-square matrix" << endl;

            long int h = 0, count = 1, step = 0;
            for (long int i = 1; i < N; ++i)
            {
                h = 0;
                while (i+h<N and eigen_values[i-1]-eigen_values[i] < Epsilon)
                {
                    eigen_values[i]=eigen_values[i-1];
                    ++h;
                }
                if (eigen_values[i-1]!=eigen_values[i]) count++;
            }

            Matrix temp(2, count, 'z');

            count = 1;
            for (long int i = 0; i < N; ++i)
            {
                if (eigen_values[i]==eigen_values[i+1])
                {
                    count++;
                }
                else 
                {
                    temp.el[0][step] = eigen_values[i];
                    temp.el[1][step] = count;
                    count = 1;
                    step++;
                }
            }

            eigen_values_info = temp;
        }
        // Запись собственных векторов соответственно упорядоченным (по неубыванию) собственным значениям
        void Eigen_Vectors()
        {
            
            if (Sys.row != Sys.column) 
                cout << "ERROR: Eigen_Values - a non-square matrix" << endl;
            else {
                if (!Flag_eig_val) this->Eigen_Values();
            
                Matrix X(n,n,'z');
                long int n = Sys.row, step = 0, k = 0;

                for (long int i = 0; i < this->eigen_values_info.column; ++i)
                {
                    Matrix I(n, n, 'i'), A(Sys), b(n, this->eigen_values_info.el[1][i], 'z');
                    I.mul(this->eigen_values_info.el[0][i]);
                    A -= I;
                    Slae s(A);

                    s.B(b);

                    s.LU();
                    
                    s.Solve_LU_Spesial();

                    k = this->eigen_values_info.el[1][i];

                    step += k;
                    for (long int i = step-k; i != step; ++i)
                        for (long int j = 0; j != n; ++j) 
                            X.el[j][i] = s.solve_LU.el[j][i-step+k];
                }

                Eig_Vec = X;
            }
            
        }

        // // Работает, но не полностью очищает память !!!!!!!!!!!
        // void SVD()
        // {
        //     long int n = Sys.row;
        //     long int m = Sys.column;
        //     long int N = min(n,m);

        //     Matrix A(Sys), A_t(Sys), P(m, m, 'z');
        //     A_t.Transposition();
        //     P = mul(A_t, A);

        //     Slae p(P);
        //     p.Eigen_Vectors();

        //     Matrix s(n,m,'i');
        //     Matrix v(m, m, 'z');

        //     for (long int i = 0; i!=N; ++i) s.el[i][i] *= sqrt(p.eigen_values[i]);

        //     long double norm = 0;
        //     for (long int i = 0; i!=m; ++i)
        //     {
        //         for (long int j = 0; j!=m; ++j) norm += p.Eig_Vec.el[j][i]*p.Eig_Vec.el[j][i];
        //         norm = sqrt(norm);

        //         for (long int j = 0; j!=m; ++j) v.el[j][i] = p.Eig_Vec.el[j][i]/norm;
        //         norm = 0;
        //     }

        //     Matrix s_t(s);
        //     s_t.Transposition();

        //     Matrix u(n, n, 'z');
        //     u = mul(A, v);
        //     for (long int i = 0; i != n; ++i)
        //         for (long int j = 0; j != n; ++j)
        //             u.el[j][i] = u.el[j][i] / s.el[i][i];

        //     Matrix u_temp(n, n, 'i');
        //     for (long int i = 0; i!=m; ++i) for (long int j = 0; j!=n; ++j) u_temp.el[j][i] = u.el[j][i];

        //     U_SVD = u_temp;
        //     S_SVD = s;
        //     V_SVD = v;
        // }


        // Не работает с прямоугольными матрицами
        void SVD()
        {
            Matrix A(Sys), A_t(Sys), P(n, n, 'z');
            A_t.Transposition();
            P = mul(A_t, A);
            Slae p(P);
            p.Eigen_Vectors();

            Matrix s(n,n,'i'), v(n,n,'z');
            for (long int i = 0; i!=n; ++i) s.el[i][i] *= sqrt(p.eigen_values[i]);

            long double norm = 0;
            for (long int i = 0; i!=n; ++i)
            {
                for (long int j = 0; j!=n; ++j) norm += p.Eig_Vec.el[j][i]*p.Eig_Vec.el[j][i];
                norm = sqrt(norm);

                for (long int j = 0; j!=n; ++j) v.el[j][i] = p.Eig_Vec.el[j][i]/norm;
                norm = 0;
            }

            Matrix s_t(s);
            s_t.Transposition();

            Matrix u(n, n, 'z');
            u = mul(A, v);
            for (long int i = 0; i != n; ++i)
                for (long int j = 0; j != n; ++j)
                    u.el[j][i] = u.el[j][i] / s.el[i][i];



            U_SVD = u;
            S_SVD = s;
            V_SVD = v;
        }
};

void M_LU_Solve(Matrix a, Matrix b, bool time = false, bool out_put = false)
{
    Time t; 

    Slae A(a);

    A.B(b);

    A.LU();

    A.Solve_LU();

    if (out_put)
        A.solve_LU.Display();

    if (time)
        t.Past_Time();

}


