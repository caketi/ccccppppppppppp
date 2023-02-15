#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// ./client 192.168.2.6 50001
int main(int argc, char* argv[]){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("make socket error\n");
        return -1;
    }
    // 定义一个存放自己IP地址的结构体
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    
    // 将IP地址和端口号存放进结构体中
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(atoi(argv[3]));// 端口号
    
    inet_pton(AP_INET, argv[1], &server_addr.sin_addr); // IP地址

    // 服务器绑定自己的IP地址
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // 将绑定好的套接字设置为监听套接字
    listen(sockfd, 5);
    // 定义一个存放连接对象的IP地址和端口号等信息的结构体
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    bzero(&client_addr, client_addr_size);
    // 创建一个TCP套接字

    // 准备一个存放对方IP地址和端口号的结构体

    // 连接对方的监听套接字
    return 0;
}
