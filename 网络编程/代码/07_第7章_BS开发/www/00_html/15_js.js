function change_fun()
{
    //获取label的内容 对于label 而是innerHTML
    var text = document.getElementById("addr").innerHTML;
    alert("获得的内容为:"+text);

    //更改label的内容
    document.getElementById("addr").innerHTML="SZ";

}