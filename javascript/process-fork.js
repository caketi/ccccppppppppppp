const http = require('http')
const fork = require('child_process').fork
//访问localhost:300/get-sum
const server = http.createServer((req, res) => {
    if(req.url === '/get-sum'){
        console.info('main process--- id', process.pid)

        const computeProcess = fork('./compute.js')
        computeProcess.send('start compute')

        computeProcess.on('message', data => {
            console.info('main process copy--', data)
            res.end('sum is ' + data)
        })

        computeProcess.on('close', () => {
            console.info('child process quit on error')
            computeProcess.kill()
            res.end('error')
        })
    }
})
server.listen(300, () => {
    console.info('localhost: 300')
})