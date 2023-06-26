const http = require('http')
const md5 = require('md5')
const server = http.createServer((req, res) => {
    res.setHeader('Access-Control-Allow-Origin',"http://localhost:3000");
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
    res.setHeader('Access-Control-Allow-Credentials', 'true');
    if(req.method=='POST'){
        let postData = '';
        req.on('data', (chunk) => {
            postData += chunk;
        });
        req.on('end', () => {
            console.log(postData);
            res.setHeader('Set-Cookie', [`token=${md5(postData + new Date().valueOf())};HttpOnly:path=/webstorage`]);
            res.end(`{
                code: 0,
                msg: 'ok'
            }`)
        });
    }else {
        res.writeHead(200)
        res.end()
    }
});
server.listen(7777, () => {
    console.log('server start at 7777');
})