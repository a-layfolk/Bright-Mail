#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void *test(void *p)
{
    sleep(5);
    cout << "end sleep" << endl;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, test, NULL);
    // pthread_detach(tid);
    for (int i = 0; i < 10; i++)
    {
        sleep(1);
        cout << "sleep " << i << " second." << endl;
    }
    cout << "fuck" << endl;
}