function my_string()
{
    var text="2020:nz2001:good";
    //write讲字符串写入到浏览器上
    document.write("字符串的长度:"+text.length+"<br>");
    document.write("第0个字符为:"+text.charAt(0)+"<br>");

    var start = 0;
    var stop = 0;

    while(1)
    {
        //寻找:的位置
        stop = text.indexOf(":", start);
        if(stop == -1)
        {
            //提取最后一个字符串
            var tmp = text.substring(start);
            document.write("提取的内容为:"+tmp+"<br>");
            break;
        }

        var tmp = text.substring(start,stop);
        document.write("提取的内容为:"+tmp+"<br>");

        //步进条件
        start = stop +1;
    }

}