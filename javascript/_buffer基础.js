// const me =  'ccsdfa'
// const buffer = Buffer.from(me)
// console.info(buffer)

const fs = require('fs')

fs.readFile('./_buffer基础.js', {encoding: 'utf-8'},(err, data) => {
    console.log(data)
})