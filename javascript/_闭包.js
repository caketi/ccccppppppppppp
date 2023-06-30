// 闭包所处的环境会被保存
function outer(){
    var name = 'test';
    function inner(){
        console.info(name);
    }
    return inner;
}

var inner = outer();
inner()