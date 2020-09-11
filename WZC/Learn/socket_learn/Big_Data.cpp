int server_sock,client_sock;
    socklen_t server_len,client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds,testfds;
    server_sock=socket(AF_INET,SOCK_STREAM,0);
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(3334);
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);
    server_len=sizeof(server_address);
    bind(server_sock,(struct sockaddr *)&server_address,server_len);
    listen(server_sock,5);
    
    FD_ZERO(&readfds);
    FD_SET(server_sock,&readfds);
    while(1){
        char ch[20];
        char buffer[256];
        char block[1024];
        int fd,n;
        FILE *fp;
        int nread;
        time_t t;
        testfds=readfds;
        printf("server waiting/n");
        result=select(FD_SETSIZE,&testfds,(fd_set *)0,(fd_set *)0,(struct timeval *)0);
        if(result<1){
            perror("server5");
            exit(1);
        }
        for(fd=0;fd<FD_SETSIZE;fd++){
            if(FD_ISSET(fd,&testfds)){
                if(fd==server_sock){
                  client_len = sizeof(struct sockaddr_in);
                  client_sock=accept(server_sock,(struct sockaddr *)&client_address,&client_len);
                  FD_SET(client_sock,&readfds);
                  printf("adding client on fd %d /n",client_sock);
                }else{
                    ioctl(fd,FIONREAD,&nread);
                    if(nread==0){
                        close(fd);
                        FD_CLR(fd,&readfds);
                        printf("removing client on fd %d/n",fd);
                    }else{
                        n = read(fd,buffer,255);
                        if (n < 0)
                             printf("ERROR reading from socket");
                        printf("%s",buffer);
			//读取一个文件发送到客户端
                        fp=fopen("/home/wyt/test","r");
                        while(!feof(fp)){
				//分段发送
                            fgets(block,sizeof(block),fp);
                            send(fd,block,sizeof(block),0);
                            //write(fd,block,sizeof(block));
                        }
                        fclose(fp);
                    }
                }
            }
        }
    }



//client1.cpp程序
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <iostream>
using namespace std;
int main(int argc, char** argv) {
    struct sockaddr_in address;
    int client_sock;
    char ch[20]="my name is client/0";
    int len,result;
    char in[5];
    int n,tmp;
    char buffer[1024];
    client_sock=socket(AF_INET,SOCK_STREAM,0);
    address.sin_addr.s_addr=inet_addr("127.0.0.1");  
    address.sin_family=AF_INET;
    address.sin_port=htons(3334);
    len=sizeof(address);
    result=connect(client_sock,(struct sockaddr *)&address,len);
    if(result==-1){
        printf("error!");
        exit(-1);
    }
    n=write(client_sock,"abc/n",6);
    if(n<0){
        printf("error write/n");
    }
    bzero(buffer,1024);
   //进行循环读取数据	
    while(tmp=recv(client_sock,buffer,sizeof(buffer),0)){
        if(tmp==-1) break;
        printf("%s",buffer);
    }
    exit(0);
    return (EXIT_SUCCESS);
}