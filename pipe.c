//Program to demonstrate the working of pipes
#include<stdio.h>
#include<string.h>
char string1[]="Hello,";
char string2[50];
int fd1[2], fd2[2];//fd1[0]--Reading end of first pipe fd1[1]--Writing end of first pipe
void main(){
    if(pipe(fd1)<0 || pipe(fd2)<0){
        printf("Pipe creation failed\n");
        exit(1);
    }

    int p=fork();
    if(p<0){
        printf("Child process creation failed\n");
        exit(1);
    }
    if(p>0){//Parent process
        printf("Enter a string(no spaces): ");
        scanf("%s",string2);
        write(fd1[1],string2,strlen(string2)+1);
        wait(NULL);
        char final_string[100];
        read(fd2[0],final_string,100);
        printf("%s\n",final_string);
    }
    else{//Child process
        char temp_string[100],return_string[100];
        read(fd1[0],temp_string,100);
        strcat(return_string,string1);
        strcat(return_string,temp_string);
        write(fd2[1],return_string,strlen(return_string)+1);

    }
        
    
}
