#include<stdio.h>
#include<sys/socket.h>
#include<netinet/ether.h>
#include <sys/ioctl.h>//ioctl
#include <net/if.h>//struct ifreq
#include <netpacket/packet.h>//struct sockaddr_ll
#include<pthread.h>
#include<unistd.h>//_exit
#include<string.h>//strncpy
// 0x0800: ip  
// 0x0806: arp
// 0x8035: rarp
// 1: arp请求 2：arp应答 3：rarp请求 4：rarp应答

// 以太网头部 arp协议头部
// 6    6    2         2 		 2 				1       1     2   6    4   6   4
// dmac smac frametype hardtype protocaltype  htypelen ptlen op smac sip dmac dip

void my_sendto(int sockfd, char *out, unsigned char *msg, int msg_len);
void *recv_msg(void *arg)
{
	int sockfd = (int)arg;
	while(1) // 网络环境复杂，多接受
	{
		unsigned char buf[1500]="";
		recvfrom(sockfd, buf,sizeof(buf), 0,NULL,NULL);
		
		if(ntohs(*(unsigned short *)(buf+12)) == 0x0806)//arp报文
		{
			if(ntohs(*(unsigned short *)(buf+14+6)) == 2)//应答
			{
				
				char mac[18]="";
				sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",
				buf[6+0],buf[6+1],buf[6+2],buf[6+3],buf[6+4],buf[6+5]);
				char ip[16]="";
				sprintf(ip,"%d.%d.%d.%d",\
				buf[28+0],buf[28+1],buf[28+2],buf[28+3]);
				printf("IP:%s--->MAC:%s\n",ip,mac);// 目的 - - 查询ip 对应的 mac
			}
		}
	}
	return NULL;
}
int main()
{
	//1、创建原始套接字
	int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(sockfd < 0)
	{
		perror("socket");
		return 0;
	}
	
	//msg存放arp请求报文
	unsigned char msg[]={
		/*mac报文头部 14B*/
		0xff,0xff,0xff,0xff,0xff,0xff,/*目的mac地址*/
		0x00,0x0c,0x29,0x79,0xf9,0x7f,/*源mac地址 根据自己修改 ubuntu_mac*/
		0x08,0x06,/*帧类型*/
		
		/*ARP报文头部 28B*/
		0x00,0x01,/*硬件类型*/
		0x08,0x00,/*协议类型*/
		6,/*硬件地址长度*/
		4,/*协议地址长度*/
		0x00,0x01,/*1 ARP请求*/
		0x00,0x0c,0x29,0x79,0xf9,0x7f,/*源mac地址 根据自己修改 ubuntu_mac*/
		192,168,0,111,/*源IP 根据自己修改 ubuntu_ip*/
		0x00,0x00,0x00,0x00,0x00,0x00,/*目的mac地址*/
		192,168,0,0/*目的IP*/
	};
	
	//创建线程接受arp应答 -- 《先接收防止应答没接上》
	pthread_t tid;
	pthread_create(&tid,NULL, recv_msg, (void *)sockfd);
	
	//发送arp请求帧数据
	int i=0; 
	for(i=1;i<255;i++) // 扫描网段 192.168.0.0 - 192.168.0.255 对应的 mac
	{
		msg[41]=i;
		my_sendto(sockfd, "eth0",msg, 42);
	}
	
	sleep(3);
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

	//原始套接字 组帧数据报文---》 从本机的哪块网卡sendto（倒数第二个参数）出去
}