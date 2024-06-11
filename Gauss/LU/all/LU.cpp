#include "Slae.h"

using namespace std;

int main()
{
    
    cout << setprecision(16);
    int N = 5;

    Matrix G(N,N,'g');
    Matrix b(N,2*N,'g');
    
    Slae l1(G);

    l1.QR_Householder();

    // l1.QR();
    

    // q.Transposition();

    // l1.Q.Display();
    // q.Display();

    // Matrix W = mul(q, l1.Q);
    // W.Display();

    // cout << l1.Q.el[2][2] << endl;

    // return 0;

/////////////////////////////
    // int N = 1;

    // cout << endl << "Решение СЛАУ для матрицы Гильберта (N x N) и правой " << endl << "части - той же матрицы Гильберта (N x N**2)" << endl << endl;
    // for (int i = 0; i != 4; ++i)
    // {
    //     N = 1;
    //     for (int j = 0; j != i; ++j)
    //         N *= 10;

    //     cout << "N = " << N << " - до решения " << endl;

    //     Matrix G(N,N,'g');
    //     Matrix b(N,2*N,'g');
        
    //     M_LU_Solve(G, b, 1, 0);
    // }
///////////////////////////
    // int N = 100;

    // Matrix G(N,N,'g');
    // Matrix b(N,2*N,'g');
    
    // Slae l1(G);

    // l1.B(b);

    // l1.LU();

    // l1.Solve_LU();

    // l1.solve_LU.Display();
///////////////////////////
    // int N = 4;

    // Matrix G(N, N, 'g');
    // Matrix L(N, N, 'i');
    // Matrix U(G);

    // LU(U, L);
    // U.Display();
    // Diag(U);

    // cout << L.type() << " " << U.type() << endl;
    // cout << L.det() << " " << U.det() << endl;
 
    // return 0;
}