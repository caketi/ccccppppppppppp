function sum(b1, b2) {
    console.info(this.c + this.m + b1 + b2)
}

x = {
    c: 3,
    m: 3,
}

sum.call(x, 2, 2)
sum.apply(x, [2, 2]) 
// apply -- 数组可变零散值


function outer(){
    var a = 1;
    var b = 2;
    return {
        a: 3,
        b: 4,
        fn: function(){
            console.info(this.a + this.b);
        }
    }
}

outer()
outer().fn() //7

// 上下文如何被调用 调用函数时的前言后语 函数被调用 确定this
var obj1 = {
    a: 1,
    b: 2,
    fn: function(){
        console.info(this.a + this.b);
    }
}

var obj2 = {
    a: 3,
    b: 4,
    fn: obj1.fn
};

obj2.fn(); // 7

var arr = ['a', 'b', 'c', function () {
    console.info(this[0]);
}];

arr[3](); //a

function fun() {
    arguments[3]();//b
}
fun('a', 'b', 'c', function () {
    console.info(this[1]);
})

function fun() {
    return this.a + this.b;
}
var a = 1;
var b = 2;
var obj = {
    a: 3,
    b: fun(), //3
    fun: fun
}
var result = obj.fun() // 6
console.info(result) //

// var a = 1;
// var obj = {
//     a: 2,
//     fun: (function(){
//         var a = this.a; // IIFE的this是window 1
//         return function(){
//             console.info(a + this.a); //2+1
//         }
//     })()
// }
// obj.fun(); //3



// var obj = {
//     a: 1,
//     b: 2,
//     fun: function(){
//         console.info(this.a + this.b);
//     }
// }
// var a = 3;
// var b = 4;
// setTimeout(() => {
//     obj.fun()
// }, 2000); //3

// setTimeout(
//     obj.fun
// , 2000); //7