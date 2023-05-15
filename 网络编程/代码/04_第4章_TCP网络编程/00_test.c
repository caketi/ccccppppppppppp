#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <fcntl.h>
//将主机 加入到多播组 224.0.0.2  接受
int main()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	//让sockfd有一个固定的IP端口
	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8000);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr *)&my_addr,sizeof(my_addr));
	
	//将192.168.0.111 加入到多播组 224.0.0.2中
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.2");
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq,sizeof(mreq));
	
	while(1)
	{
		unsigned char buf[1500]="";
		recvfrom(sockfd,buf,sizeof(buf), 0,NULL,NULL);
		printf("buf=%s\n", buf);
	}
	
	close(sockfd);
	return 0;
}