let timer = null;
if (timer) {
    clearTimeout(timer);
}
setTimeout(() => {
    console.log(1)
}, 300);

// 1.javascript 对象中不能用对象做key 但是Map可以
const obj1 = { name: "w" }
const obj2 = { name: "z" }
const info = {
    [obj1]: 'aa',
    [obj2]: 'aaaa'
}
console.log(info) // { '[object Object]': 'aaaa' }
// --------------------------------------------------------
const map = new Map()
map.set(obj1, "aaaaa")
map.set(obj2, "dfa")
console.log(map) // Map(2) { { name: 'w' } => 'aaaaa', { name: 'z' } => 'dfa' }