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
function deal_led(arg)//arg就是img的id led1  led2 led3
{  
    var url="/cgi-bin/led.cgi?";
    url+=arg;

    var path = document.getElementById(arg).src;
    if(path.indexOf("led_off",0) != -1)
    {
        document.getElementById(arg).src = "./image/led_on.png";
        url+=":1";
    }
    else if(path.indexOf("led_on",0) != -1)
    {
        document.getElementById(arg).src = "./image/led_off.png";
        url+=":0";
    }

    //创建xmlhttp对象
    var xmlhttp = getXMLHttpRequest();
    //设置回调函数
    xmlhttp.onreadystatechange=function(){
        //alert("xmlHttp.readyState="+xmlHttp.readyState,+",xmlHttp.status="+xmlHttp.status);
        if(xmlhttp.readyState == 4 && xmlhttp.status==200)
        {
            //获取服务器的结果
            var ret = xmlhttp.responseText;
            alert("ret="+ret);
        }
    }

    //open
    xmlhttp.open("GET",url, true);//url="/cgi-bin/led.cgi?led2:1"

    //send
    xmlhttp.send();
}