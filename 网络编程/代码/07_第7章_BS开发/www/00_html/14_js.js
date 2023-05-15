function my_button(arg)
{
    if(arg == 1)//登录 admin 123456
    {
        //获取网页上输入框的用户名密码
        var usr = document.getElementById("usr").value;//重点
        var pwd = document.getElementById("pwd").value;
        if(usr=="admin" && pwd=="123456")
        {
            window.location.href="http://www.baidu.com";
        }
        else
        {
            alert("用户名或密码错误请重新输入");
            //清空用户名密码的输入框
            document.getElementById("usr").value="";
            document.getElementById("pwd").value="";
        }
    }
    else if(arg == 0)//取消
    {
        //清空用户名密码的输入框
        document.getElementById("usr").value="";
        document.getElementById("pwd").value="";
    }
}