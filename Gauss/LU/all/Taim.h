#include <iostream>
#include <unistd.h>
#include <ctime>
using namespace std;

class Taim
{
    private: 
        int seconds;
    public:
        Taim() : seconds(time(NULL)) {}

        void Past_Time()
        {
            int t = time(NULL);

            cout << "Прошло " << (t - seconds) / 60 << " м. " << (t - seconds) % 60 << " с. " << endl; 
        }

};