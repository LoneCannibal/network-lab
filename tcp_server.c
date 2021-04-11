#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8080
#define SA struct sockaddr
void chat(int sockfd)
{
    char buff[100];
    int n;
    while(strcmp("exit",buff)!=0)
    {
        strcpy(buff,"\n");
        read(sockfd,buff,sizeof(buff));
        printf("Client: %s\n",buff);
        strcpy(buff,"\n");
        printf("Server: ");
        scanf("%[^\n]%*c", buff);
        write(sockfd,buff,sizeof(buff));
    }
    printf("EXIT command detected\n");
}
int main()
{
    int sockfd,connfd,len;
    struct sockaddr_in servaddr, cli;
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        printf("Socket could not be created\n");
        exit(0);
    }
    printf("Socket was created successfully\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORT);
    if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))==-1)
    {
        printf("Failed to bind socket with IP and port\n");
        exit(0);
    }
    printf("Socket bind was successful\n");
    if((listen(sockfd,5))!=0)
    {
        printf("Listen failed\n");
        exit(0);
    }
    printf("Server is listening\n");
    len=sizeof(cli);
    connfd=accept(sockfd, (SA*)&cli,&len);
    if(connfd==-1)
    {
        printf("Server accept failed\n");
        exit(0);
    }
    printf("Server is accepting data\n");
    chat(connfd);
    close(sockfd);
    return 0;
}