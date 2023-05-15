function get_time()
{
    setInterval("get_time_fun()", 1000);
}
function get_time_fun()
{
    var d = new Date();
    //在js中 去写网页 
    var text= "<table border='1'>";
    //首行
    text += "<tr> <td>时</td><td>分</td><td>秒</td></tr>"
    //第一行
    text += "<tr><td>";
    text += d.getHours();
    text += "</td><td>";
    text += d.getMinutes();
    text += "</td><td>";
    text += d.getSeconds();
    text += "</td></tr>";
    text += "</table>";

    document.getElementById("div").innerHTML= text;
}