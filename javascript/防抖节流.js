const { reactive } = require("vue");

function debounce(fn, delay, resultCallback, immediate = false) {
  // 定时器保存上一次的
  let timer = null;
  let isInvoke = false;
  const _debounce = function (...args) {
    return new Promise((resolve, reject) => {
      // 取消上一次的timer
      if (timer) clearTimeout(timer);
      if (immediate && !isInvoke) {
        const result = fn.apply(this, args);
        if (resultCallback) resultCallback(result);
        resolve(result);
        isInvoke = true;
      } else {
        // 延迟执行
        let timer = setTimeout(() => {
          const result = fn.apply(this, args);
          if (resultCallback) resultCallback(result);
          resolve(result);
          isInvoke = false;
          timer = null;
        }, delay);
      }
    });
  };
  _debounce.cnacel = function () {
    if (timer) clearTimeout(timer);
    timer = null;
    isInvoke = false;
  };
  return _debounce;
}

// 需要限流的函数 限流间隔？
function throttle(fn, interval) {
  let lastTime = 0;

  const _throttle = function () {
    const nowTime = new Date().getTime();

    const remainTime = interval - (nowTime - lastTime);
    if (remainTime <= 0) {
      fn();
      lastTime = nowTime;
    }
  };

  return _throttle;
}

function throttle2(fn, interval, options = { leading: true, trailing: false }) {
  //记录上一次的开始时间
  const { leading, trailing } = options;
  let lastTime = 0;
  let timer = null;

  const _throttle = function () {
    const nowTime = new Date().getTime();
    if (!lastTime && !leading) lastTime = nowTime;

    const remainTime = interval - (nowTime - lastTime);
    if (remainTime <= 0) {
      if (timer) {
        clearTimeout(timer);
        timer = null;
      }

      fn();
      // 保留上次触发时间
      lastTime = nowTime;
      return;
    }
    if (trailing && !timer) {
      timer = setTimeout(() => {
        timer = null;
        lastTime = !leading ? 0 : new Date().getTime();
        fn();
      }, remainTime);
    }
  };
  return _throttle;
}

function throttle3(
  fn,
  interval,
  resultCallback,
  options = { leading: true, trailing: false }
) {
  //记录上一次的开始时间
  const { leading, trailing } = options;
  let lastTime = 0;
  let timer = null;

  const _throttle = function (...args) {
    return new Promise((resolve, reject) => {
      const nowTime = new Date().getTime();
      if (!lastTime && !leading) lastTime = nowTime;

      const remainTime = interval - (nowTime - lastTime);
      if (remainTime <= 0) {
        if (timer) {
          clearTimeout(timer);
          timer = null;
        }

        const result = fn.apply(this, args);
        if (resultCallback) resultCallback(result);
        resolve(result);
        // 保留上次触发时间
        lastTime = nowTime;
        return;
      }
      if (trailing && !timer) {
        timer = setTimeout(() => {
          timer = null;
          lastTime = !leading ? 0 : new Date().getTime();
          const result = fn.apply(this, args);
          if (resultCallback) resultCallback(result);
          resolve(result);
        }, remainTime);
      }
    });
  };

  _throttle.cancel = function () {
    lastTime = 0;
    timer = null;
  };
  return _throttle;
}
