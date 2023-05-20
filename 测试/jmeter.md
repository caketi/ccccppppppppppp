# Jmeter

- 压测原理和元件组成
- 前置 后置处理器
- 逻辑控制器 正则表达式
- 定时器场景 数据处理

## 分布式压测

- 被压测系统没到瓶颈之前，发压机难免先发送资源不足的情况
- 分散部署多个jmeter agent--将压测脚本远程运行，共同实施压测 **remote agent**
- jmeter.properties || close rmi ssl-- server.rmi.ssl.disable=true
- jmeter-server -Djava.rmi.server.hostname=xxx -Dserver_port=xx
- 添加运行依赖库到lib/ext目录下
