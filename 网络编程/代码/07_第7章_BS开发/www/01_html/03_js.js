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
function get_file_fun()
{
    //1、创建xmlHttpRequest对象
    var xmlhttp = null; 
    xmlhttp = getXMLHttpRequest();

    //2、设置服务器响应的回调函数
    xmlhttp.onreadystatechange = function(){
        //xmlhttp.readyState==4 && xmlhttp.status==200 标识服务器处理完成
        if(xmlhttp.readyState==4 && xmlhttp.status==200)
        {
            //获取服务器的结果 xmlhttp.responseXML才是服务器的应答
            //获取服务器的结果 xmlhttp.responseText才是服务器的应答
            var ret = xmlhttp.responseText;
            //局部更新网页上的label
            document.getElementById("label").innerHTML = ret;
        }
    }

    //3、open
    var url="./file/a.txt";
    xmlhttp.open("GET", url, true);//异步方式
    
    //4、send
    xmlhttp.send();
}

