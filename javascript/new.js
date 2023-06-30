
function fun() {
    this.a = 3;
    this.b = 6;

}

// js--- new一个函数--会自动返回内部信息
var obj = new fun()
console.info(obj)

// 显示时间戳的两种方法。 1970.1.1 毫秒数
var d = new Date()
var timestamp1 = d.getTime()  //精确到毫秒
var timestamp2 = Date.parse(d) //精确到秒 最后三位000

console.info(timestamp1)
console.info(timestamp2)


var dd = new Date('2032-09-03')
// var dd = new Date(2032, 8, 1)
console.info(dd)
console.info('年', dd.getFullYear())
console.info('月', dd.getMonth()) // 从0开始
console.info('日', dd.getDate())
console.info('星期', dd.getDay())
console.info('小时', dd.getHours())
console.info('分钟', dd.getMinutes())
console.info('秒', dd.getSeconds())



// apply形式传入零散值
var arr = [3, 6, 3, 2]
var max = Math.max.apply(null, arr)
console.info(Math.max(...arr))
console.log(max)



setInterval(() => {
    var nd = new Date();
    var td = new Date(2024, 5, 7)

    var diff = td - nd;
    var day = parseInt(diff / (1000 * 60 * 60 * 24))
    var hours = parseInt(diff % (1000 * 60 * 60 * 24) / (1000 * 60 * 60))
    var minutes = parseInt(diff % (1000 * 60 * 60) / (1000 * 60))
    var seconds = parseInt(diff % (1000 * 60 * 60) % (1000 * 60) / 1000)

    // <h1>2024高考倒计时</h1>
    // <h2 id="info"></h2>
    // var info = document.getElementById('info')
    // info.innerText = day+'天' + hours + '时' + minutes + '分' + seconds + '秒'

    console.info('距离2024高考还有 '+ day+'天' + hours + '时' + minutes + '分' + seconds + '秒')
}, 1000);