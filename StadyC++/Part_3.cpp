#include <iostream>
using namespace std;

void print_matrix(double** X, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << X[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int main()
{
    int N = 3;
    double** numbers{new double*[N]{}};  
    // Выделяем память под двухмерный массив
    for (int i = 0; i < N; i++)
    {
        numbers[i] = new double[N]{};
    }
 
    // Ввод
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            numbers[i][j] = 1./(i+j+1);
        }
    }
    
    float B[N];
    for (int i = 0; i < N; i++) B[i] = 1.;

    // Объявление L и U
    double** U = new double *[N];
    for (int i = 0; i < N; i++)
        U[i] = new double [N];

    double** L = new double *[N];
    for (int i = 0; i < N; i++)
        L[i] = new double [N];


    for (int i = 0; i < N; i++) 
    {
        if (numbers[i][i] != 0.) 
        {
            for (int j = i; j < N; j++) 
            {
                L[j][i] = numbers[j][i]/numbers[i][i]; 
                for (int k = i; k < N; k++) {
                    U[j][k] = numbers[j][k] - numbers[j][i]*numbers[j][k]/numbers[i][i];
                }
            }
        }
    }

    

    // Вывод
    print_matrix(L, N);
    print_matrix(U, N);
    print_matrix(numbers, N);


    // Очистка памяти
    for (int i = 0; i < N; i++)
    {
        delete[] numbers[i];
        delete[] U[i];
        delete[] L[i];
    }
    delete[] numbers;
    delete[] U;
    delete[] L;
}