function proto_test(){
    console.info("prototype constructor")
}

console.info(proto_test.prototype)
console.info(typeof proto_test.prototype)
console.info(proto_test.prototype.constructor === proto_test)
console.info(proto_test.prototype.constructor == proto_test)