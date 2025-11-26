#include <stdio.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#define SEM_KEY 0x4324

union semun
{
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

int main()
{
    int pid, s, i, semid, ret;
    union semun su;
    // create a semaphore with single counter
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
    // initialize semaphore to 0
    su.val = 0;
    ret = semctl(semid, 0, SETVAL, su);

    pid = fork();
    if (pid == 0) // child -- print Infotech
    {
        char *str = "Infotech\n";
        // P(sem);
        struct sembuf ops[1];
        ops[0].sem_num = 0;
        ops[0].sem_op = -1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);

        for (i = 0; str[i] != '\0'; i++)
        {
            putchar(str[i]);
            fflush(stdout);
            sleep(1);
        }
    }
    else // parent -- print Sunbeam
    {
        char *str = "Sunbeam\n";
        for (i = 0; str[i] != '\0'; i++)
        {
            putchar(str[i]);
            fflush(stdout);
            sleep(1);
        }
        // V(sem);
        struct sembuf ops[1];
        ops[0].sem_num = 0;
        ops[0].sem_op = +1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);

        wait(&s);
        // destroy the semaphore
        semctl(semid, 0, IPC_RMID);
    }
    return 0;
}
