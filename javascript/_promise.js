const PROMISE_STATUS_PENDING = "onpending";
const PROMISE_STATUS_FULFILLED = "fullfilled";
const PROMISE_STATUS_REJECTED = "rejected";
class MPromise {
  constructor(executor) {
    this.status = PROMISE_STATUS_PENDING;
    this.value = undefined;
    this.reason = undefined;
    this.onFulfilledFns = [];
    this.onRejectedFns = [];
    const resolve = (value) => {
      if (this.status === PROMISE_STATUS_PENDING) {
        queueMicrotask(() => {
          if (this.status !== PROMISE_STATUS_PENDING) return;
          this.status = PROMISE_STATUS_FULFILLED;
          this.value = value;
          this.onFulfilledFns.forEach((fn) => {
            fn(this.value);
          });
          // this.onFulfilled(this.value);
        });
      }
    };

    const reject = (reason) => {
      if (this.status === PROMISE_STATUS_PENDING) {
        //  setTimeout/queueMicrotask注意代码调用顺序

        queueMicrotask(() => {
          if (this.status !== PROMISE_STATUS_PENDING) return;
          this.status = PROMISE_STATUS_REJECTED;
          this.reason = reason;
          this.onFulfilledFns.forEach((fn) => {
            fn(this.reason);
          });
        });
      }
    };
    executor(resolve, reject);
  }
  then(onFulfilled, onRejected) {
    return new MPromise((resolve, reject) => {
      //1. 在then调用的时候 状态已经确定下来
      if (this.status === PROMISE_STATUS_FULFILLED && onFulfilled) {
        try {
          const value = onFulfilled(this.value);
          resolve(value);
        } catch (err) {
          reject(err);
        }
      }
      if (this.status === PROMISE_STATUS_REJECTED && onRejected) {
        try {
          const reason = onRejected(this.reason);
          resolve(reason);
        } catch (err) {
          reject(err);
        }
      }
      // 2.成功回调和失败回调 加入数组
      if (this.status === PROMISE_STATUS_PENDING) {
        this.onFulfilledFns.push(() => {
          const value = onFulfilled(this.value);
          resolve(value);
        });
        this.onRejectedFns.push(() => {
          const reason = onRejected(this.reason);
          resolve(reason);
        });
        // this.onFulfilledFns.push(onFulfilled);
        // this.onRejectedFns.push(onRejected);
      }
      // this.onFulfilled = onFulfilled;
      // this.onRejected = onRejected;
    });
  }
}

const promise = new MPromise((resolve, reject) => {
  console.log("pending-------");
  //   reject(22);
  resolve(11);
});

promise.then(
  (res) => {
    console.info("res: ", res);
  },
  (err) => {}
);

setTimeout(() => {
  promise.then(
    (res) => {
      console.info("res2: ", res);
    },
    (err) => {
      console.info("err");
    }
  );
}, 1900);
