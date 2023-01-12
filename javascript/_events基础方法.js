const Eventemitter = require("events");
const { emit, env } = require("process");

const emitter = new Eventemitter();

emitter.on("click", (args) => {
  console.info("监听1到click事件", args);
});
const listener2 = (args) => {
  console.info("监听1到tes事件", args);
};
emitter.on('test', listener2)

setTimeout(()=>{
    emitter.emit("click", "code", "tes");
    emitter.off("click", listener2);
    emitter.emit("click", "tes");
}, 2000);

console.info(emitter.eventNames())