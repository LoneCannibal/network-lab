//Program to test message queue with parent and child process
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
struct msg_queue{
    long msg_type;
    char msg_text[100];
}message;
void main(){
    int key,msg_id;
    key=ftok("progfile",65);
    msg_id=msgget(2222,0666|IPC_CREAT);
    if(msg_id==-1){
        printf("Message queue could not  be created\n");
        exit(1);
    }
    int f=fork();
    if(f==-1){
        printf("Child process could not be created\n");
        exit(1);
    }
    if(f==0){//Child process
        strcpy(message.msg_text,"Hi, parent");
        message.msg_type=1;
        msgsnd(msg_id,&message,sizeof(message),0);
        strcpy(message.msg_text,"");
        msgrcv(msg_id,&message,sizeof(message),1,0);
        printf("Parent process sent:  %s\n",message.msg_text);
    }
    else if(f>0){//Parent process
        msgrcv(msg_id,&message,sizeof(message),1,0);
        printf("Child process sent:  %s\n",message.msg_text);
        strcpy(message.msg_text,"Hello, child");
        message.msg_type=1;
        msgsnd(msg_id,&message,sizeof(message),0);
        
    }
}