// xhr.withCredentials=true ie6-9不支持  ie10
// load ie6-8不支持
//  error请求发生错误时触发  ie10
// abort ie10
// timeout ie6-7不支持 ie8
// xhr.setRequestHeader
// xhr.responseType xhr.response xhr.responseText 
// response可以替代两个  不考虑兼容性
// responseText只能在没有设置reponseType或者responseType=""
const url = "xxx?word=caketi&passwd=test";
const xhr = new XMLHttpRequest();

xhr.onreadystatechange = () => {
  if (xhr.readyState != 4) return;
  if ((xhr.status >= 200 && xhr.status < 300) || xhr.status == 304) {
    console.log(xhr.responseText);
  }
  xhr.open("GET", url, true);
  xhr.send(null);
};
