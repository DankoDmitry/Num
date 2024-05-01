#include <iostream>
using namespace std;

int main()
{
    int const N = 3;

    float Gilbert_maxrix[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            Gilbert_maxrix[i][j] = 1./(i+j+1) ;
        }
    }
    
    float** U = new float *[N];
    for (int i = 0; i < N; i++)
        U[i] = new float [N];

    float** L = new float *[N];
    for (int i = 0; i < N; i++)
        L[i] = new float [N];


    float B[N];
    for (int i = 0; i < N; i++) B[i] = 1.;

    for (int i = 0; i < N; i++) {
        if (Gilbert_maxrix[i][i] != 0.) {
            for (int j = i; j < N; j++) {
                L[j][i] = Gilbert_maxrix[j][i]/Gilbert_maxrix[i][i]; 
                for (int k = i; k < N; k++) {
                    U[j][k] = Gilbert_maxrix[j][k] - Gilbert_maxrix[j][i]*Gilbert_maxrix[j][k]/Gilbert_maxrix[i][i];
                }
            }
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            cout << L[j][i] << "   ";
        }
        cout << endl;
    }
    cout << endl;
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            cout << U[j][i] << "   ";
        }
        cout << endl;
    }

    return 0;
}
