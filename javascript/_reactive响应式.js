// 正确的收集依赖
// Proxy的set方法中收集对应的函数
// 全局activeReactiveFn变量
// 在get中找到depend对象，addDepend(全局activeReactiveFn变量)

// 对depend进行优化
// addDepend函数->addDepend函数
// 直接获取到自由变量
// 将之前保存的数组[]-> Set
// 对对象的响应式操作
// 封装reactive函数
// new Proxy(): vue3
// Object.defineProperty(): vue2
class Depend{
    constructor(){
        this.reactiveFns = new Set()
    }

    depend(){
        if(activeReactiveFn){
            this.reactiveFns.add(activeReactiveFn)
        }
    }
    notify(){
        this.reactiveFns.forEach(fn => {
            fn()
        })
    }
}

const targetMap = new WeakMap()
function getDepend(target, key){
    // 根据target对象获取map的过程
    let map = targetMap.get(target)
    if(!map){
        map = new Map()
        targetMap.set(target, map)
    }

    let depend = map.get(key)
    if(!depend){
        depend = new Depend()
        map.set(key, depend)
    }
    return depend
}

function reactive_before_es6(obj){
    Object.keys(obj).forEach(key => {
        let value = obj[key]
        Object.defineProperty(obj, key, {
            get: function(){
                const depend = getDepend(obj, key)
                depend.depend()
                return value
            },
            set: function(newValue){
                value = newValue
                const depend = getDepend(obj, key)
                depend.notify()
            }
        })
    })
    return obj
}

function reactive(obj){
    return new Proxy(obj, {
        get: function(target, key, receiver){
            // 根据target， key获取对应的depend
            const depend = getDepend(target, key)
            // 给depend对象中添加响应函数
            // depend.addDepend(activeReactiveFn)
            depend.depend()

            return Reflect.get(target, key, receiver)
        },
        set: function(target, key, newValue, receiver){
            Reflect.set(target, key, newValue, receiver)
            const depend = getDepend(target, key)
            depend.notify()
        }
    })
}