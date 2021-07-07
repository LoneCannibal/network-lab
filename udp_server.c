//Program to implement client server communication using UDP
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080
void chat(int sockfd){
    while(1){
        char buffer[200];
        struct sockaddr_in cliaddr;
        int n=recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, ( struct sockaddr *)&cliaddr,sizeof(cliaddr));
        printf("Client: %s\n",buffer);
        printf("Server: ");
        scanf("%[^\n]%*c", buffer);
        sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &cliaddr,sizeof(cliaddr));
        strcpy(buffer,"");
    }

}
int main(){
    struct sockaddr_in servaddr;
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);   
    if(sockfd==-1){
        printf("Socker creation failed\n");
        exit(1);
    }
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(PORT);
    if((bind(sockfd,&servaddr,sizeof(servaddr)))==-1)
    {
        printf("Failed to bind socket with IP and port\n");
        exit(0);
    }
    printf("Socket bind was successful\n");
    chat(sockfd);
}