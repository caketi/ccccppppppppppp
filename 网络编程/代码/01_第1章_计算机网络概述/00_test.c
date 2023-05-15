/* ************************************************************************
 *       Filename:  00_test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  12/05/20 16:48:16
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
typedef union
{
	//共用体 成员公用一个空间
	unsigned short data;
	unsigned char buf[2];
}DATA;
int main(int argc, char *argv[])
{
	printf("%d\n",sizeof(DATA));
	DATA ob;
	ob.data = 0x0102;
	//如果buf[0]=0x01大  buf[0]=0x02 
	if(ob.buf[0]==0x01 && ob.buf[1]==0x02)
	{
		printf("大端格式\n");
	}
	else if(ob.buf[0]==0x02 && ob.buf[1]== 0x01)
	{
		printf("小端格式\n");
	}

	return 0;
}


