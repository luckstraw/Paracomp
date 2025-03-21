#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        cout << "Hello from thread " << thread_id << endl;
    }
    return 0;
}