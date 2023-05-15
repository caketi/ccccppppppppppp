#include<stdio.h>
#include<stdlib.h>
int main()
{
    //传输HTML 文本第一行输出的内容必须是"content-type:text/html\n\n"
    printf("content-type:text/html\n\n");

    //获取服务器的数据 GET方式 QUERY_STRING
    char *data = getenv("QUERY_STRING");//data-->"10+20"
    
    //解析data
    int data1=0,data2=0;
    char ch = 0;
    sscanf(data,"%d%c%d", &data1, &ch, &data2);
    if(ch == '+')//加法运算
    {
        //将处理的结果 发送给服务器
        printf("%d\n", data1+data2);
    }
    else if(ch == '-')//减法运算
    {
        //将处理的结果 发送给服务器
        printf("%d\n", data1-data2);
    }

    return 0;
}