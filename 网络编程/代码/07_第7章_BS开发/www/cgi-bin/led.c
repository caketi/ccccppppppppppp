#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void led_init()
{
    //判断GPIO是否在系统中打开
    if(access("/sys/class/gpio/gpio71/value", F_OK))//不存在
    {
        system("echo 71 > /sys/class/gpio/export");//到处IO口
    }
    if(access("/sys/class/gpio/gpio75/value", F_OK))//不存在
    {
        system("echo 75 > /sys/class/gpio/export");//到处IO口
    }
    if(access("/sys/class/gpio/gpio76/value", F_OK))//不存在
    {
        system("echo 76 > /sys/class/gpio/export");//到处IO口
    }

    //设置IO的方向（输出 输入）
    system("echo out > /sys/class/gpio/gpio71/direction");
    system("echo out > /sys/class/gpio/gpio75/direction");
    system("echo out > /sys/class/gpio/gpio76/direction");

    //将所有的灯灭掉
    system("echo 1 > /sys/class/gpio/gpio71/value");
    system("echo 1 > /sys/class/gpio/gpio75/value");
    system("echo 1 > /sys/class/gpio/gpio76/value");
}
void set_led(int led, int on_off)
{
    //判断哪一个灯
    if(led == 1)
    {
        //判断开关状态
        if(on_off == 1)//亮
        {
            //io口 输出低电平
            system("echo 0 > /sys/class/gpio/gpio71/value");
        }
        else if(on_off == 0)//灭
        {
            system("echo 1 > /sys/class/gpio/gpio71/value");
        }
    }
    else if(led == 2)
    {
        //判断开关状态
        if(on_off == 1)//亮
        {
            //io口 输出低电平
            system("echo 0 > /sys/class/gpio/gpio75/value");
        }
        else if(on_off == 0)//灭
        {
            system("echo 1 > /sys/class/gpio/gpio75/value");
        }
    }
    else if(led == 3)
    {
        //判断开关状态
        if(on_off == 1)//亮
        {
            //io口 输出低电平
            system("echo 0 > /sys/class/gpio/gpio76/value");
        }
        else if(on_off == 0)//灭
        {
            system("echo 1 > /sys/class/gpio/gpio76/value");
        }
    }
}
int main()
{
    //传输HTML 文本第一行输出的内容必须是"content-type:text/html\n\n"
    printf("content-type:text/html\n\n");

    //获取服务器的数据 GET方式 QUERY_STRING
    char *data = getenv("QUERY_STRING");//data-->"10+20"
    
    //解析data="led2:1"
    int led =0, on_off = 0;
    sscanf(data,"led%d:%d", &led, &on_off);

    //初始化设备
    led_init();

    //设置灯的状态
    set_led(led, on_off);
    
    return 0;
}