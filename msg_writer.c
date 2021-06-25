//Program to implement interprocess communication using message queue
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
char string1[]="Hello";
struct msg_queue{
    long msg_type;
    char msg_txt[100];
}message;
void main(){
    int key,msg_id;
    key=ftok("progfile",65);
    msg_id=msgget(key, 0666|IPC_CREAT);
    if(msg_id<0){
        printf("Message queue could not be created");
        exit(1);
    }
    message.msg_type=1;
    printf("Write a word: ");
    scanf("%s",message.msg_txt);
    msgsnd(msg_id,&message,sizeof(message),0);

}