function isOjbect(value) {
    const valueType = typeof value
    return (value !== null) && (valueType === "object" || valueType === "function")
}

function deepClone(originValue, map = new WeakMap()) {
    // 判断是否是一个Set类型
    if (originValue instanceof Set) {
        return new Set([...originValue])
    }
    if (originValue instanceof Map) {
        return new Map([...originValue])
    }
    // 如果是一个Symbol的value， 那么创建一个新的Symbol
    if (typeof originValue === "symbol") {
        return Symbol(originValue.description)
    }
    // 如果是一个function 直接使用同一个函数
    if (typeof originValue === "function") {
        return originValue
    }
    if (!isOjbect(originValue)) {
        return originValue
    }
    if (map.has(originValue)) {
        return map.get(originValue)
    }
    const newObject = Array.isArray(originValue) ? [] : {}
    map.set(originValue, newObject)
    for (const key in originValue) {
        newObject[key] = deepClone(originValue[key], map)
    }
    // 对Symbol的key进行特殊的处理
    const symbolKeys = Object.getOwnPropertySymbols(originValue)
    for (const skey of symbolKeys) {
        newObject[skey] = deepClone(originValue[skey], map)
    }

    return newObject
}

console.log(deepClone({ k: "aa", kk: { kkkk: "1" } }))


// js对象名称不符合规范可使用"" 且必须用方括号访问 --- 变量名也
var test2 = { k: "aa", aaaaa: { kkkk: "1" } }
console.info(test2)
var result2 = deepClone2(test2)
delete test2.k
console.info(test2)
console.info(result2)
function deepClone2(object) {
    if (Array.isArray(object)) {
        // 数组
        var result = [];
        for (var i = 0; i < object.length; i++) {
            result.push(deepClone2(object[i]));
        }
    } else if (typeof object == 'object') {
        // 对象
        var result = {};
        for (var k in object) {
            result[k] = deepClone2(object[k]);
        }
    } else {
        // 基本类型
        var result = object;
    }
    return result;
}

