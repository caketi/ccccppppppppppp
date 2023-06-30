# webpack

## module

模块化---去掉全局变量

- 模块顶层this的指向 
模块中 顶层的this指向undefined

- import export 具有提升效果

## webpack loader

```js
const HtmlWebpackPlugin = require('html-webpack-plugin')
const path = require('path');
module.exports = {
    pugins:[
        new HtmlWebpackPlugin({
            template: './index.html'
        })
    ],
    entry:{
        index: './src/index.js',
        search: './src/search.js'
    },
    output: {
        path: path.resolve(__dirname, 'dist')
        filename:'[name].js'
    }
}

```

use:['style-loader', 'css-loader']
use:['MiniCssExtractPlugin.loader', 'css-loader']

