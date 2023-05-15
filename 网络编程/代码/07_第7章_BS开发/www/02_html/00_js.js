function getXMLHttpRequest()
{
    var xmlhttp = null;
    if (window.XMLHttpRequest)//自动检测当前浏览器的版本，如果是IE5.0以上的高版本的浏览器
    {// code for IE7+, Firefox, Chrome, Opera, Safari
        xmlhttp=new XMLHttpRequest();//创建请求对象
    }
    else////如果浏览器是底版本的
    {// code for IE6, IE5
        xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");//创建请求对象
    }
    return xmlhttp;//返回请求对象
}
function calc_fun(arg)
{
    //1、获取网页输入框的数据data1 data2
    var data1 = document.getElementById("data1").value;
    var data2 = document.getElementById("data2").value;
    //判断data1 data2是否合法
    if(isNaN(data1) || isNaN(data2) )
    {
        document.getElementById("data1").value="";
        document.getElementById("data2").value="";
        alert("请输入有效的数值");
        return;
    }

    //组包请求报文url "/cgi-bin/calc.cgi?10+20"  "/cgi-bin/calc.cgi?10-20"
    var url="/cgi-bin/calc.cgi?";
    url +=data1;
    if(arg == "1")//加
    {
        url +="+";
    }
    else if(arg == "0")//减
    {
        url +="-";
    }
    url+=data2;
    alert("url:"+url);

    //创建一个xmlHttpRequest对象
    var xmlHttp = null;
    xmlHttp =  getXMLHttpRequest();

    //open
    xmlHttp.open("GET", url, false);//false表示同步

    //send
    xmlHttp.send();//将请求url发送给服务器

    //等待服务器的应答（同步）
    if(xmlHttp.readyState == 4 && xmlHttp.status==200)
    {
        //获取服务器的结果
        var ret = xmlHttp.responseText;
        //将ret赋值给label
        document.getElementById("ret").innerHTML=ret;
    }
}