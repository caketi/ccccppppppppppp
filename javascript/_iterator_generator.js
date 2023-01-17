function requestData(url){
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve(url)
        }, 2000);
    })
}
// 异步函数返回值是一个promise
async function getData(){
    const res1 = await requestData("wh")
    const res2 = await requestData(res1+"a")
    const res3 = await requestData(res2+"b")
    const res4 = await requestData(res3+"c")
    console.info(res4)

}
getData()
// function* getData(){
//     const res1 = yield requestData("wh")
//     const res2 = yield requestData(res1+"a")
//     const res3 = yield requestData(res2+"b")
//     const res4 = yield requestData(res3+"c")
//     console.info(res4)

// }
// // npm install co  第三方包自动执行 TJ
// // const co = require('co')
// // co(getData)
// function execGenerator(genFn){
//     const generator = genFn()
//     function exec(res){
//         const result = generator.next(res)
//         if(result.done){
//             return result.value
//         }
//         result.value.then(res => {
//             exec(res)
//         })
//     }
//     exec()
// }

// execGenerator(getData)



// const iterator = { 
//     next: function(){
//         return {done: true, value: 22}
//     }
// }
// // yield -- 暂停执行 return -- 终止执行
// function* foo(){
//     console.log("start)))")
    
//     const v = 1
//     console.log(v)
//     yield v

//     const v1 = 122
//     console.log(v1)
//     yield v1

//     console.info("end-0-0")
// }

// const generator = foo()
// console.info(generator.next())
// console.info(generator.next())
// console.info(generator.next())
// generator.next()