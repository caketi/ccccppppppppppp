替换实例
r : 进入单字符替换模式
R : 进入替换模式
&: 重复上次的替换过程
:s/vi/vim/ : 只替换当前行的第一个 vi 为 vim
:s/vi/vim/g : 替换当前行的所有 vi 为 vim
:%s/vi/vim/g : 替换全文所有 vi 为 vim
:%s/vi/vim/gi : 替换全文所有 vi 为 vim, 大小写不敏感
:n,$s/vi/vim/gci : 替换从第 n 行到结尾所有 vi 为 vim, 每次替换提示, 不区分大小写   :17,$s/Plug/Plugin[已使用]
:.,$s/vi/vim/gci : 替换从当前行到结尾所有 vi 为 vim, 每次替换提示, 不区分大小写
:.,+3s/^/#: 在当前行到下面三行添加 # 的注释
:g/^\s*$/d : 删除所有空行
:215,237 s/\(.\)$/\1(自定义)/c: 将 215 至 237 行尾部添加 (自定义)
:%s/^\n$//gc/ : 替换多个空行为一个空行
:122,250s/\(201\d*\)\.\(\d*\)\.\(\d*\)\s/\1-\2-\3_/gc: 替换 2017.12.31类型的字段为2017-12-31_
%s/\(\](http:.*com\/\)\(HK.*\))/\](https:\/\/a.hanleylee.com\/\2?x-oss-process=style\/WaMa)/gc: 将[](http: ....com) 替换成 https 并且尾部带有样式参数
:%s/\(a.*bc\)\(<.*>\)\(xy.*z\)/\3\2\1/gc: 使用缓冲块实现对前后区域匹配并翻转位置(需要时再理解)
:%s/hello/&, world/: 将会把hello替换成hello, wolrd
:%s/.*/(&)/: 将会把所有行用()包含起来
: s/world/\U&/: 把 world 变成 WORLD
:%s ; /user1/tim;/home/time;g: /user1/tim改为/home/time, 除了/字符外, 还可以使用除反斜杆, 双引号和竖直线 \, ", 和 |, 之外的任何非字母表, 非空白字符作为分隔符, 在对路径名进行修改时, 这点尤其便利
:s: 与 :s//~/相同, 重复上次替换
:&: 重复上次替换
%s/\<child\>/children/g: 保证在 child 是个完整单词的情况下进行替换
:g/mg[ira]box/s/box/square/g: 将 mgibox routine, mgrbox routine, mgabox routine, 中的 box 换为 square
&: 直接使用 & 也是重复上次替换的意思
替换时系统会对用户进行询问, 有 (y/n/a/q/1/^E/^Y)

y : 表示同意当前替换
n : 表示不同意当前 替换
a : 表示替换当前和后面的并且不再确认
q : 表示立即结束替换操作
1 : 表示把当前的替换后结束替换操作;
^E : 向上滚屏
^Y : 向下滚屏,
