/*
    C socket server example
*/
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#include<PaillierCryptoSystem.h>

extern "C"
{
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
};

int getPubKey(const string &name,PaillierCryptoSystem &pcs)
{
  ifstream fin("/home/shaobozhong/pub_key.txt");
  string str;
  while(getline(fin,str))
  {
    string keyName,n,g;
    istringstream stream(str);
    stream>>keyName>>n>>g;
    if (keyName==name) 
    {
      //cout<<n<<g<<endl;
      pcs.setN(n);
      pcs.setG(g);
      fin.close();
      return 0;
    }
  }
  fin.close();
  return 1;
}
int main(int argc , char *argv[])
{
    PaillierCryptoSystem pcs;
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr =inet_addr("192.168.149.129");
    server.sin_port = htons(5005 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 5);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    while(1)
    {
      client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
      if (client_sock < 0)
      {
        perror("accept failed");
        return 1;
      }
      puts("Connection accepted");
     
     memset(client_message,0,2000);
      //Receive a message from client
     while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
      { 
          //Send the message back to client
          puts(client_message);
          string str=client_message;
          string name;
          string data;
          puts("ok");
          istringstream stream(str);
          stream>>name>>data;
          cout<<name<<" "<<data<<endl;
          memset(client_message,0,2000);
          if (data=="")
          {
            cout<<"data wrong"<<endl;
            strcpy(client_message,"data wrong");
            send(client_sock ,client_message ,strlen(client_message),0);
            memset(client_message,0,2000);

          }
          if (1==getPubKey(name,pcs)) 
          {
            strcpy(client_message,"wrong user");
            send(client_sock ,client_message ,strlen(client_message),0);
            memset(client_message,0,2000);
          }
          else
          {
          PaillierPlaintext pp(data);
          PaillierCiphertext pc=pcs.enc_u(pp);
          strcpy(client_message,pc.get_str().c_str());

          send(client_sock ,client_message ,strlen(client_message),0);
          memset(client_message,0,2000);
          }
      }
     
      if(read_size == 0)
      {
          puts("Client disconnected");
          fflush(stdout);
      }
      else if(read_size == -1)
      {
          perror("recv failed");
      }
      close(client_sock);
    }
return 0;
}
