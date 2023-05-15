#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		printf("./a.out server_ip file_name\n");
		return 0;
	}
	
	//tftp是基于udp 所以是udp编程流程
	int sockfd = socket(AF_INET, SOCK_DGRAM ,0);
	if(sockfd <0)
	{
		perror("socket");
		return 0;
	}
	
	//给tftp服务器发送 下载文件的请求
	//组tftp 文件读取请求报文
	// unsigned char 0-255  char -127-127 可能溢出（192）
	unsigned char cmd[128]="";
	int len = sprintf(cmd,"%c%c%s%c%s%c",0x00,0x01,argv[2],0,"octet",0);
	//将请求cmd发给服务器的 69号端口
	struct sockaddr_in server;
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(69);
	inet_pton(AF_INET,argv[1], &server.sin_addr.s_addr);
	sendto(sockfd, cmd, len, 0, (struct sockaddr *)&server, sizeof(server));
	
	//打开一个本地空的文件
	int fd = open(argv[2],O_WRONLY|O_CREAT,0666);
	if(fd < 0)
	{
		perror("open");
		return 0;
	}
	
	//不同读取服务器传过来的文件数据
	unsigned short num=0;
	while(1)
	{
		unsigned char buf[1024]="";
		struct sockaddr_in from;
		socklen_t from_len = sizeof(from);
		int len = recvfrom(sockfd,buf,sizeof(buf),0, \
		(struct sockaddr *)&from, &from_len);
		
		//判断收到的数据的操作码 必须是00 03表示文件数据
		// 2byte 操作码 2byte块编号  data
		// buf[0] [1]   [2][3]       [4]
		if(buf[1]==0x03)//文件数据
		{
			//将文件数据 写入 本地址文件中
			//防止写入重复数据
			if((num+1) == ntohs(*(unsigned short *)(buf+2)) )
			{
				write(fd, buf+4 , len-4);
				num = ntohs(*(unsigned short *)(buf+2));
				printf("recv:%d\n",num);
			}
			
			//给服务器发送ACK回应
			// 2byte 操作码 2byte块编号
			buf[1]=4;
			sendto(sockfd, buf , 4 ,0,(struct sockaddr *)&from,sizeof(from));
			
			if(len < 516)//这是最后一个文件数据
				break;
		}
	}
	//关闭套接字
	close(sockfd);
	//关闭文件
	close(fd);
	return 0;
}