#include<stdio.h>
#include<arpa/inet.h>
int main()
{
	//模拟一个32位网路字节序IP地址
	unsigned char p[]={192,168,0,111};
	
	char ip_str[16]="";
	inet_ntop(AF_INET,p, ip_str, 16 );
	printf("ip_str=%s\n", ip_str);
	return 0;
}