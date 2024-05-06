#include "Slae.h"

int main()
{
    int N = 4;

    Matrix G(N,N,'g');
    Matrix b(N,2*N,'g');

    Slae l1(G);

    l1.B(b);

    l1.LU();

    l1.Solve_LU();

    l1.solve_LU.Display();

    return 0;


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