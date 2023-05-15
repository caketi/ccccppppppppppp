#include<stdio.h>
#include<string.h>
#include<sys/socket.h>//socket
#include<sys/types.h>
#include<netinet/in.h>//struct sockaddr_in
#include<arpa/inet.h>//inet_pton
int main()
{
	//1、创建一个udp套接字
	int sockfd = socket(AF_INET, SOCK_DGRAM,0);
	
	//2、给套接字bind固定的信息
	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8000);//自身端口
	//INADDR_ANY 让系统自动寻找可用的本地IP地址
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY==0
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
	
	//2、发送数据
	//定义一个IPv4 目的地址结构 192.168.0.110 8080
	struct sockaddr_in dst_addr;
	//清空结构体
	//memset(&dst_addr,0,sizeof(dst_addr));
	bzero(&dst_addr,sizeof(dst_addr));
	dst_addr.sin_family = AF_INET;//协议
	//将主机字节序转换成网络字节序
	dst_addr.sin_port = htons(8080);//端口
	//将字符串"192.168.0.110" 转换成32位整形数据 赋值IP地址
	inet_pton(AF_INET,"192.168.0.110", &dst_addr.sin_addr.s_addr);
	
	sendto(sockfd,"hehe",strlen("hehe"),0, \
	(struct sockaddr *)&dst_addr , sizeof(dst_addr) );
	sleep(1);
	sendto(sockfd,"haha",strlen("haha"),0, \
	(struct sockaddr *)&dst_addr , sizeof(dst_addr) );
	//3、关闭套接字
	close(sockfd);
	return 0;
}