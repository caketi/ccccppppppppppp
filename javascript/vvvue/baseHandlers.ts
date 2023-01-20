import { triggerRef } from "vue"

const get = createGetter()
function createGetter(){
    return function get(target: object, key: string | symbol, receiver: object){
        const res = Reflect.get(target, key, receiver)
        track(traget, key)
        return res
    }
}

const set = createSetter()
function createSetter(){
    return function get(target: object, key: string | symbol, value: unknown, receiver: object){
        const res = Reflect.set(target, key, value, receiver)
        triggerRef(target, key, value)
        return res
    }
}

export const mutableHandlers: ProxyHandler<object> = {
    get, 
    set
}