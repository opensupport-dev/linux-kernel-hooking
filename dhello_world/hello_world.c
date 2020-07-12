#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/time.h>
 
 
/* When you want to know your pid on user app running user space, it'll be used.

//using namespace std;

pid_t gettid() { return syscall( __NR_gettid ); }
 
int main(int argc, char * argv[])
{
        unsigned long pid = 0;

        pid = gettid();
        printf("Current pid: %lu\n", pid);
        //printf("Current pid %lu\n", (unsigned long)gettid());

        return 0;
}
*/

int main(int argc, char * argv[])
{
        char sHelloMsg[] = {"Hello world!\n"};
        printf(sHelloMsg);
        return 0;
}

