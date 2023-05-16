#include<stdio.h>
#include<sys/socket.h>
#include<netinet/ether.h>
int main()
{
	//创建一个链路层 通信的原始套接字 -- 可以接收本机网卡上所有的数据帧 sudo!!!
	int fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	printf("fd = %d\n", fd);
	
	close(fd);
	return 0;
}
