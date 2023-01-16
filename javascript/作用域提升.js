

console.info(globalThis)


// for( var i = 0; i < 2; i++){
//         console.log(i)
// }
for( var i = 0; i < 2; i++){
    (function(n){
        console.log(i)
    })(i)
}

for(let a = 0; a < 1; a++){
    console.info(a)
}

// function foo(){
//     var a = b = 100
//     var a = 100
//     b  = 100
// }
// foo()
// // console.info(a) // undefined
// console.info(b) //100 


// -============
// var a = 100
// function foo(){
//     console.info(a)
//     return 
//     var a = 100
// }
// foo() // undefined



// ------------------
// function foo(){
//     console.info(n)
//     var n = 200
//     console.info(n)
// }
// var n = 100
// foo() // undefined 200 
// console.info(n) // 100

// --------------------
// var n = 100
// function foo(){
//     n = 200
// }
// foo()
// console.info(n) // 200

// --------------------
// var n = 100

// function foo1(){
//     console.info(n)
// }

// function foo2(){
//     var n = 200
//     console.info(n)
//     foo1()
// }

// foo2() // 200 100
// console.info(n) // 100