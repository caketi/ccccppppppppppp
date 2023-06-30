function object(o){
    // 创建一个临时构造函数
    function f(){
    }
    // 让这个临时构造函数的prototype指向o new出来的对象 __proto__指向了o
    f.prototype = o;
    return new f();
}

var o1 = {
    a:1,
    b:2
}

var o2 = object(o1)
console.info(o2.__proto__ === o1)
console.info(o1.a)
console.info(o2.a)
console.info(o1.prototype)
console.info(o2.prototype)


var o3 = Object.create(o1, {
    
    e: {
        value: 99
    }
})

console.info(o3.__proto__ === o1)
console.info(o3.a)
console.info(o3.b)
console.info(o3.e)


function inheritPrototype(subType, superType){
    var prototype = Object.create(superType.prototype);
    subType.prototype = prototype;
}