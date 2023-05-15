#include<stdio.h>
#include<arpa/inet.h>
int main()
{
	//点分十进制数串
	char *str_ip="192.168.0.111";
	//32位无符号整形数据
	unsigned int num_ip=0;
	//AF_INETIPv4  AF_INET6 IPv6
	inet_pton(AF_INET,str_ip, &num_ip);
	
	printf("str_ip=%s\n", str_ip);
	printf("num_ip=%u\n", num_ip);//1862314176 
	
	//细致分析 num_ip的4字节分布
	unsigned char *p = (unsigned char *)&num_ip;
	printf("%u %u %u %u\n", *p, *(p+1),*(p+2), *(p+3));//192 168 0 111
	return 0;
}