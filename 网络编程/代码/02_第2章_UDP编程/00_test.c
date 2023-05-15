#include<stdio.h>
#include<arpa/inet.h>
int main()
{
	unsigned short num = 0x0102;
	
	//将num转换成网络字节序
	printf("num = %#x\n",num);//主机是小端
	printf("htons(num) = %#x\n",htons(num));//网络是大端
	
	return 0;
}