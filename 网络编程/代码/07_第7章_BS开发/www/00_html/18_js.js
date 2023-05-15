function hero_fun()
{
    //获取下拉列表框被选中的索引号
    var index = document.getElementById("hero").selectedIndex;

    //根据索引号 从选项数据中options[]中得到选中的内容
    var hero_name = document.getElementById("hero").options[index].value;
    alert("你选择的英雄为:"+hero_name);
}