# 阅读材料

[https://juejin.cn/post/6886247611318140942](css浮动)

seo搜索引擎优化
DTD doctype
header
body

    block
    inline
    inline-block

## http

0.9 --- GET  无请求头 无状态码 短链接
1.0 --- GET POST HEAD 请求头 状态码
1.1 --- 单个IP地址提供多个域名 长链接 分块编码 更多的请求方法
2   --- 多路复用 并行请求通过同一链接处理---将一种资源优先于另一种资源的能力
3

http请求无状态 --- 降低服务器压力 -- 参考cookie session token

## slice() substring() substr()

slice() substring() [a,b) -- 其中substring()的参数可以互换
substr(1,3) 1开始取3个

## 绝对定位水平居中 50% margin-top margin-left 一半

并排---浮动 定位
ol绝对定位，li浮动

```css
p{
    width: 80px;
    height: 80px;
    background-color: orange;
    position: absolute;
    top: 50%;
    left: 50%;
    margin-top: -40px;
    margin-left: -40px;
}
```

## 如何创建BFC

1. float的值不是none
2. position的值不是static relative
3. display的值是inline-block、flex或inline-flex
4. overflow:hidden --- 非常好用

- 垂直显示的盒子不要设置浮动，只有并排显示的盒子设置浮动
- 大盒子带着小盒子跑 一个大盒子中，内部可以继续使用浮动
- div免费，可不节约

```css
a {
    display:blcok;
    width: 60px;
    height: 100px;
}
```

## 脱离文档流 浮动、绝对定位、固定定位

## UTF-8 gb2312（gbk)

1个汉字3个字节 1个汉字2个字节

## 如何清除浮动

浮动--最初解决文字环绕问题
元素的宽度会自动收缩到其内容的宽度，除非显式设置了宽度。
浮动元素会尽可能地靠近容器的左侧或右侧。
其他非浮动元素会环绕在浮动元素周围，但是如果浮动元素太宽，可能会出现被覆盖的情况。
浮动元素会脱离正常的文档流，可能会对其他元素的布局产生影响。

- 让盒子负责自己的布局
- overflow:hidden(auto)

## position:absolute / fixed

- 前者相对最近的 absolute / relative
- 后者相对屏幕 viewport

## display:inline-block 间隙

- 字符间距
- 消灭字符或者消灭间距

## 实现两栏 三栏布局的方法

- 表格 / float+margin / inline-block / flexbox

## 如何适配移动端页面

- viewport
- rem / viewport / media query
- 设计上 隐藏 折行 自适应

## doctype

- 让浏览器标准模式渲染
- 让浏览器知道元素的合法性

## html4 or html5

## css reset -- yui lib Normalize.css

```css
* {
  margin: 0;
  padding: 0;
}
```

## a > div 为何合法

不一定合法 ，取决于外面包裹的元素

## CSS 部分问题与解答

这里是 [Front End Web Development Quiz](http://davidshariff.com/quiz/) 中的 CSS 部分问题与解答.

1. Q: CSS 属性是否区分大小写？

        ```
        ul {
            MaRGin: 10px;
        }
        ```

    A: 不区分。
    HTML，CSS 都对大小写不敏感，但为了更好的可读性和团队协作一般都小写，而在 XHTML 中元素名称和属性是必须小写的。

2. Q: 行内(inline)元素 设置`margin-top`和`margin-bottom` 是否起作用？

    A: 不起作用。(答案是起作用，个人觉得不对。)

    html 里的元素分为替换元素（replaced element）和非替换元素（non-replaced element）。

    - 替换元素是指用作为其他内容占位符的一个元素。最典型的就是`img`，它只是指向一个图像文件。以及大多数表单元素也是替换，例如`input`等。
    - 非替换元素是指内容包含在文档中的元素。例如，如果一个段落的文本内容都放在该元素本身之内，则这个段落就是一个非替换元素。

    讨论`margin-top`和`margin-bottom`对行内元素是否起作用，则要对行内替换元素和行内非替换元素分别讨论。

    首先我们应该明确外边距可以应用到行内元素，规范中是允许的，不过由于在向一个行内非替换元素应用外边距，对行高(line-height)没有任何影响。由于外边距实际上是透明的。所以对声明`margin-top`和`margin-bottom`没有任何视觉效果。其原因就在于行内非替换元素的外边距不会改变一个元素的行高。而对于行内非替换元素的左右边距则不是这样，是有影响的。

    而为替换元素设置的外边距会影响行高，可能会使行高增加或减少，这取决于上下外边距的值。行内替换元素的左右边距与非替换元素的左右边距的作用一样。来看看 demo:

    <http://codepen.io/paddingme/pen/JwCDF>

3. Q: 对内联元素设置`padding-top`和`padding-bottom`是否会增加它的高度？（原题是 Does setting padding-top and padding-bottom on an inline element add to its dimensions?）

    A: 答案是不会。同上题比较纠结，不太明白这里的 dimensions 指的是到底是什么意思？放置一边，咱们来分析下。对于行内元素，设置左右内边距，左右内边距将是可见的。而设置上下内边距，设置背景颜色后可以看见内边距区域有增加，对于行内非替换元素，不会影响其行高，不会撑开父元素。而对于替换元素，则撑开了父元素。看下 demo，更好的理解下：

    <http://codepen.io/paddingme/pen/CnFpa>

4. Q: 设置`p`的`font-size:10rem`，当用户重置或拖曳浏览器窗口时，文本大小是否会也随着变化？

    A: 不会。

    `rem`是以`html`根元素中`font-size`的大小为基准的相对度量单位，文本的大小不会随着窗口的大小改变而改变。

5. Q: 伪类选择器`:checked`将作用与`input`类型为`radio`或者`checkbox`,不会作用于`option`。

    A: 不对。

    伪类选择器`checked`的定义很明显:

    > The :checked CSS pseudo-class selector represents any radio (`<input type="radio">`), checkbox (`<input type="checkbox">`) or option (`<option>`in a `<select>`) element that is checked or toggled to an on state. The user can change this state by clicking on the element, or selecting a different value, in which case the :checked pseudo-class no longer applies to this element, but will to the relevant one.

6. Q: 在 HTML 文本中，伪类`:root`总是指向`html`元素？

    A: 不是（答案中给出了是 ==||）。以下摘自知乎[:root 与 html 在 CSS3 中指的是同一个元素吗？](http://www.zhihu.com/question/20312140)的答案：

    > 单指创建的根。这个根可能不是 html ，如果是片段 html，没有创建根，则为片段的根。把这下面 URL 打到支持 data URL 的瀏覽器看看（Firefox, Chrome, Safari, Opera），可见一斑：

    ```
    data:application/xhtml+xml,<div xmlns="http://www.w3.org/1999/xhtml"><style>:root { background: green; } html { background: red !important; }</style></div>
    ```

7. Q:`translate()`方法能移动一个元素在 z 轴上的位置？

    A: 不能。`translate()`方法只能改变 x 轴，y 轴上的位移。

8. Q: 如下代码中文本“Sausage”的颜色是?

    ```
    <ul class="shopping-list" id="awesome">
        <li><span>Milk</span></li>
        <li class="favorite" id="must-buy"><span class="highlight">Sausage</span></li>
    </ul>
    ```

    ```
    ul {color:red;}
    li {color:blue;}
    ```

    A: blue。

9. Q: 如下代码中文本“Sausage”的颜色是?

    ```
    <ul class="shopping-list" id="awesome">
        <li><span>Milk</span></li>
        <li class="favorite" id="must-buy"><span class="highlight">Sausage</span></li>
    </ul>
    ```

    ```
    ul {color:red;}
    #must-buy {color:blue;}
    ```

    A: blue。

10. Q: 如下代码中文本“Sausage”的颜色是?

    ```
    <ul class="shopping-list" id="awesome">
        <li><span>Milk</span></li>
        <li class="favorite" id="must-buy"><span class="highlight">Sausage</span></li>
    </ul>
    ```

    ```
    .shopping-list .favorite {
        color: red;
    }
    #must-buy {
        color: blue;
    }
    ```

    A: blue。

11. Q: 如下代码中文本“Sausage”的颜色是?

    ```
    <ul class="shopping-list" id="awesome">
        <li><span>Milk</span></li>
        <li class="favorite" id="must-buy"><span class="highlight">Sausage</span></li>
    </ul>
    ```

    ```
    ul#awesome {
        color: red;
    }
    ul.shopping-list li.favorite span {
        color: blue;
    }
    ```

    A: blue。

12. Q: 如下代码中文本“Sausage”的颜色是?

    ```
    <ul class="shopping-list" id="awesome">
        <li><span>Milk</span></li>
        <li class="favorite" id="must-buy"><span class="highlight">Sausage</span></li>
    </ul>
    ```

    ```
    ul#awesome #must-buy {
        color: red;
    }
    .favorite span {
        color: blue!important;
    }
    ```

    A: blue。

13. Q: 如下代码中文本“Sausage”的颜色是?

    ```
    <ul class="shopping-list" id="awesome">
        <li><span>Milk</span></li>
        <li class="favorite" id="must-buy"><span class="highlight">Sausage</span></li>
    </ul>
    ```

    ```
    ul.shopping-list li .highlight {
        color: red;
    }
    ul.shopping-list li .highlight:nth-of-type(odd) {
        color: blue;
    }
    ```

    A: blue。

14. Q: 如下代码中文本“Sausage”的颜色是?

    ```
    <ul class="shopping-list" id="awesome">
        <li><span>Milk</span></li>
        <li class="favorite" id="must-buy"><span class="highlight">Sausage</span></li>
    </ul>
    ```

    ```
    #awesome .favorite:not(#awesome) .highlight {
        color: red;
    }
    #awesome .highlight:nth-of-type(1):nth-last-of-type(1) {
        color: blue;
    }
    ```

    A: blue。

15. Q:`#example`位置如何变化：

    ```
    <p id="example">Hello</p>
    ```

    ```
    #example {margin-bottom: -5px;}
    ```

    A: 向上移动 5px。

16. Q: `#example`位置如何变化：

    ```
    <p id="example">Hello</p>
    ```

    ```
    #example {margin-left: -5px;}
    ```

    A: 向左移动 5px。

17. `#i-am-useless` 会被浏览器加载吗？

    ```
    <div id="test1">
        <span id="test2"></span>
    </div>
    ```

    ```
    #i-am-useless {background-image: url('mypic.jpg');}
    ```

    A: 不会

18. `mypic.jpg` 会被浏览器加载吗？

    ```
    <div id="test1">
        <span id="test2"></span>
    </div>
    ```

    ```
    #test2 {
        background-image: url('mypic.jpg');
        display: none;
    }
    ```

    A: 会被下载。

19. `mypic.jpg` 会被浏览器加载吗？

    ```
    <div id="test1">
        <span id="test2"></span>
    </div>
    ```

    ```
    #test1 {
        display: none;
    }
    #test2 {
        background-image: url('mypic.jpg');
        visibility: hidden;
    }
    ```

    A: 不会被下载。

20. Q: `only` 选择器的作用是？

    ```
    @media only screen and (max-width: 1024px) {argin: 0;}
    ```

    A：停止旧版本浏览器解析选择器的其余部分。

    only 用来定某种特定的媒体类型，可以用来排除不支持媒体查询的浏览器。其实 only 很多时候是用来对那些不支持 Media Query 但却支持 Media Type 的设备隐藏样式表的。其主要有：支持媒体特性（Media Queries）的设备，正常调用样式，此时就当 only 不存在；对于不支持媒体特性(Media Queries)但又支持媒体类型(Media Type)的设备，这样就会不读了样式，因为其先读 only 而不是 screen；另外不支持 Media Qqueries 的浏览器，不论是否支持 only，样式都不会被采用。

21. Q:`overfloa:hidden` 是否形成新的块级格式化上下文？

    ```
    <div>
        <p>I am floated</p>
        <p>So am I</p>
    </div>
    ```

    ```
    div {overflow: hidden;}
    p {float: left;}
    ```

    A：会形成。

    会触发 BFC 的条件有：

    - float 的值不为 none。
    - overflow 的值不为 visible。
    - display 的值为 table-cell, table-caption, inline-block 中的任何一个。
    - position 的值不为 relative 和 static。

22. Q: `screen`关键词是指设备物理屏幕的大小还是指浏览器的视窗？

    ```
    @media only screen and (max-width: 1024px) {margin: 0;}
    ```

    A: 浏览器视窗

## 知识点总结

tips:根据以上考点总结下如下知识点，后期会写文章进行总结，这里只挑出重点进行解析。

- 关于 CSS 选择器以及优先级的知识可查阅如下文章：

  - [CSS 选择器参考手册](http://www.w3school.com.cn/cssref/css_selectors.asp)
  - [CSS 选择器笔记](http://www.ruanyifeng.com/blog/2009/03/css_selectors.html)
  - [高级 CSS 样式选择器](http://blog.fity.cn/post/421/)
  - [征服高级 CSS 选择器](http://www.qianduan.net/taming-advanced-css-selectors.html)
  - [详解 CSS 选择器、优先级与匹配原理](http://developer.51cto.com/art/201009/226852.htm)
  - [优先级](https://developer.mozilla.org/zh-CN/docs/Web/CSS/Specificity)
  - [牢记 31 种 CSS 选择器用法](http://peiwen.lu/css-selectors-must-memorize/#post__title)

- 如何计算优先级：

  > 那么你如何计算指定选择器的优先级？如果你考虑到将优先级表示为用逗号隔开的四个数字就会相当简单，比如：1, 1, 1, 1 或 0, 2, 0, 1

  - 第一个数字(a)通常就是 0，除非在标签上使用 style 属性；
  - 第二个数字(b)是该选择器上的 id 的数量的总和；
  - 第三个数字(c)是用在该选择器上的其它属性选择器和伪类的总和。这里包括 class (.example) 和属性选择器(比如 `li[id=red]`)；
  - 第四个数字(d)计算元素(就像 table、p、div 等等)和伪元素(就像:first-line 等)；
  - 通用选择器(\*)是 0 优先级；
  - 如果两个选择器有同样的优先级，在样式表中后面的那个起作用。

- 浏览器 CSS 匹配顺序：

  浏览器 CSS 匹配不是从左到右进行查找，而是从右到左进行查找。比如`#divBox p span.red{color:red;}`，浏览器的查找顺序如下：先查找 html 中所有 class='red'的 span 元素，找到后，再查找其父辈元素中是否有 p 元素，再判断 p 的父元素中是否有 id 为 divBox 的 div 元素，如果都存在则匹配上。浏览器从右到左进行查找的好处是为了尽早过滤掉一些无关的样式规则和元素。

- `display:none` 和`visibilty:hidden`的区别：

  可参考：

  - [What is the difference between visibility:hidden and display:none?](http://stackoverflow.com/questions/133051/what-is-the-difference-between-visibilityhidden-and-displaynone)
  - [display:none 和 visibility:hidden 的区别！](http://bbs.blueidea.com/thread-2942695-1-1.html)

  > `display:none`和`visibility:hidden`都是把网页上某个元素隐藏起来的功能，但两者有所区别，经过亲自实验，我发现使用`` visibility:hidden`属性会使对象不可见，但该对象在网页所占的空间没有改变（看不见但摸得到），等于留出了一块空白区域，而`display:none`属性会使这个对象彻底消失（看不见也摸不到）

  > `display:none` means that the the tag in question will not appear on the page at all (although you can still interact with it through the dom). There will be no space allocated for it between the other tags. visibility:hidden means that unlike display:none, the tag is not visible, but space is allocated for it on the page. so for example:

  ```
  <span>test</span> | <span>Appropriate style in this tag</span> | <span>test</span>
  ```

  > `display:none` would be:

  > test | | test

  > `visibility:hidden` would be:

  > test |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| test

  > In visibility:hidden the tag is rendered, it just isn't seen on the page.

- 浏览器如何渲染，可以查阅如下文章：

  - [浏览器的渲染原理简介](http://coolshell.cn/articles/9666.html)
  - [专题：浏览器:渲染重绘、重排两三事](http://developer.51cto.com/art/201311/418133.htm)
  - [浏览器加载和渲染 HTML 的顺序以及 Gzip 的问题](http://www.nowamagic.net/academy/detail/48110160)
  - [从 FE 的角度上再看输入 url 后都发生了什么](http://div.io/topic/609)

- BFC( block formatting contexts ) 块级格式上下文

  - [深入理解 BFC 和 Margin Collapse](http://www.w3cplus.com/css/understanding-bfc-and-margin-collapse.html)
  - [CSS 布局中一个简单的应用 BFC 的例子](http://www.aliued.cn/2012/12/31/css%E5%B8%83%E5%B1%80%E4%B8%AD%E4%B8%80%E4%B8%AA%E7%AE%80%E5%8D%95%E7%9A%84%E5%BA%94%E7%94%A8bfc%E7%9A%84%E4%BE%8B%E5%AD%90.html)
  - [理解 BFC(Block Formatting Context)](http://jqc.me/?p=68)

- margin，padding 相关的知识可以参考查阅《CSS 权威指南》
