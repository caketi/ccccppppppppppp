#include<stdio.h>
#include<sys/socket.h>
int main()
{
	//创建一个UDP通信的套接字
	//AF_INET IPv4
	//SOCK_DGRAM udp套接字
	//0 自动获取协议类别
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("sockfd = %d\n", sockfd);
	
	//关闭套接字
	close(sockfd);
	return 0;
}