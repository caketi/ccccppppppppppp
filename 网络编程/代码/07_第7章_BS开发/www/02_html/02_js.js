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

    //POST数据是密文传输 不能将数据放入？后面
    var url="/cgi-bin/calc.cgi";

    //将发送给服务器的数据data
    var data="";
    data +=data1;
    if(arg == "1")//加
    {
        data +="+";
    }
    else if(arg == "0")//减
    {
        data +="-";
    }
    data+=data2;
    alert("data:"+data);

    //创建一个xmlHttpRequest对象
    var xmlHttp = null;
    xmlHttp =  getXMLHttpRequest();

    //open POST
    xmlHttp.open("POST", url, false);//false 同步

    //POST send 由于url没有数据 所以只能用send将data发送出去
    xmlHttp.send(data);//将data发送给服务器

    if(xmlHttp.readyState == 4 && xmlHttp.status==200)
    {
        //获取服务器的结果
        var ret = xmlHttp.responseText;
        //将ret赋值给label
        document.getElementById("ret").innerHTML=ret;
    }
}