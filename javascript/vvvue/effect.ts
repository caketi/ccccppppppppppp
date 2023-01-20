export function effect<T = any>(fn: () => T) {
  const _effect = new ReactiveEffect(fn);

  _effect.run();
}
export let activeEffect: ReactiveEffect | undefined;

export class ReactiveEffect<T = any> {
  constructor(public fn: () => T) {}
  run() {
    activeEffect = this;
    return this.fn();
  }
}

export function track(target: object, key: unknown) {
    if (!activeEffect) return
    let depsMap = targetMap.get(target)
    if(!depsMap){
        targetMap.set(target, (depsMap = new Map()))
    }
    depsMap.set(key, activeEffect)
    console.info("track收集依赖");
}

export function trigger(target: object, key: unknown, newValue: unknown) {
   const depsMap = targetMap.get(target)
   if(!depsMap){
    return 
   }
   const effect = depsMap.get(key) as ReactiveEffect
   if(!effect){
    return
   }
   effect.fn()
    console.info("trigger触发依赖");
}
