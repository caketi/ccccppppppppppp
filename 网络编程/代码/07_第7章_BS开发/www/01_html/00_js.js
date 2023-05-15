var my_timer;
function timer_fun(arg)
{
    if(arg == "1")//开启定时器
    {
        //每1秒 就调用一次 my_fun()函数
       my_timer =  setInterval( "my_fun()" ,1000 );//定时单位毫秒
    }
    else if(arg == "0")//关闭定时器
    {
        //清除定时器
        clearInterval(my_timer);
    }
}
function my_fun()
{
    //Math.random产生一个0~1的随机数浮点数
    //Math.round 四舍五入 取整
    var num =Math.round( Math.random()*100 );
    document.getElementById("wendu").innerHTML = num;
}