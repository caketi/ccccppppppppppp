#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main()
{
	//1、创建一个tcp监听套接字
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//2、使用bind函数 给监听套接字 绑定固定的ip以及端口
	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8000);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
	
	//3、使用listen创建连接队列 主动变被动
	listen(sockfd, 10);
	
	//4、使用accpet函数从连接队列中 提取已完成的连接 得到已连接套接字
	struct sockaddr_in cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	int new_fd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
	//new_fd代表的是客户端的连接   cli_addr存储是客户端的信息
	char ip[16]="";
	inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr, ip,16);
	printf("客户端:%s:%hu连接了服务器\n",ip,ntohs(cli_addr.sin_port));
	
	//5、获取客户端的请求 以及 回应客户端
	char buf[128]="";
	recv(new_fd, buf,sizeof(buf),0);
	printf("客户端的请求为:%s\n",buf);
	
	send(new_fd,"recv", strlen("recv"), 0);
	
	
	//6、关闭已连接套接字
	close(new_fd);
	
	//7、关闭监听套接字
	close(sockfd);
	
	return 0;
}