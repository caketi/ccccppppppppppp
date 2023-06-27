# react 

## react fiber 

## react 节点类型

react元素--createElement返回的结果
组件----类组件 函数组件
fiberNode---组成fiber架构的节点

```js
<script type="text/babel">
let Component = () => <div>stduy react</div>
let reactEle = <div style="color:red">
                    hello3
                    <Component></Component>
                    <p>
                       <span>good</span>
                    </p>
                </div>
        console.log(reactEle);
</script>
```
## 类组件的本质
```js
let FuncComponent = function(){

}
FuncComponent.prototype = new React.Component();
FuncComponent.prototype.render = function(){
    return <div>caketi</div>
}
console.log(FuncComponent.prototype);
ReactDOM.render(<FuncComponent></FuncComponent>, document.getElementById('root'))
```

## 组件渲染逻辑

组件---进入渲染流程---isReactComponent---是--实例化类组件并传入props--调用构造函数---实例化类组件---调用render函数---返回---虚拟dom对象
--否--直接调用函数并传入props--返回--虚拟dom对象

