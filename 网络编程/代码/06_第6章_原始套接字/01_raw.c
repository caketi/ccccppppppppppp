#include<stdio.h>
#include<sys/socket.h>
#include<netinet/ether.h>

int main()
{
	//1、 创建一个原始套接字 ETH_P_ALL收发任何数据类型
	int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(sockfd < 0)
	{
		perror("socket");
		return 0;
	}
	printf("sockfd = %d\n", sockfd);

	//2、使用recvfrom接受网络数据 数据很多
	while(1)
	{
		//定义buf存放帧数据 大小1500 unsigned char
		unsigned char buf[1500]="";
		int len = recvfrom(sockfd, buf, sizeof(buf),0,NULL,NULL);
		printf("len = %d\n", len);
		//buf不要用%s遍历 帧数大多都是不识别的ASCII值  有太多的0x00
		//printf("buf=%s\n",buf);
		//sleep(1);//别sleep会丢失数据
		
		//解析buf-->mac头信息-->必须明白mac头的结构
		//1、mac头部：目的mac(6B) 源mac(6B) 类型（2B）
		//[mac][ip][tcp/udp][data] ff:ff:ff:ff:ff:ff
		char src_mac[18]="";
		char dst_mac[18]="";
		sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
		buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
		sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x",\
		buf[0+6],buf[1+6],buf[2+6],buf[3+6],buf[4+6],buf[5+6]);
		printf("%s--->%s\n", src_mac, dst_mac);
		
		//判断mac头部中协议类型 0x0800 IP  0x0806 ARP 0x8035 RARP
		unsigned short mac_type = ntohs(*(unsigned short *)(buf+12));
		if( mac_type == 0x0800 )
		{
			printf("mac_type = %#x IP报文\n",mac_type);
			//2、分析IP头部
			unsigned char *ip_addr = buf+14;//+14跳过mac头
			//ip_addr跳到源IP的起始位置
			ip_addr += 12;
			char src_ip[16]="";
			char dst_ip[16]="";
			sprintf(src_ip,"%d.%d.%d.%d", \
			ip_addr[0],ip_addr[1],ip_addr[2],ip_addr[3]);
			
			ip_addr += 4;
			sprintf(dst_ip,"%d.%d.%d.%d", \
			ip_addr[0],ip_addr[1],ip_addr[2],ip_addr[3]);
			printf("%s--->%s\n",src_ip,dst_ip);
			
			//判断完成网路层的上一层协议类型
			ip_addr = buf+14;
			unsigned char *ip_type = ip_addr +9;
			if(*ip_type == 1)
			{
				printf("ICMP报文\n");
			}	
			else if(*ip_type == 2)
			{
				printf("IGMP报文\n");
			}
			else if(*ip_type == 6)
			{
				printf("TCP报文\n");
				ip_addr = buf+14;//ip报文起始位置
				int ip_head_len = (*ip_addr&0x0f)*4;//提取ip报文的头部长度
				unsigned char *tcp_addr = buf+14+ip_head_len;
				unsigned short src_port = ntohs(*(unsigned short *)tcp_addr);
				unsigned short dst_port = ntohs(*(unsigned short *)(tcp_addr+2));
				printf("%hu--->%hu\n", src_port, dst_port);
				
				//调到tcp首部长度的位置
				unsigned char *tcp_headLen_addr = tcp_addr+12;
				int tcp_head_len = ((*tcp_headLen_addr>>4)&0x0f)*4; 
				printf("TCP:%s\n", tcp_addr+tcp_head_len);
			}
			else if(*ip_type == 17)
			{
				printf("UDP报文\n");
				ip_addr = buf+14;//ip报文起始位置
				int ip_head_len = (*ip_addr&0x0f)*4;//提取ip报文的头部长度
				unsigned char *udp_addr = buf+14+ip_head_len;
				unsigned src_port = ntohs(*(unsigned short *)udp_addr);
				unsigned dst_port = ntohs(*(unsigned short *)(udp_addr+2));
				printf("%hu--->%hu\n", src_port, dst_port);
				printf("%s\n", udp_addr+8);//应用层数据
			}
			
		}
		else if(mac_type == 0x0806)
		{
			printf("mac_type = %#x ARP报文\n",mac_type);
		}
		else if(mac_type == 0x8035)
		{
			printf("mac_type = %#x RARP报文\n",mac_type);
		}
		
	}
	 
	//关闭套接字
	close(sockfd);
	return 0;
}