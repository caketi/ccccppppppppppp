// 命令式 声明式（有点像封装函数） 

const { effectScope } = require("vue")

// 运行时渲染
const vnode = {
    type: 'div',
    props: {
        class: 'tets'
    },
    children: 'he'
}

function render(vnode){
    const ele = document.createElement(vnode.type)
    ele.className = vnode.props.class
    ele.innerText = vnode.children
    document.body.appendChild(ele)
}

render(vnode)
// 编译时 HTML标签结构
const proxyProduct = new Proxy(product, {
    set(target, key, newVal, receiver){
        target[key] = newVal
        effect()
        return true
    },
    get(target, key, receiver){
        return target[key]
    }
})