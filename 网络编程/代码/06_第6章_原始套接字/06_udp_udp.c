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
#include <netinet/ip.h>//struct iphdr
#include <netinet/udp.h>//struct udphdr
void my_sendto(int sockfd, char *out, unsigned char *msg, int msg_len);
typedef struct
{
	u_int32_t saddr;//源IP
	u_int32_t daddr;//目的IP
	u_int8_t flag;//标记（0）
	u_int8_t type;//udp协议 17
	u_int16_t len;//长度
}WEIHDR;
unsigned short checksum(unsigned short *buf, int len)
{
	int nword = len/2;
	unsigned long sum;

	if(len%2 == 1)
		nword++;
	for(sum = 0; nword > 0; nword--)
	{
		sum += *buf;
		buf++;
	}
	sum = (sum>>16) + (sum&0xffff);
	sum += (sum>>16);
	return ~sum;
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
	//获取要发送的消息
	// 飞秋格式 固定port-2425
    // 版本:

	printf("请输入要发送的消息:");
	char data[128]="1_iptux_0#5#2:123:edu:edu:32:loveyou";
	int data_len = strlen(data);
	//如果data_len不是偶数 补0为偶数
	if(data_len%2 != 0)//奇数
		data_len++;
	
	/*目的mac地址 XPmac*/
	unsigned char dst_mac[6]={0x70,0x5A,0x0F,0x63,0xF5,0x9D};//win_mac
	unsigned char dst_ip[4]={192,168,0,110};//win_ip
	unsigned char src_mac[6]={0x00,0x0c,0x29,0x9a,0xeb,0x23};//伪装的mac!!!!
	unsigned char src_ip[4]={192,168,0,105};//伪装的IP !!!!!
	
	
	unsigned char msg[1024]="";
	//1、组mac头部
	struct ether_header *eth_addr = (struct ether_header *)msg;
	//赋值目的mac地址
	memcpy(eth_addr->ether_dhost, dst_mac, 6);
	//赋值源mac地址
	memcpy(eth_addr->ether_shost, src_mac, 6);
	//赋值帧类型 
	eth_addr->ether_type = htons(0x0800);
	
	//2、组IP报文
	struct iphdr *ip_hdr = (struct iphdr *)(msg+14);
	ip_hdr->version = 4;//IPv4版本
	ip_hdr->ihl = 5;//IP头部长度 单位4B 所以赋值5其实就是5*4=20B
	ip_hdr->tos = 0;//服务类型
	ip_hdr->tot_len = htons(20+8+data_len);//总长度=IP首部长度+IP数据长度
	ip_hdr->id = htons(0);//标识
	ip_hdr->frag_off = htons(0);//标志 + 片偏移
	ip_hdr->ttl = 128;//64或128都可以 生命周期
	ip_hdr->protocol = 17;//udp 17   tcp 6
	ip_hdr->check = htons(0);//首部校验？？？？ 后续校验
	memcpy(&ip_hdr->saddr, src_ip, 4);//源IP
	memcpy(&ip_hdr->daddr, dst_ip, 4);//目的IP
	//ip报文头部校验
	ip_hdr->check = checksum(ip_hdr, 20);
	
	//3、udp头部
	struct udphdr *udp_hdr = (struct udphdr *)(msg+14+20);
	udp_hdr->source = htons(2425);//源端口 !!!!
	udp_hdr->dest = htons(2425);//目的端口 !!!!
	udp_hdr->len = htons(8+data_len);//udp总长度=udp报文头+数据长
	udp_hdr->check = htons(0);//???? udp校验
	//将data拷贝到udp的数据部分
	memcpy(msg+14+20+8, data, data_len);
	
	//准备udp校验
	unsigned char wei_head[1024]="";
	WEIHDR *wei_hdr = (WEIHDR *)wei_head;
	memcpy(&wei_hdr->saddr, src_ip, 4);//源IP
	memcpy(&wei_hdr->daddr, dst_ip, 4);//目的IP
	wei_hdr->flag = 0;
	wei_hdr->type = 17;//协议
	wei_hdr->len = htons(8+data_len);//udp的总长度
	//将msg中的udp头部信息以及data数据 拷贝到为头部后方
	memcpy(wei_head+12, udp_hdr, 8+data_len);
	
	//校验udp： 为头部+udp头部+data部分
	udp_hdr->check = checksum(wei_head, 12+8+data_len);
	
	//发送arp请求帧数据
	my_sendto(sockfd, "eth0",msg, 14+20+8+data_len);
	
	sleep(5);
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