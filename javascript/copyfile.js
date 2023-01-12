const fs = require('fs')
const path = require('path') 
// 内置path模块处理

const src2Dir = process.argv[2]
const dest2Dir = process.argv[3]
const destDir = 'E:\\ww\\ccccppppppppppp\\javas'
const srcDir = 'E:\\ww\\ccccppppppppppp\\cpu'
console.info(path.dirname(destDir))
console.info(path.basename(destDir))
console.info(path.extname(destDir))

let i = 0;
while(i < 10){
    i++;
    const num = 'day'
    const srcPath = `${srcDir}`
    const destPath = `${destDir}`
    if(fs.existsSync(destPath)) continue;
    fs.mkdir(destPath, (err) => {
        if(!err) console.log("okay!!!");
        
        const srcFiles = fs.readdirSync(srcPath);
        for(const file of srcFiles){
            if(file.endsWith('.md')){
                fs.copyFile(path.resolve(srcPath,file), path.resolve(destPath, file), (err) => {
                    console.log(err);
                })
            }
        }
    })
}