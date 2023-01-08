function getSum(){
    let sum = 0
    for(let i = 0; i < 10000; i++){
        sum += i
    }
    return sum
}

process.on('message', data => {
    console.info('child process id---', process.pid)
    console.info('child process copy info=0---', data)

    const sum = getSum()
    process.send(sum)
})