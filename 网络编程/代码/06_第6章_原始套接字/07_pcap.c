#include<stdio.h>
#include <pcap.h>
int main()
{
	//1、创建一个pcap句柄
	pcap_t *pcap_handle = NULL;
	pcap_handle = pcap_open_live("eth0",1500,0,0,NULL);
	
	//2、接受数据
	struct pcap_pkthdr pck_hdr;//记录收到数据的时间和报文长度
	unsigned char *msg = NULL;//存放接受到的帧数据
	msg = pcap_next(pcap_handle, &pck_hdr);
	printf("报文长度:%u\n", pck_hdr.caplen);
	//msg:mac ip  udp/tcp  data
	//msg的mac地址解析 和 原始套接字一样
	//解析msg的mac地址
	char src_mac[18]="";
	char dst_mac[18]="";
	sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", \
	msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", \
	msg[0+6],msg[1+6],msg[2+6],msg[3+6],msg[4+6],msg[5+6]);
	printf("%s--->%s\n", src_mac, dst_mac);
	
	//关闭句柄
	pcap_close(pcap_handle);
	return 0;
}