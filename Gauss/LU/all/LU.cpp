#include "Slae.h"

using namespace std;

int main()
{

    cout << setprecision(16);
    int N = 3;

    Matrix G(N,N,'g');

    G.el[1][0] = 5;
    G.el[2][0] = 1;
    G.el[2][1] = 10;

    G.Display();

    Slae l1(G);


    l1.SVD();

    l1.U_SVD.Display();
    l1.S_SVD.Display();
    l1.V_SVD.Display();

    Matrix v(l1.V_SVD);
    v.Transposition();

    mul(mul(l1.U_SVD, l1.S_SVD), v).Display();












    // l1.LU();

    // l1.L.Display();
    // l1.U.Display();

    // mul(l1.L, l1.U).Display();









    // // Величина ошибки методов QR на основе унитарности Q
    // cout << setprecision(16);
    // int N = 100;
    // Matrix G(N,N,'g');
    // Matrix I(N,N,'i');
    // Slae l1(G);
    // l1.QR_Householder();
    // l1.QR();
    // // G.Display();
    // // l1.Q_Householder.Display();
    // // l1.R_Householder.Display();
    // // l1.Q.Display();
    // // l1.R.Display();
    // Matrix q(l1.Q);
    // q.Transposition();
    // cout << distinction_L2(I, mul(q, l1.Q)) << endl;
    // Matrix q_Householder(l1.Q_Householder);
    // q_Householder.Transposition();
    // cout << distinction_L2(I, mul(q_Householder, l1.Q_Householder)) << endl;






    
    // // G.el[1][1] = 0;
    // G.Display();


    // Slae l1(G);

    // l1.QR_Householder();

    // // l1.Q_Householder.Display();
    // l1.R_Householder.Display();

    // // mul(l1.Q_Householder, l1.R_Householder).Display();

    // l1.QR();
    

    // // q.Transposition();

    // l1.R.Display();
    // // q.Display();

    // // Matrix W = mul(q, l1.Q);
    // // W.Display();

    // // cout << l1.Q.el[2][2] << endl;

    // // return 0;

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
 
    return 0;
}