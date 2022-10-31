// 接雨水
var Trap = function(height){
    let maxi = 0
    let maxHeight = -Infinity
    for(let i = 0; i < height.length; i++){
        if(height[i] > maxHeight){
            maxHeight = height[i]
            maxi = i
        }
    }
    let max = -Infinity
    let water = 0;
    for(let i = 0; i < maxi; i++){
        if(height[i] > max){
            max = height[i]
        }else {
            water += max-height[i]
        }
    }

    max  = -Infinity
    for(let i = height.length - 1; i > maxi; i--){
        if(height[i] > max){
            max = height[i]
        }else {
            water += max - height[i]
        }
    }
    return water
}
console.log(Trap([0,1,0,2,1,0,1,3]))
// 3步问题 走一步 、二步 、三步
var waysToStep = function(n){
    if(n === 0) return 1
    if(n === 1) return 1
    if(n === 2) return 2
    let a = 1, b = 1, c = 2, d;
    for(let i = 3; i <= n; i++){
        d = (a+b+c) % 1000000007
        a = b
        b = c
        c = d
    }
    return c
}
console.log(waysToStep(5))
// 完全平方数 给一个数n返回平方和是这个数 所需的数量是多少，如 1 只需 1^2 \\\\ 2 1^2 + 1^2
var numSquares = function (n) {
  let nums = [0, 1];
  for (let i = 2; i <= n; i++) {
    let min = Infinity;
    for (let s = 1; s * s <= i; s++) {
      //   for (let s = 2; s * s <= n; s++) {
      //     // if(nums[i-s*s] + 1 < min){
      //     //     min = nums[i-s*s] + 1
      //     // }
      //   }
      let num = nums[i - s * s] + 1;
      min = Math.min(min, num);
    }
    nums[i] = min;
  }
  console.log(nums);
  return nums[n];
};
console.log(numSquares(2));

// nim游戏，先手赢--只要石头数量能被4模后不等0就行也就是保证结果落在1-3之间，
var canWinNim = function (n) {
  return n % 4 != 0;
};
console.log(canWinNim(2));

// 最大子序和，找具有最大和的连续子数组
var maxSubArray = function (nums) {
  let max = -Infinity;
  let maxWithLastElement = 0;
  for (let i = 0; i < nums.length; i++) {
    if (maxWithLastElement > 0) {
      maxWithLastElement = maxWithLastElement + nums[i];
    } else {
      maxWithLastElement = nums[i];
    }
    max = Math.max(max, maxWithLastElement);
  }
  return max;
};
console.log(maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]));
