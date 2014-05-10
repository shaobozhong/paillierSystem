/*
    C ECHO client example using sockets
*/
#include<iostream>
extern "C"{
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
};

int main()
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("192.168.149.129");
    server.sin_family = AF_INET;
    server.sin_port = htons(5005 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1)
    {
        printf("Enter message : ");
        scanf("%s" , message);
        
        //Send some data
        printf("%d\n",strlen(message));
        if( send(sock , message , strlen(message), 0) < 0) 
        {
            puts("Send failed");
            return 1;
        }
        memset(message,0,1000);
        //Receive a reply from the server
        memset(server_reply,0,2000);
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
         
        puts("Server reply :");
        puts(server_reply);
    }
    
    close(sock);
    return 0;
}
