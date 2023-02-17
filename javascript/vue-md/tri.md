## 路由拦截
axios拦截
需要在路由配置中添加一个字段，用于判断路由是否需要拦截
```javascript
{
    name: 'index',
    path: '/index',
    component: Index,
    meta:{
        requireAuth: true
    }
    router.beforeEach((to,from,next)=>{
        if(to.meta.requireAuth){
            if(store.state.token){
                next()
            }else{

            }
        }
    })
}
```