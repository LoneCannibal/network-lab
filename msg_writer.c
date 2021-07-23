//Program to implement interprocess communication using message queue (Writer program)
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
struct msg_queue{
    long msg_type;
    char msg_text[100];
}message;
void main(){
    int key,msg_id;
    key=ftok("progfile",65);
    msg_id=msgget(2222,0666|IPC_CREAT);
    if(msg_id<0){
        printf("Message queue could not be created\n");
        exit(1);
    }
    while(1){
        printf("Program 1: ");
        fgets(message.msg_text,sizeof(message.msg_text),stdin);
        message.msg_type=1;
        msgsnd(msg_id,&message,sizeof(message),0);
        strcpy(message.msg_text,"");
        msgrcv(msg_id,&message,sizeof(message),1,0);
        printf("Program 2:  %s",message.msg_text);
        
    }

}