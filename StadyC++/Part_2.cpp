#include <iostream>
using namespace std;

int main() 
{
    int N = 5;
    double** v = new double*[N];
    for (int i = 0; i < N; i++)
        {
            v[i] = new double[N];
            for (int j = 0; j < N; j++)
            {
                v[i][j] = i*i;
            }
        }

    swap(*(v+1), *(v+2));

    // double* text = v[3];
    // v[3]=v[4];
    // v[4]=text;
    
    
    
    for (int i = 0; i < N; i++)
        {
        for (int j = 0; j < N; j++)
            cout << v[i][j] << "   ";
        cout << endl;
        }

    return 0;
}