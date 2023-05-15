#include<stdio.h>
#include<string.h>
#include<sys/socket.h>//socket
#include<sys/types.h>
#include<netinet/in.h>//struct sockaddr_in
#include<arpa/inet.h>//inet_pton
#include<pthread.h>
//./aout 9000

void *my_send_fun(void *arg)//arg=&sockfd
{
	int sockfd = *(int *)arg;
	
	struct sockaddr_in dst_addr;
	bzero(&dst_addr,sizeof(dst_addr));
	dst_addr.sin_family = AF_INET;
	
	while(1)
	{
		
		//获取键盘输入
		char buf[128]="";
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1]=0;//去掉换行符
		
		if(strncmp(buf,"sayto", 5)==0)
		{
			//sayto 192.168.0.111 8000
			unsigned short port = 0;
			char ip[16]="";
			sscanf(buf,"sayto %s %hd", ip, &port );
			dst_addr.sin_port = htons(port);
			inet_pton(AF_INET, ip, &dst_addr.sin_addr.s_addr);
			continue;
		}
		else//要发送的消息
		{
			sendto(sockfd, buf, strlen(buf),0,\
			(struct sockaddr *)&dst_addr, sizeof(dst_addr));
		}
		
	}
	return NULL;
}
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("please input:./a.out 8000\n");
		return 0;
	}
	
	//创建一个通信的套接字
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
		return 0;
	}
	
	//给套接字sockfd绑定一个固定的IP以及端口信息
	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(atoi(argv[1]));
	bind(sockfd, (struct sockaddr *)&my_addr,sizeof(my_addr));
	
	//创建一个发送线程
	pthread_t tid;
	pthread_create(&tid,NULL, my_send_fun, (void *)&sockfd);
	pthread_detach(tid);
	
	//接受线程
	while(1)
	{
		char buf[128]="";
		struct sockaddr_in from;
		socklen_t len = sizeof(from);
		recvfrom(sockfd,buf,sizeof(buf),0,\
		(struct sockaddr *)&from, &len);
		
		unsigned short port = ntohs(from.sin_port);
		char ip[16]="";
		inet_ntop(AF_INET,&from.sin_addr.s_addr, ip,16);
		printf("来至%s:%hu %s\n",ip,port,buf);
	}
	return 0;
}