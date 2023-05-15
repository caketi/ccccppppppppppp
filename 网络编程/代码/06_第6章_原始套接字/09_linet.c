#include<stdio.h>
#include <libnet.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{	
	//1、初始化内存
	libnet_t *lib_handle = libnet_init(LIBNET_LINK_ADV,"eth0",NULL);
	
	char data[128]="";
	printf("请输入要发送的udp数据:");
	fgets(data,sizeof(data),stdin);
	data[strlen(data)-1]=0;
	int data_len = strlen(data)+strlen(data)%2;//长度为偶数
	
	//构建数据包：从应用层--->链路层
	//1、构建udp数据
	libnet_ptag_t ptag_udp = libnet_build_udp(8000,9000,8+data_len,\
	0,data,data_len, lib_handle, 0);
	
	//2、构建IP报文
	libnet_ptag_t ptag_ip = libnet_build_ipv4(20+8+data_len,0,0,0,128,\
	17,0,inet_addr("192.168.0.111"),inet_addr("192.168.0.110"),\
	NULL,0, lib_handle, 0);
	
	//3、构建mac数据报文
	unsigned char src_mac[6]={0x00,0x0c,0x29,0x79,0xf9,0x7f};
	unsigned char dst_mac[6]={0x70,0x5A,0x0F,0x63,0xF5,0x9D};
	libnet_ptag_t ptag_mac = libnet_build_ethernet(dst_mac, src_mac, 0x0800,\
	NULL,0, lib_handle, 0);
	
	//4、发送帧数据
	libnet_write(lib_handle);
	
	//循环的发送5次
	int i=0;
	for(i=0;i<5;i++)
	{
		printf("请输入要发送的udp数据:");
		fgets(data,sizeof(data),stdin);
		data[strlen(data)-1]=0;
		data_len = strlen(data)+strlen(data)%2;//长度为偶数
		
		//重新构建udp报文
		ptag_udp = libnet_build_udp(8000,9000,8+data_len,\
	0,data,data_len, lib_handle, ptag_udp);
		
		//重新构建IP报文
		ptag_ip = libnet_build_ipv4(20+8+data_len,0,0,0,128,\
	17,0,inet_addr("192.168.0.111"),inet_addr("192.168.0.110"),\
	NULL,0, lib_handle, ptag_ip);
		//发送帧数据
		libnet_write(lib_handle);
		
	}
	
	//释放资源
	libnet_destroy(lib_handle);
	return 0;
}