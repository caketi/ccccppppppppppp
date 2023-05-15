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
	//udp支持广播 arp dhcp ntp(网络时间协议) 不能tcp实现
	int sockfd = socket(AF_INET, SOCK_DGRAM,0);
	
	//让sockfd支持广播
	int yes = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes,sizeof(yes));
	
	//发送广播地址（目的地址 是广播地址）
	struct sockaddr_in dst_addr;
	bzero(&dst_addr,sizeof(dst_addr));
	dst_addr.sin_family = AF_INET;
	dst_addr.sin_port = htons(8000);
	dst_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
	//inet_pton(AF_INET,"255.255.255.255", &dst_addr.sin_addr.s_addr);
	
	char msg[]="i am broadcast";
	sendto(sockfd,msg,strlen(msg),0, \
	(struct sockaddr *)&dst_addr, sizeof(dst_addr));
	
	close(sockfd);
	return 0;
}