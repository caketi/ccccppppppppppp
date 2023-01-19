function isOjbect(value){
    const valueType = typeof value 
    return (value !== null) && (valueType === "object" || valueType === "function")
}

function deepClone(originValue, map = new WeakMap()){
    // 判断是否是一个Set类型
    if(originValue instanceof Set){
        return new Set([...originValue])
    }
    if(originValue instanceof Map){
        return new Map([...originValue])
    }
    // 如果是一个Symbol的value， 那么创建一个新的Symbol
    if(typeof originValue === "symbol"){
        return Symbol(originValue.description)
    }
    // 如果是一个function 直接使用同一个函数
    if(typeof originValue === "function"){
        return originValue
    }
    if(!isOjbect(originValue)){
        return originValue
    }
    if(map.has(originValue)){
        return map.get(originValue)
    }
    const newObject = Array.isArray(originValue) ? [] : {}
    map.set(originValue, newObject)
    for(const key in originValue){
        newObject[key] = deepClone(originValue[key], map)
    }
// 对Symbol的key进行特殊的处理
    const symbolKeys = Object.getOwnPropertySymbols(originValue)
    for(const skey of symbolKeys){
        newObject[skey] = deepClone(originValue[skey], map)
    }

    return newObject
}

console.log(deepClone({k:"aa", kk: { kkkk: "1"}}))