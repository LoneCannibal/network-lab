//Program to implement interprocess communication using shared memory(Writer)
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
void main(){
    int key=ftok("shmfile",65);
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    char *str=(char*)shmat(shmid,(void*)0,0);
    printf("Enter data to write: ");
    gets(str);
    shmdt(str);
}