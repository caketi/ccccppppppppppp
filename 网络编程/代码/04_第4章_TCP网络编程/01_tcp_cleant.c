#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <fcntl.h>
//TCP客户端
int main()
{
	//创建一个TCP套接字 SOCK_STREAM 默认主动连接服务器
	//socket函数创建的套接字 默认没有ip以及端口
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("sockfd = %d\n", sockfd);
	
	//bind是可选的
	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(9000);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd,(struct sockaddr *)&my_addr,sizeof(my_addr));
	
	//connect链接服务器
	struct sockaddr_in ser_addr;
	bzero(&ser_addr,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(8000);//服务器的端口
	ser_addr.sin_addr.s_addr = inet_addr("192.168.0.110");//服务器的IP
	//如果sockfd没有绑定固定的IP以及端口 在调用connect时候 系统给sockfd分配自身IP以及随机端口
	//阻塞 要经历三次握手 肉眼感受不出来
	connect(sockfd, (struct sockaddr *)&ser_addr,sizeof(ser_addr));
	
	//给服务器发送数据 send
	printf("发送的消息:");
	char buf[128]="";
	fgets(buf,sizeof(buf),stdin);
	buf[strlen(buf)-1]=0;
	send(sockfd, buf, strlen(buf), 0);
	
	//接收服务器数据 recv
	char msg[128]="";
	int recv_len = recv(sockfd, msg,sizeof(msg), 0);
	if(recv_len == 0)
	{
		close(sockfd);
		return 0;
	}
	printf("recv_len = %d\n", recv_len);
	printf("服务器的应答:%s\n", msg);
	
	//关闭套接字
	close(sockfd);
	return 0;
}