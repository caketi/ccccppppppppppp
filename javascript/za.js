// 1.javascript 对象中不能用对象做key Map可以
const obj1 = {name: "w"}
const obj2 = {name: "z"}
const info = { 
    [obj1]: 'aa',
    [obj2]: 'aaaa'
}
console.log(info)
const map = new Map()
map.set(obj1, "aaaaa")
map.set(obj2, "dfa")
console.log(map)