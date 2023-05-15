#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<pthread.h>
//TCP并发ECHO服务器（并发回执服务器---客户端给服务器发啥 服务器就给客户端回啥）
void* deal_client_fun(void *arg)//arg = &new_fd
{
	//并发服务器的核心服务代码（各不相同）
	//通过arg获得已连接套接字
	int fd = *(int *)arg;
	while(1)//以下语句是服务器的核心代码
	{
		//获取客户端请求
		char buf[128]="";
		int len = recv(fd,buf,sizeof(buf), 0);
		if(len == 0)
			break;
		//回应客户端
		send(fd, buf, len, 0);
	}
	
	close(fd);
}
int main()
{
	//1、创建tcp监听套接字
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
	}
	//端口复用
	int yes = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(yes));
	
	//2、给TCP监听套接字 bind固定的IP以及端口信息
	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8000);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(sockfd, (struct sockaddr *)&my_addr,sizeof(my_addr));
	if(ret == -1)
	{
		perror("bind");
	}
	//3、调用listen 将sockfd主动变被动  同时创建链接队列
	listen(sockfd, 10);
	
	//4、提取完成链接的客户端 accept
	//accept调用一次 只能提取一个客户端
	while(1)
	{
		struct sockaddr_in cli_addr;
		socklen_t cli_len = sizeof(cli_addr);
		int new_fd = accept(sockfd,(struct sockaddr *)&cli_addr , &cli_len);
		
		//遍历客户端的信息ip port
		unsigned short port=ntohs(cli_addr.sin_port);
		char ip[16]="";
		inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr, ip, 16);
		printf("已有客户端:%s:%hu连接上了服务器\n", ip, port);
		
		//对每一个客户端 开启一个线程 单独的服务器客户端
		pthread_t tid;
		pthread_create(&tid,NULL, deal_client_fun, (void *)&new_fd);
		//线程分离
		pthread_detach(tid);
	}	
	
	//关闭监听套接字
	close(sockfd);
	
	return 0;
}