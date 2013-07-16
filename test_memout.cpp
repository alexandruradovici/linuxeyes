#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

int main()
{
    key_t K = ftok ("/",'E');
    int mem_id = shmget (K, 5, IPC_CREAT|0666);
    char *str_memout = (char*)shmat (mem_id, NULL, 0);
    if (str_memout!=NULL) printf ("str_memout: %s\n", str_memout);
}
