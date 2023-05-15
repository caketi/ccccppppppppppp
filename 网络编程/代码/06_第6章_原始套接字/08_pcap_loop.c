#include<stdio.h>
#include <pcap.h>
//pcap_loop每收到一个报文 就会调用一次回调函数
void callback(u_char *arg, const struct pcap_pkthdr *packet_header, \
const u_char *packet_content)
{
	unsigned char *msg = packet_content;
	printf("报文长度:%u\n", packet_header->caplen);
	//解析msg的mac地址
	char src_mac[18]="";
	char dst_mac[18]="";
	sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", \
	msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", \
	msg[0+6],msg[1+6],msg[2+6],msg[3+6],msg[4+6],msg[5+6]);
	printf("%s--->%s\n", src_mac, dst_mac);
}
int main()
{
	//1、创建一个pcap句柄
	pcap_t *pcap_handle = NULL;
	pcap_handle = pcap_open_live("eth0",1500,0,0,NULL);
	
	//设置过滤规则
	struct bpf_program program;
	pcap_compile(pcap_handle,&program, "src port 9000", 0, 0xffffff00);
	pcap_setfilter(pcap_handle, &program);
	
	//2、接受数据 带阻塞
	pcap_loop(pcap_handle, 5, callback, NULL);
	
	//关闭句柄
	pcap_close(pcap_handle);
	return 0;
}