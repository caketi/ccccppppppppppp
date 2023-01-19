class CTEventBus {
  constructor() {
    this.eventBus = {};
  }
  on(eventName, eventCallback, thisArg){
    let handlers = this.eventBus[eventName]
    if(!handlers){
        handlers = []
        this.eventBus[eventName] = handlers
    }
    handlers.push({
        eventCallback,
        thisArg
    })
  }
  emit(eventName, ...payload) {
    const handlers = this.eventBus[eventName];
    if (!handlers) return;
    handlers.forEach((handler) => {
      handler.eventCallback.apply(handler.thisArg, payload);
    });
  }
  off(eventName, eventCallback) {
    const handlers = this.eventBus[eventName];
    if (!handlers) return;
    const newHandlers = [...handlers];
    for (let i = 0; i < newHandlers.length; i++) {
      const handler = newHandlers[i];
      if (handler.eventCallback === eventCallback) {
        const index = handlers.indexOf(handler);
        handlers.splice(index, 1);
      }
    }
  }
}

const eventBus = new CTEventBus()

eventBus.on("abc", function(){
    console.info("ff", this)
}, {name: "dcfasf"})

const handleCallback = function(){
    console.info("af", this)
}
eventBus.on("fassf", handleCallback, {name: "faf"})
eventBus.emit("fassf", 111)
eventBus.emit("abc", 11111)
eventBus.off("fassf", handleCallback)